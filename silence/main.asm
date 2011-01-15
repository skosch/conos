list P=18F4620, F=INHX32, C=160, N=80, ST=OFF, MM=OFF, R=DEC

#include <p18f4620.inc>
#include <lcd18.inc>
#include <macros.asm>

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


	udata
state	res 1
key_pressed res 1
param_offset res 2		;offset in cm, up to 300, therefore 2 bytes
param_interval res 2

;;;;;;Vectors;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	org		0x0000
	
	
	goto	Init
	
	org		0x08				;high priority ISR
	goto IHR

	org		0x18				;low priority ISR
	retfie

	code

IHR
	;; if it was a key input, go to the menu handling thing.
	btfsc	PORTB,1
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

	call	InitLCD		; Initializes the LCD
	bsf	INTCON3, INT1IE
	bsf	INTCON2, INTEDG1 ; enable RB1 interrupts
	bsf	INTCON, GIE


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
	
	SELECT state
	case 0			;Welcome screen
		SELECT key_pressed
		case 15		;D:Next
		goto menu_next
		endcase
		ENDSELECT
	endcase
	case 1			;Load Prompt
		SELECT key_pressed
		case 12		;*:Back
		goto menu_back
		endcase
		case 3		;A:Load
		goto menu_next
		endcase
		case 15		;D:Next
		goto menu_skip
		endcase
		ENDSELECT
	endcase
	case 2			;Offset Prompt
		SELECT key_pressed
		case 0
		goto parameter_append
		endcase
		case 1
		goto parameter_append
		endcase
		case 2
		goto parameter_append
		endcase
		case 4
		goto parameter_append
		endcase
		case 5
		goto parameter_append
		endcase
		case 6
		goto parameter_append
		endcase
		case 8
		goto parameter_append
		endcase
		case 9
		goto parameter_append
		endcase
		case 10
		goto parameter_append
		endcase
		case 13
		goto parameter_append
		endcase
		case 12		;*:Back
		goto menu_back
		endcase
		case 15		;D:Next
		goto menu_next
		endcase
		case 11		;C:Delete
		goto parameter_delete
		endcase
		ENDSELECT
	

	endcase
	case 3			;Interval Prompt

	endcase
	ENDSELECT

	movf	PORTB, f
	bcf	INTCON3, INT1IF	;clear RB1 interrupt bit
	goto	Mainline



	;; ****************************************
	;; Adds an offset or interval character and updates the display
	;; ****************************************
parameter_append
	call	KPHexToInt
	
	SELECT state
	case 3			;offset input
	movlw	.10		;multiply the parameter by ten,
	mulwf	param_offset, f
	movfw	key_pressed
	addwf	param_offset, f	;...then add the key.
	goto menu_drawscreen		;and do the following
	endcase
	case 4
	movlw	.10		;multiply the parameter by ten,
	mulwf	param_interval, f
	movfw	key_pressed
	addwf	param_interval, f	;...then add the key.
	goto menu_drawscreen		;and do the following
	endcase
	ENDSELECT
	goto Mainline		;just in case.
	;; **************************************************

menu_drawscreen
	SELECT state
	case 0
	
	endcase

	ENDSELECT

	
	;; write "Offset: 111             
	;; write offset
	;; write 12-length(offset) spaces, goto second line
	;; write "*:Back    Next:D"
	;; goto Mainline


LCDTbl_1
	db "Welcome        ","         Load:A","Ins Cone!   Up:A""Offset:_       ","Interval:_     ","Ready!         ","Deploying ...  ","Success!       ","   cm( ) Next:A","Store?    Yes:A"
LCDTbl_2
	"         Start:D",
	"*:Back    Next:D"






	
Mainline
	goto	$
end