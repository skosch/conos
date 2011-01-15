;*******************************************************************
; Keypad/LCD Test Code
; Assembler : mpasm.exe
; Linker    : mplink.exe
; Written By : Kevin Lam
;
; Notes: You may notice that this code uses unusual directives such
;        as 'code', 'udata_shr', 'global', 'extern', etc.
;        This is an example of a project implementing the concept of
;        'relocatable code'. The individual assembly files are
;        compiled into .o files, similar to what happens in C,
;        and then linked together at the end. In order to build
;        this kind of project, go to Project->Build Options->Project,
;        then under the MPASM tab, check "Use Alternate Settings"
;        and type /o in the corresponding textbox. You'll also need
;        to add an appropriate linker script to the project, which
;        can be found in MPLAB's program folder. The advantage of
;        using relocatable code, is that sets of functions can be
;        compiled as separate units into object files (or libraries)
;        and then imported into any other project, without worrying
;        about conflicting variables/code locations etc. This makes
;        modular programming easier in many cases.
;*******************************************************************

      list p=16f877                 ; list directive to define processor
      #include <p16f877.inc>        ; processor specific variable definitions
      __CONFIG _CP_OFF & _WDT_OFF & _BODEN_ON & _PWRTE_ON & _HS_OSC & _WRT_ENABLE_ON & _CPD_OFF & _LVP_ON

      #include <lcd.inc>			   ;Import LCD control functions from lcd.asm

         ORG       0x0000     ;RESET vector must always be at 0x00
         goto      init       ;Just jump to the main code section.
         
         code     ;'code' lets the linker decide where in
                  ;program memory to put these instructions.
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
          
         call      InitLCD    ;Initialize the LCD (code in lcd.asm; imported by lcd.inc)

test     btfss		PORTB,1     ;Wait until data is available from the keypad
         goto		$-1 

         swapf		PORTB,W     ;Read PortB<7:4> into W<3:0>
         andlw		0x0F
         call     KPHexToChar ;Convert keypad value to LCD character (value is still held in W)
         call     WR_DATA      ;Write the value in W to LCD

         btfsc		PORTB,1     ;Wait until key is released
         goto		$-1
         goto     test

KPHexToChar
          addwf     PCL,f
          dt        "123A456B789C*0#D"
	return

          END
