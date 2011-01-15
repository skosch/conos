
#include <p18f4620.inc>
		list P=18F4620, F=INHX32, C=160, N=80, ST=OFF, MM=OFF, R=DEC

;;;;;;Configuration Bits;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		CONFIG OSC=INTIO67, FCMEN=OFF, IESO=OFF
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

;**************************************************************
; Initialize Part
;  
; ADCON1 - AN0/RA0 as the only analog input
; ADCON2 - Acquisition time = 8 TAD
;		 - Conversion clock = Fosc/64
; TRISB - PORTB as output
;**************************************************************
		org		0
		movlw	B'01110000'	;set internal oscillator frequency
		movwf	OSCCON		;to 8 MHz
		bsf		OSCTUNE, 6	;turn on PLL to enable 32MHz clock frequency
		bra		INIT

INIT	bcf		INTCON,GIE	;disable global interrupt
		movlw	B'00001110'	;configure ADCON1
		movwf	ADCON1		
		movlw	B'00100110'	;configure ADCON2
		movwf	ADCON2
		clrf   	TRISB		;configure PORTB as output
		bra		ADSTART


;***************************************************************
; MAIN PROGRAM
;***************************************************************
ADSTART	rcall	AD_CONV	;call the A2D subroutine
     	movwf	PORTB	;display the high 8-bit result to the LEDs 

ENDLP	bra		ENDLP	;endless loop


;***************************************************************
; AD CONVERT ROUTINE
;***************************************************************
AD_CONV	movlw	B'00000001'	;configure ADCON0
     	movwf	ADCON0		
     	bsf		ADCON0,1	;start the conversion

WAIT	btfsc	ADCON0,1	;wait until the conversion is completed
     	bra		WAIT		;poll the GO bit in ADCON0
     	movf	ADRESH,W	;move the high 8-bit to W
     	return
	end
