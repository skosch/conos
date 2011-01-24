list P=18F4620, F=INHX32, C=160, N=80, ST=OFF, MM=OFF, R=DEC

#include <p18f4620.inc>
#include <macros.inc>
#include <menu.inc>

#include <lcd18.inc>
#include <deploy.inc>

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
	
tmp1	res 1			;temporary storage for calculations
	
cones_deployed res 1
cones_remaining res 1		;boolean, from distance sensor in shaft
timestamp res 3

	;; stats variables
cones_positions res 20
cones_type	res 2

dist_traveled	res 2
stats_current_display res 1	;the number of the cone currently shown
stats_current_set res 1		;the set (date/time) currently being browsed in the stats

stats_mode res 1		;whether or not we're in stats mode, for the print-param.
	
param_offset res 2
param_interval res 2

;;;;;;Vectors;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	org	0x0000
	
	
	goto	Init
	;; ****************************************
	;; NOTE TO SELF : IF YOU WANT TO USE LOW PRIORITY ISR,
	;;	NEED TO ENABLE PRIORITY INTERRUPTS 
	code
	global Init, Mainline
	global state, tmp1, cones_deployed, cones_remaining, timestamp, cones_positions, cones_type, dist_traveled, stats_current_display, stats_current_set, stats_mode, param_offset, param_interval
	
	org	0x08				;high priority ISR
	goto IHR

	org	0x18				;low priority ISR
	goto IHR
	retfie

IHR
	bcf	LATE, 0
	pagesel	menu_handler
	goto	menu_handler
	retfie
	
Init
	clrf	INTCON		; no interrupts
	clrf	TRISA		; PORTA is output
	movlw	b'11110010'	; Keypad inputs on Port B
	movwf	TRISB
	clrf	TRISC
	clrf	TRISD
	clrf	TRISE
	

	clrf	LATA
	clrf	LATB
	clrf	LATC
	clrf	LATD
	clrf	LATE

	call	InitLCD		; Initializes the LCD
	bsf	INTCON3, INT1IE
	bsf	INTCON2, INTEDG1 ; enable RB1 interrupts
	bsf	INTCON, GIE

	;; set all variables to zero
	call	menu_init
	call	menu_drawscreen
	goto	Mainline
	
	
Mainline
	
	goto	$
end
