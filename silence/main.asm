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
