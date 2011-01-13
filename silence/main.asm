
list R=hex
list p=16f877

#include "p16f877.inc"
;#include "macros.asm"		

	
__CONFIG _CP_OFF & _DEBUG_OFF &  _CPD_OFF & _LVP_OFF & _BODEN_OFF & _PWRTE_ON & _WDT_OFF & _XT_OSC

#include "lcd.inc"


	
	;; VARIABLE ALIAS DECLARATIONS ;; ******************************

org 0	;reset vector

goto 	init
code	;; CODE GOES HERE: INITIALIZATION
	;; all port a,c,d output, some inputs on b
	;; clear all portabcd
	;; call InitLCD
init
         clrf      INTCON         ; No interrupts
         bsf       STATUS,RP0     ; select bank 1
         clrf      TRISA          ; All port A is output
         movlw     b'11110010'    ; Set required keypad inputs
         movwf     TRISB
         clrf      TRISC          ; All port C is output
         clrf      TRISD          ; All port D is output

         bcf       STATUS,RP0     ; select bank 0
         clrf      PORTA
         clrf      PORTB
         clrf      PORTC
         clrf      PORTD
          
         call	InitLCD    ;Initialize the LCD (code in lcd.asm; imported by lcd.inc)

test
	btfss	PORTB,1     ;Wait until data is available from the keypad
        goto		$-1 

        swapf		PORTB,W     ;Read PortB<7:4> into W<3:0>
        andlw		0x0F
        call     KPHexToChar ;Convert keypad value to LCD character (value is still held in W)
        call     WR_DATA      ;Write the value in W to LCD

        btfsc		PORTB,1     ;Wait until key is released
        goto		$-1
        goto     test


KPHexToChar
	addwf	PCL,f
	dt	"123A456B789C*0#D"
	
end