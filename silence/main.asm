list P=18F4620, F=INHX32, C=160, N=80, ST=OFF, MM=OFF, R=DEC

#include <p18f4620.inc>
#include <macros.inc>
#include <lcd18.inc>


;;;;;;Configuration Bits;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		CONFIG OSC=HS, FCMEN=OFF, IESO=OFF
		CONFIG PWRT = OFF, BOREN = SBORDIS, BORV = 3
		CONFIG WDT = OFF, WDTPS = 32768
		CONFIG MCLRE = ON, LPT1OSC = OFF, PBADEN = OFF, CCP2MX = PORTC
		CONFIG STVREN = ON, LVP = OFF, XINST = OFF
		CONFIG DEBUG = OFF
		CONFIG CP0 = OFF, CP1 = OFF, CP2 = OFF, CP3 = OFF
		CONFIG CPB = OFF, CPD = OFF
		CONFIG WRT0 = OFF, WRT1 = OFF, WRT2 = OFF, WRT3 = OFF
		CONFIG WRTB = OFF, WRTC = OFF, WRTD = OFF
		CONFIG EBTR0 = OFF, EBTR1 = OFF, EBTR2 = OFF, EBTR3 = OFF
		CONFIG EBTRB = OFF

	udata_acs
state	res 1
key_pressed res 1

offset_bcd res 2
interval_bcd res 2

param_offset res 2		;offset in cm, up to 300, therefore 2 bytes
param_interval res 2

tmp1	res 1			;temporary storage for calculations

;;;;;;Vectors;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	org		0x0000
	
	
	goto	Init
	
	org		0x08				;high priority ISR
	goto IHR

	org		0x18				;low priority ISR
	goto IHR
	retfie

	code

IHR
	;; if it was a key input, go to the menu handling thing.
	btfsc	PORTB,1		;
	goto	menu_handler
	
	
	
	retfie
	
Init
	clrf	INTCON		; no interrupts
	clrf	TRISA		; PORTA is output
	movlw	b'11110010'	; Keypad inputs on Port B
	movwf	TRISB
	clrf	TRISC
	clrf	TRISD

	clrf	LATA
	clrf	LATB
	clrf	LATC
	clrf	LATD

movlw	b'10101010'
	movwf	LATC
	
	call	InitLCD		; Initializes the LCD
	bsf	INTCON3, INT1IE
	bsf	INTCON2, INTEDG1 ; enable RB1 interrupts
	bsf	INTCON, GIE
	movlw	0
	movwf	state
	call	menu_drawscreen
	goto	Mainline
	
	;; ****************************************
	;; KPHexToInt converts key_pressed into the corresponding number
	;; ****************************************
KPHexToInt
	movlw	upper KeyTbl
	movwf	TBLPTRU
	movlw	high KeyTbl
	movwf	TBLPTRH
	movlw	low KeyTbl
	addwf	key_pressed, W	;add the key offset to the lower end of the table
	movwf	TBLPTRL
	movlw	0
	addwfc	TBLPTRH, F	;let the carry ripple up if we went too far
	addwfc	TBLPTRU, F

	tblrd	*		;read that thing into the latch
	
	movf	TABLAT, W	;put it into W
	movwf	key_pressed
	
KeyTbl	db 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0, 0, 0, 0, 0 ;the list of values
	return


	;; ****************************************
	;; Menu Handler: Takes care of navigation through the menu
	;; ****************************************
menu_handler
	swapf	PORTB,W		;read PortB<7:4> into W<3:0>
	andlw	0x0F		;mask the lower nibble
	rlncf	WREG, W		;program memory counts up by two
	movwf	key_pressed
	movff	key_pressed, PORTC
	select state
	case 0			;Welcome screen
		movf	key_pressed, w
		xorlw	15	;D:Next
		gtifz	menu_next

	endcase
	case 1			;Load Prompt
		movf	key_pressed, w
		xorlw	12	;*:Back
		gtifz	menu_back	
		xorlw	3 ^ 12	;A:Load
		gtifz	menu_next
		xorlw	15 ^ 12	;D:Next
		gtifz	menu_skip

	endcase
	case 2			;Offset Prompt
		PointFSR0To	offset_bcd ;append to offset variable
		movf	key_pressed, w
		xorlw	12	;*:Back
		gtifz	menu_back	
		xorlw	11 ^ 12	;C:Delete
		gtifz	parameter_delete
		xorlw	15 ^ 11	;D:Next
		gtifz	menu_skip	

	;; test for other keys AB#:
		xorlw	3 ^ 15
		gtifz	Mainline
		xorlw	7 ^ 3
		gtifz	Mainline
		xorlw	14 ^ 7
		gtifz	Mainline

	;; otherwise, it's a number key. append.
		goto	parameter_append
	
	endcase
	case 3			;Interval Prompt

	endcase
	endselect
	
	movf	PORTB, f

	goto	Mainline



	;; ****************************************
	;; Adds an offset or interval character and updates the display
	;; ****************************************
parameter_append
	call	KPHexToInt
	;; rotate left by 4 bits
	rlcf	INDF0, f, 4
	andlw	b'00001111'
	andwf	INDF0
	movwf	INDF0
	goto 	Mainline
	return

	;; ****************************************
	;; Deletes an offset or interval character and updates the display
	;; ****************************************
parameter_delete
	rrncf	INDF0, f, 4
	movlw	8
	rrcf	PLUSW0,f, 4	;goto the upper byte and shift it down by four as well
	goto Mainline		;just in case.



	;; ****************************************
	;; Increases the state counter and draws the screen
	;; ****************************************
menu_next
	incf	state, f
	goto	menu_drawscreen

	;; ****************************************
	;; Decreases the state counter and draws the screen
	;; ****************************************
menu_back
	decf	state, f
	goto	menu_drawscreen

	;; ****************************************
	;; Increases the state counter by two and draws the screen
	;; ****************************************
menu_skip
	incf	state, f
	incf	state, f
	goto	menu_drawscreen

menu_drawscreen
	;;  first, load the tablepointer to the tables and write the first and
	;;  second line to the display.
	;;  then, take care of inserting the current variable values.
	
	movlw	upper LCDTbl_1
	movwf	TBLPTRU
	movlw	high LCDTbl_1
	movwf	TBLPTRH
	
	movff	state, tmp1
	movlw	16
	mulwf	tmp1		;now tmp1 = state * 16
	movf	tmp1,w 

	movlw	low LCDTbl_1
	addwf	tmp1, W		;add the key offset*16 to the lower end of the table
	
	movwf	TBLPTRL
	movlw	0
	addwfc	TBLPTRH, F	;let the carry ripple up if we went too far
	addwfc	TBLPTRU, F
	tblrd	*		;read that thing into the latch
	movf	TABLAT, W	;put it into W
	movwf	PORTC
NextChar_1
	call	WrtLCD		;loop through the table entry until 0 is hit
	tblrd	+*
	movf	TABLAT,W
	bnz	NextChar_1

	movlw	0xC0		;position cursor at second line. 0x80 + 0x40 = 0xC0
	call	CmdLCD

	tblrd	+*
	movf	TABLAT,W
	
NextChar_2
	call	WrtLCD		;loop through the table entry until 0 is hit
	tblrd	+*
	movf	TABLAT,W
	bnz	NextChar_2	

	
	goto 	Mainline
	;; Congrats! By now, the standard content for each state should be written.
	
	select state
	case 	3		;add the offset value
	movlw 	.7
	call	CmdLCD
	;; write offset
	endcase
	case 	4			;add the interval value
	movlw	.9
	call	CmdLCD
	;; write interval
	endcase
	endselect

	bcf	INTCON3, INT1IF	;clear RB1 interrupt bit	
	goto Mainline
LCDTbl_1
	db "Welcome         ",0,"         Start:D",0
	db "          Load:A",0,"*:Back    Next:D",0
	db "Ins Cone!   Up:A",0,"*:Back    Down:D",0
	db "Offset:_        ",0,"*:Back    Next:D",0
	db "Interval:_      ",0,"*:Back    Next:D",0
	db "Ready!          ",0,"*:Back   Start:D",0
	db "Deploying ...   ",0,"         Abort:C",0
	db "Success! Stats:A",0,"*:Back          ",0
	db "   cm ( ) Next:A",0,"*:Back TDist:   ",0
	db "Store?     Yes:A",0,"*:Back      No:B",0


	;; Congrats again! The display has been written! Go back and chill!
	

Mainline
	goto	$
end
