list P=18F4620, F=INHX32, C=160, N=80, ST=OFF, MM=OFF, R=DEC
#include <p18f4620.inc>
#include <deploy.inc>
#include <lcd18.inc>
#include <macros.inc>
#include <main.inc>


extern state, param_offset, param_interval, dist_traveled, stats_mode, tmp1, stats_current_display

	
udata_acs
key_pressed res 1

offset_bcd res 2
interval_bcd res 2

d1 res 1
d2 res 1
d3 res 1
	
digit_1 res 1
digit_2	res 1
digit_3	res 1
digit_4 res 1
digit_5	res 1
digit_6 res 1

warning res 1


	code
	global menu_drawscreen, menu_handler, menu_init


	;; ****************************************
	;; menu_init is called from Init and clears all the variables used
	;; ****************************************

menu_init
	movlw	0
	movwf	state
	movwf	digit_1
	movwf	digit_2
	movwf	digit_3
	movwf	param_offset
	movwf	param_interval
	lfsr	0,offset_bcd
	movwf	INDF0
	movwf	PREINC0
	lfsr	0,interval_bcd
	movwf	INDF0
	movwf	PREINC0
	return
	
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
	return
	
KeyTbl	db 1, 2, 3, 0, 4, 5, 6, 0, 7, 8, 9, 0, 0, 0, 0, 0 ;the list of values
	


	;; ****************************************
	;; Menu Handler: Takes care of navigation through the menu
	;; ****************************************
menu_handler
	swapf	PORTB,W		;read PortB<7:4> into W<3:0>
	andlw	0x0F		;mask the lower nibble;
	;; here was a rlncf wreg, w to count the program memory up by two, no idea.
	movwf	key_pressed

	select state
	case 0
		;Welcome screen
	movf	key_pressed, w
	xorlw	0xF	;D:Next

	gtifz	menu_next ;
	goto	finish_interrupt
	endcase
	case 1
		  ;Options screen
	movlw	0	;might go to offset screen, clear digits just to be sure
	movwf	digit_1
	movwf	digit_2
	movwf	digit_3
	
	movlw	12
	xorwf	key_pressed, w
	gtifz	menu_back ;*:Back
	movlw	3
	xorwf	key_pressed, w
	gtifz	menu_1to8
	movlw	15
	xorwf	key_pressed, w
	gtifz	menu_next
	goto 	finish_interrupt
	endcase
	case 2
	;; Offset screen
	movlw	12
	xorwf	key_pressed,w	;*:Back
	gtifz	menu_back

	movlw	11
	xorwf	key_pressed, w
	gtifz	parameter_delete

	movlw	15
	xorwf	key_pressed, w
	gtifz	menu_3

	;; test for other keys AB#:
	movlw	3
	xorwf	key_pressed, w
	gtifz	finish_interrupt
	movlw	7
	xorwf	key_pressed, w
	gtifz	finish_interrupt
	movlw	14
	xorwf	key_pressed, w
	gtifz	finish_interrupt

	;; otherwise, it's a number key. 
	goto	parameter_append
	endcase
	case 3
	;; Interval Screen
	movlw	12
	xorwf	key_pressed,w	;*:Back
	gtifz	menu_back

	movlw	11
	xorwf	key_pressed,w
	gtifz	parameter_delete
	
	movlw	15
	xorwf	key_pressed,w
	gtifz	menu_next	

	;; test for other keys AB#:
	movlw	3
	xorwf	key_pressed,w
	gtifz	finish_interrupt
	movlw	7
	xorwf	key_pressed,w
	gtifz	finish_interrupt
	movlw	14
	xorwf	key_pressed,w
	gtifz	finish_interrupt

	;; otherwise, it's a number key. append.
	goto	parameter_append
	endcase
	case 4
	;; READY!
	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_back

	movlw	15
	xorwf	key_pressed,w
	gtifz	start_deployment ;THIS IS WHERE THE ACTUAL DELPLOYMENT STARTS!

	goto	finish_interrupt
	endcase
	case 5
	;; Deploying ...
	movlw	11		;C:Abort
	xorwf	key_pressed,w
	gtifz	menu_back	;THIS IS WHEN THE ACTUAL DEPLOYMENT IS ABORTED!

	movlw	15		;THIS IS JUST FOR NOW, TO TEST NAVIGATIONZ!
	xorwf	key_pressed,w
	gtifz	menu_next
	
	goto	finish_interrupt
	endcase
	case 6
	;; Success Screen
	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_start	;go back to start screen

	movlw	3
	xorwf	key_pressed,w
	gtifz	menu_next	;start stats screen
	goto	finish_interrupt
	endcase
	case 7
	;; Stats screen after deployment
	movlw	12
	xorwf	key_pressed,w	;go back to start screen
	gtifz	menu_start

	movlw	3
	xorwf	key_pressed,w
	gtifz	stats_show_previous_cone
	
	movlw	7
	xorwf	key_pressed,w
	gtifz	stats_show_next_cone

	goto	finish_interrupt
	endcase
	case 8
	;; Settings screen
	movlw	14		;#:Date
	xorwf	key_pressed,w
	gtifz	menu_8to13

	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_1

	movlw	3		;A:Time
	xorwf	key_pressed,w
	gtifz	menu_8to14

	movlw	15		;D:Stats
	xorwf	key_pressed,w
	gtifz	menu_next

	goto	finish_interrupt
	endcase
	case 9
	;; Stats Selection (View or Delete)
	movlw	3
	xorwf	key_pressed,w
	gtifz	menu_9to10		;THIS COULD BE MENU_NEXT, BUT WE HAVE TO GO INTO STATS MODE

	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_back

	movlw	7		;B:Delete
	xorwf	key_pressed,w
	gtifz	menu_12		;Delete window

	goto	finish_interrupt
	endcase
	case 10
	;; Set Selection
	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_9

	movlw	3		;A: Show next set
	xorwf	key_pressed,w
	gtifz	stats_show_next_set

	movlw	7
	xorwf	key_pressed,w
	gtifz	stats_show_previous_set

	movlw	15		;D: View Set data
	xorwf	key_pressed,w
	gtifz	menu_10to11

	goto	finish_interrupt
	endcase
	case 11
	;; View data set
	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_11to10

	movlw	3		;A: Show next cone
	xorwf	key_pressed,w
	gtifz	stats_show_next_cone

	movlw	7
	xorwf	key_pressed,w
	gtifz	stats_show_previous_cone

	goto	finish_interrupt
	endcase
	case 12
	;; Delete all data?
	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_9

	movlw	3
	xorwf	key_pressed,w
	gtifz	menu_delete_data

	goto	finish_interrupt
	endcase
	case 13
	;; Enter date
	movlw	15
	xorwf	key_pressed, w
	gtifz	menu_13to8

	;; test for other keys AB#:
	movlw	3
	xorwf	key_pressed, w
	gtifz	finish_interrupt
	movlw	7
	xorwf	key_pressed, w
	gtifz	finish_interrupt
	movlw	14
	xorwf	key_pressed, w
	gtifz	finish_interrupt

	;; otherwise, it's a number key. 
	goto	date_append
	endcase
	case 14
	;; Enter time
	movlw	15
	xorwf	key_pressed, w
	gtifz	menu_14to8

	;; test for other keys AB#:
	movlw	3
	xorwf	key_pressed, w
	gtifz	finish_interrupt
	movlw	7
	xorwf	key_pressed, w
	gtifz	finish_interrupt
	movlw	14
	xorwf	key_pressed, w
	gtifz	finish_interrupt

	;; otherwise, it's a number key. 
	goto	time_append
	endcase
	endselect
	
menu_default
	movf	PORTB, f

	goto	finish_interrupt


date_append
	;; appends a digit to the date
	goto	menu_drawscreen

time_append
	;; appends a digit to the time
	goto	menu_drawscreen

	;; ****************************************
	;; Adds an offset or interval character and updates the display
	;; ****************************************
parameter_append
	call	KPHexToInt
	movwf	key_pressed
	;; rotate left by 4 bits to make room for the new digit
	clrf	PREINC0
	movf	POSTDEC0,f
	swapf	INDF0, w	;take nibble two and put it into w
	andlw	0xF
	movwf	PREINC0		;and make it the new highest nibble
	movf	POSTDEC0, f

	movf	INDF0, w	;clear what used to be the middle nibble
	andlw	0xF		;now take the lowest nibble
	swapf	WREG, w		;put it in the high position
	movwf	INDF0	

	movf	key_pressed,w
	iorwf	INDF0,f



	
n	goto 	menu_drawscreen
	

	;; ****************************************
	;; Deletes an offset or interval character and updates the display
	;; ****************************************
parameter_delete
	swapf	INDF0, f
	movf	INDF0,w
	andlw	0xF
	movwf	INDF0

	movf	PREINC0,w
	andlw	0xF
	swapf	WREG, w
	movwf	POSTDEC0

	movf	INDF0, w
	iorwf	PREINC0,w	;TEST
	movf	POSTDEC0, f
	movwf	INDF0

	clrf	PREINC0
	movf	POSTDEC0, f
	
	goto menu_drawscreen	;just in case.

	;; ****************************************
	;; Go back to welcome screen
	;; ****************************************
menu_start
	goto	Init		;calls Init, which clears everthing and calls
				;menu_drawscreen, which calls finish_interrupt.

	;; ****************************************
	;; Increases the state counter and draws the screen
	;; ****************************************
menu_next
	incf	state, f
	call	menu_prepareforinput
	goto	menu_drawscreen

	;; ****************************************
	;; Decreases the state counter and draws the screen
	;; ****************************************
menu_back
	decf	state, f
	call	menu_prepareforinput
	goto	menu_drawscreen

	;; ****************************************
	;; Deletes leftover BCD digits and makes sure the address pointers are right
	;; ****************************************
menu_prepareforinput
	movlw	0
	movwf	digit_1
	movwf	digit_2
	movwf	digit_3
	select	state
	case	2
	lfsr	0, offset_bcd
	lfsr	1, param_offset
	endcase
	case	3
	lfsr	0, interval_bcd
	lfsr	1, param_interval
	endcase
	endselect
	return

	;; ****************************************
	;; Decreases the state counter and draws the screen
	;; ****************************************
menu_twoback
	decf	state, f
	decf	state, f
	goto	menu_drawscreen
	
	;; ****************************************
	;; Increases the state counter by two and draws the screen
	;; ****************************************
menu_skip
	incf	state, f
	incf	state, f
	call	menu_prepareforinput
	goto	menu_drawscreen
	

	;; ****************************************
	;; GOTO MENU_3 (OFFSET SCREEN->INTERVAL SCREEN)
	;; ****************************************
menu_3
	;; if param is > 300, issue warning; otherwise, goto interval

	movf	param_offset+1,w ;put the high byte of param_offset into w
	sublw	1		 ;subtract 1, which is the bit for 256
	skpz			 ;if its bigger than 256, keep testing
	goto	results16	 
	movf	param_offset,w	;put the low byte of param_offset into w
	sublw	low .300	;subtract the low byte of 300
results16
	skpc			;if we're over, issue a warning, if not skip.
	goto	issue_warning
	goto	menu_next


	;; ****************************************
	;; GOTO MENU_4 (INTERVAL SCREEN)
	;; ****************************************

menu_4
	movf	param_interval, w
	sublw	300
	btfsc	STATUS, N
	goto	issue_warning
	movf	param_interval, w
	sublw	25
	btfss	STATUS, N
	goto	issue_warning
	goto	menu_next

menu_1to8
	movlw	7
	movwf	state
	goto	menu_next

menu_13to8
	;; check wether the date is in the right format, otherwise issue_Warning
	goto	menu_1to8

menu_14to8
	;; check whether the time is in the right format, otherwise issue_warning
	goto	menu_1to8


menu_9to10
	;; set up the stats_set stuff, then display the set select screen
	goto	menu_next

	
menu_10to11
	;; pick the right set, the display the stats screen
	goto	menu_next

menu_11to10
	;; set up the stats_set stuff, and be at the same set as we just viewed
	goto	menu_back

menu_12
	movlw	11
	movwf	state
	goto	menu_next

menu_9
	movlw	8
	movwf	state
	goto	menu_next

menu_8to14
	;; read the current time into the time_digit registers
	movlw	13
	movwf	state
	goto	menu_next

menu_8to13
	;; read the current date into the date_digit registers
	movlw	12
	movwf	state
	goto	menu_next

menu_1
	movlw	0
	movwf	state
	goto	menu_next
	
menu_drawscreen
	;; if warning is set to true, add 12 to the state register.
	;; then just keep going. at the end of the routine, if warning = 1, the routine will wait for 2 seconds, set warning to zero, subtract 12 from the state register, and call itself again to redraw the original screen, and then go to Mainline again.

	btfsc	warning,0
	call	activate_warning
	
	;;  first, load the tablepointer to the tables and write the first and
	;;  second line to the display.
	;;  then, take care of inserting the current variable values.
	call	InitLCD
	movlw	upper LCDTbl_1
	movwf	TBLPTRU
	movlw	high LCDTbl_1
	movwf	TBLPTRH
	
	movlw	36
	mulwf	state 		;now tmp1 = state * 16
	;; now result is in PRODH and PRODL
	;; first, add PRODL to low LCDTbl_1 and carry up the result.
		
	movlw	low LCDTbl_1
	addwf	PRODL, W  ;add the key offset*16 to the lower end of the table 
	
	movwf	TBLPTRL
	movlw	0
	addwfc	TBLPTRH, F	;let the carry ripple up if we went too far
	addwfc	TBLPTRU, F

	;; now add PRODH to high LCDTbl_1 and carry up the result to upper.

	movf	TBLPTRH, w
	addwf	PRODH, w
	movwf	TBLPTRH
	movlw	0
	addwfc	TBLPTRU
	
	tblrd	*		;read that thing into the latch
	movf	TABLAT, W	;put it into W

NextChar_1
	call	WrtLCD		;loop through the table entry until 0 is hit
	tblrd	+*
	movf	TABLAT,W
	bnz	NextChar_1

	movlw	0xC0		;position cursor at second line. 0x80 + 0x40 = 0xC0
	call	CmdLCD

	tblrd	+*
	tblrd	+*
	movf	TABLAT,W
	
NextChar_2
	call	WrtLCD		;loop through the table entry until 0 is hit
	tblrd	+*
	movf	TABLAT,W
	bnz	NextChar_2	

	;; if we were tricked into displaying a warning message, goto deactivate_warning to go back to our actual thing.

	btfsc	warning,0 
	goto	deactivate_warning
	
	;; Congrats! By now, the standard content for each state should be written.

	;; GO ON TO WRITE THE SPECIAL PARTS
	select state
	
	case 	2		;add the offset value
	movlw 	0x87		;move the cursor behind the word "Offset:"
	call	CmdLCD
	call	print_param	;offset should still be in the FSR for print_param to use
	movlw	0xD0
	call	CmdLCD		;put cursor away
	endcase
	
	case 	3			;add the interval value
	movlw	0x89			;	call	CmdLCD
	call	CmdLCD
	call	print_param
	movlw	0xD0
	call	CmdLCD		;put cursor away
	endcase

	case	7
	;; display the last stats
	endcase

	case	10
	;; display the stat set selection
	endcase

	case	11
	;; display the stats from the selected set
	endcase

	case	13
	;; display the time entering stuff
	endcase

	case	14
	;; display the date entering stuff
	endcase
	
	endselect
	goto 	finish_interrupt

	
LCDTbl_1
	da "Welcome         ",0,"         Start:D",0 ;0
	da "       Options:A",0,"*:Back    Next:D",0 ;1
	da "Offset:_        ",0,"*:Back    Next:D",0 ;2
	da "Interval:_      ",0,"*:Back    Next:D",0 ;3
	da "Ready!          ",0,"*:Back   Start:D",0 ;4
	da "Deploying ...   ",0,"         Abort:C",0 ;5
	da "Done! Store&view",0,"*:End    stats:A",0 ;6
	da "   cm ( )  <>:AB",0,"*:End  TDist:   ",0 ;7

	da "#:Date    Time:A",0,"*:Back   Stats:D",0 ;8
	da "          View:A",0,"*:Back  Delete:B",0 ;9
	da "           <>:AB",0,"*:Back    View:D",0 ;10
	da "   cm ( )  <>:AB",0,"*:Back TDist:   ",0 ;11

	da "Del. all stats? ",0,"*:Back     Yes:A",0 ;12

	da "Enter Date:     ",0,"  /  /      OK:D",0 ;13
	da "Enter Time:     ",0,"  :         OK:D",0 ;14

	;; table continues with warning messages

	da "Offset must be  ",0,"<300 cm         ",0 ;15
	da "Interval must be",0,"<300 and >25 cm ",0 ;16


	da "                ",0,"                ",0
	da "                ",0,"                ",0
	da "                ",0,"                ",0
	da "                ",0,"                ",0
	da "                ",0,"                ",0
	da "                ",0,"                ",0
	da "                ",0,"                ",0
	da "                ",0,"                ",0

	da "All stats       ",0,"deleted!        ",0 ;25
	da "Invalid date!   ",0,"Use MM/DD/YY    ",0 ;26
	da "Invalid time!   ",0,"Use HH:MM       ",0 ;27


	;; ****************************************
	;; activate_warning adds 13 to the state register to access the warning messages
	;; in the table.
	;; ****************************************
	
activate_warning
	movf	state, w
	addlw	13
	movwf	state
	return

deactivate_warning
	movf	state, w
	addlw	256-13
	movwf	state
	bcf	warning,0
	movlw	0
	;; HERE, DELAY FOR 1.8 SECONDS, abusing the digit registers as counters
	call	Delay18

	;; if we just deleted all the data, don't go back but go back two
	select state
	case 12
	movlw	9
	movwf	state
	endcase
	endselect
	
	goto	menu_drawscreen	;go back to the "real" screeen
	

	;; ****************************************
	;; Print_param prints the BCD value that's currently in the FSR to the LCD
	;; ****************************************
print_param



	movf	PREINC0, w	;	movf	POSTDEC0,f
	bz	print_param_twodigits ;do the following if there are three digits
	
	
	andlw	0xF		      ;take the lower nibble
	movwf	digit_3
	call	NumberToASCII
	call	WrtLCD

	movf	POSTDEC0,f
	movf	INDF0,w
	andlw	0xF0
	movwf	digit_2		;the second digit was in the upper nibble, but that 
	swapf	digit_2,f
	movf	digit_2,w
	call	NumberToASCII
	call	WrtLCD
	
	movf	INDF0,w
	andlw	0xF
	movwf	digit_1
	call	NumberToASCII
	call	WrtLCD

	goto	print_param_store
	
print_param_twodigits
	;; If indf0>15
	movf	POSTDEC0, f	;go back to the lower byte
	movff	INDF0,tmp1	;and copy it to W to see whats up
	swapf	tmp1,w
	andlw	0xF
	bz	print_param_onedigit

	movlw	32
	call	WrtLCD		;print one space, this is digit 3
	movlw	0
	movwf	digit_3
	
	movf	INDF0,w
	andlw	0xF0
	movwf	digit_2		;the second digit was in the upper nibble, but that 
	swapf	digit_2,f
	movf	digit_2, w
	call	NumberToASCII
	call	WrtLCD
	
	movf	INDF0,w
	andlw	0xF
	movwf	digit_1
	call	NumberToASCII
	call	WrtLCD

	goto	print_param_store
	
print_param_onedigit
	;; If indf0<b1111
	movf	INDF0, f
	bz	print_param_zero

	movlw	0
	movwf	digit_3
	movwf	digit_2

	movlw	32
	call	WrtLCD
	movlw	32
	call	WrtLCD
	
	movf	INDF0, w
	andwf	0xF
	movwf	digit_1
	call	NumberToASCII
	call	WrtLCD

	goto	print_param_store

	
print_param_zero
	movlw	32
	call	WrtLCD
	movlw	32
	call	WrtLCD
	
	movlw	0		;print 0[space][space]
	movwf	digit_3
	movwf	digit_2
	movwf	digit_1

	movlw	0x30
	call	WrtLCD		;test!
	goto	print_param_store
	
print_param_store
	;; take digits 1, 2, and 3 and store them as an actual number in FSR1.
	clrf	INDF1		;clear the register
	clrf	PREINC1
	movf	POSTDEC1, f
	clrf	PRODL
	clrf	PRODH
	
	movlw	10
	mulwf	digit_2		;PROD=digit2*10

	movf	digit_1, w
	addwf	INDF1, f
	movf	PRODL, w
	addwfc	INDF1, f	;INDF1 is now digit1 + PRODL

	movlw	100
	mulwf	digit_3		;PROD=digit3*100

	movf	PRODL,w
	addwf	INDF1,f		;add lower byte
	movf	PRODH,w
	addwfc	PREINC1,f	;add upper byte to upper byte of INDF1
	movf	POSTDEC1, f


	movff	INDF1, LATC
	movff	PREINC1, LATA
	movf	POSTDEC1, f
	


	return

	
	;; Congrats again! The display has been written! Go back and chill!

NumberToASCII
	;; add 48, because that's where the numbers start in ASCII
	movwf	tmp1
	movlw	0x30
	addwf	tmp1,w
	return

issue_warning
	bsf	warning,0
	goto	menu_drawscreen


	;; ****************************************
	;; Show the next stat data set
	;; ****************************************
stats_show_next_cone
	incf	stats_current_display, f
	movlw	1
	movwf	stats_mode	;display stat sets
	call	stats_show_cone

	;; ****************************************
	;; Show the previous data set
	;; ****************************************
stats_show_previous_cone
	decf	stats_current_display, f
	movlw	1
	movwf	stats_mode	;display stat sets
	call	stats_show_cone

stats_show_cone
	;; here's where the cone is actually put on the LCD.
	goto	finish_interrupt

	
stats_show_next_set
	;; rotate through the sets
	goto	finish_interrupt

stats_show_previous_set
	;; rotate through the sets
	goto	finish_interrupt

stats_show_set
	;; here's where the set is actually put on the LCD
	goto	finish_interrupt

menu_delete_data
	;; deletes all stats on the EEPROM
	goto	issue_warning
	goto	finish_interrupt
	
finish_interrupt
	bcf	INTCON3, INT1IF	;clear RB1 interrupt bit
	retfie


Delay18
	
			;4499990 cycles
	movlw	0x27
	movwf	d1
	movlw	0xD0
	movwf	d2
	movlw	0x0A
	movwf	d3
	
Delay_0
	decfsz	d1, f
	bra	Delay_1
	decfsz	d2, f
Delay_1
	bra	Delay_2
	decfsz	d3, f
Delay_2
	bra	Delay_0

				;6 cycles
			;4 cycles (including call)
	return





end