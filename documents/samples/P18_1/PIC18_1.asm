
#include <p18f4620.inc>
		list P=18F4620, F=INHX32, C=160, N=80, ST=OFF, MM=OFF, R=DEC

;;;;;;Configuration Bits;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

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

;;;;;;Equates;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;*******************************************************************
;Constant Defines
;*******************************************************************
#define   RS        LATD,2        ; for v 1.0 used PORTD.3
#define   E         LATD,3        ; for v 1.0 used PORTD.2

temp_lcd  EQU       0x20           ; buffer for Instruction
dat       EQU       0x21           ; buffer for data
delay1	  EQU		0x25
delay2	  EQU		0x26
delay3	  EQU		0x27

;;;;;;Vectors;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
			org		0x0000
			goto	Mainline
			org		0x08				;high priority ISR
			retfie
			org		0x18				;low priority ISR
			retfie

Table	
		db	"ReadingTableLCD", 0


Mainline	
		  movlw		B'01110000'
		  movwf		OSCCON

		  bsf		OSCTUNE, 6
		 ; btfss		OSCTUNE, 6
		 ; goto 		Stop
		  clrf		TRISA
		  clrf		TRISB
		  clrf		TRISC
		  clrf		TRISD
		  call      delay5ms		;wait for LCD to start up
          call      delay5ms
          movlw     B'00110011'   
          call      WR_INS
          movlw     B'00110010'
          call      WR_INS
          movlw     B'00101000'    ; 4 bits, 2 lines,5X7 dot 
          call      WR_INS
          movlw     B'00001100'    ; display on/off
          call      WR_INS
          movlw     B'00000110'    ; Entry mode
          call      WR_INS
          movlw     B'00000001'    ; Clear ram
          call      WR_INS

          
		  movlw		upper Table
		  movwf		TBLPTRU
		  movlw		high Table
		  movwf		TBLPTRH
		  movlw		low Table
		  movwf		TBLPTRL
		  tblrd*
		  movf		TABLAT, W
Again
          call      WR_DATA
		  tblrd+*
		  movf		TABLAT, W
		  bnz		Again

Blink
		  movlw		B'10101010'
		  movwf		LATB
		  
DelayLoopLong
		  dcfsnz	delay3
		  goto 		NoBlink
		  call		delay5ms
		  bra		DelayLoopLong
NoBlink
		  comf		LATB
		  bra		DelayLoopLong
		  
Stop      goto      Stop

;****************************************
; Write command to LCD
; Input  : W
; output : -
;****************************************
WR_INS   

		bcf		RS	  				; clear Register Status bit
		movwf	temp_lcd			; store instruction
		andlw	0xF0			  	; mask 4 bits MSB
		movwf	LATD			  	; send 4 bits MSB

		bsf		E					; pulse enable high
		swapf	temp_lcd, WREG		  	; swap nibbles
		andlw	0xF0			  	; mask 4 bits LSB
		bcf		E
		movwf	LATD			  	; send 4 bits LSB
		bsf		E					; pulse enable high
		nop
		bcf		E
		call	delay5ms

		return


;***************************************
; Write data to LCD
; Input  : W
; Output : -
;***************************************
WR_DATA   

		bcf		RS					; clear Register Status bit
        movwf   dat				; store character
        movf	dat, WREG
		andlw   0xF0			  	; mask 4 bits MSB
        addlw   4			  	; set Register Status
        movwf   PORTD			  	; send 4 bits MSB

		bsf		E					; pulse enable high
        swapf   dat, WREG		  	; swap nibbles
        andlw   0xF0			  	; mask 4 bits LSB
		bcf		E
        addlw   4				; set Register Status
        movwf   PORTD			  	; send 4 bits LSB
		bsf		E					; pulse enable high
		nop
		bcf		E

		call	delay44us		

        return

;******************************************************************************
; Delay44us (): wait exactly  110 cycles (44 us)
; <www.piclist.org>

delay44us
		movlw	0x23
		movwf	delay1, 0
	
Delay44usLoop
	
		decfsz	delay1, f
		goto	Delay44usLoop	
		return

delay5ms
		movlw	0xC2
		movwf	delay1,0
		movlw	0x0A
		movwf	delay2,0

Delay5msLoop
		decfsz	delay1, f
		goto	d2
		decfsz	delay2, f
d2		goto	Delay5msLoop
		return
end