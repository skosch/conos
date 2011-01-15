LIST R=hex
INCLUDE "p16f877.inc"

__CONFIG _CP_OFF & _DEBUG_OFF &  _CPD_OFF & _LVP_OFF & _BODEN_OFF & _PWRTE_ON & _WDT_OFF & _XT_OSC

#include <lcd.inc>

	;; VARIABLE ALIAS DECLARATIONS ;; ******************************

org 0	;reset vector
goto Mainline


	;; ########################################
	;; INTERRUPT HANDLER
	;; ########################################
org 4
IHR
	;; insert interrupt code herep

RETFIE
	;; ########################################
	;; MAINLINE LOOP
	;; ########################################
Mainline
	;; Enable Interrupts
	bsf INTCON, GIE	;Global interrupt enable
	bsf INTCON, INTE ;RB0 interrupt enable
	bcf INTCON, INTF ;clear interrupt flag
	
	

	
end