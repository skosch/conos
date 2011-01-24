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

digit_1 res 1
digit_2	res 1
digit_3	res 1
digit_4 res 1
digit_5	res 1
digit_6 res 1


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
	movwf	LATA
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
	gtifz	menu_next
	movlw	15
	xorwf	key_pressed, w
	gtifz	menu_skip
	goto 	finish_interrupt
	endcase
	case 2
	;; Offset screen
	movlw	12
	xorwf	key_pressed,w	;*:Back
	gtifz	menu_twoback

	movlw	11
	xorwf	key_pressed, w
	gtifz	parameter_delete

	movlw	15
	xorwf	key_pressed, w
	gtifz	menu_next

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
	gtifz	stats_show_previous
	
	movlw	7
	xorwf	key_pressed,w
	gtifz	stats_show_next

	goto	finish_interrupt
	endcase
	case 8
	;; Settings screen
	movlw	14		;#:Date
	xorwf	key_pressed,w
	gtifz	menu_13

	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_1

	movlw	3		;A:Time
	xorwf	key_pressed,w
	gtifz	menu_14

	movlw	15		;D:Stats
	xorwf	key_pressed,w
	gtifz	menu_next

	goto	finish_interrupt
	endcase
	case 9
	;; Stats Selection (View or Delete)
	movlw	3
	xorwf	key_pressed,w
	gtifz	menu_10		;THIS COULD BE MENU_NEXT, BUT WE HAVE TO GO INTO STATS MODE

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
	gtifz	menu_11

	goto	finish_interrupt
	endcase
	case 11
	;; View data set
	movlw	12
	xorwf	key_pressed,w
	gtifz	menu_10

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
	
	endcase
	case 14
	;; Enter time
	endcase
	endselect
	
menu_default
	movf	PORTB, f

	goto	finish_interrupt



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

	movff	INDF0,LATC

	
	goto 	menu_drawscreen
	

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
	case	3
	lfsr	0, offset_bcd
	lfsr	1, param_offset
	endcase
	case	4
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
	

menu_drawscreen
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

	
	
	;; Congrats! By now, the standard content for each state should be written.
	
	select state
	case 	3		;add the offset value
	movlw 	0x87		;move the cursor behind the word "Offset:"
	call	CmdLCD

	call	print_param	;offset should still be in the FSR, so print_param can do its job
	movlw	0xD0
	call	CmdLCD		;put cursor away
	endcase
	case 	4			;add the interval value
	movlw	0x89			;	call	CmdLCD
	call	CmdLCD
	call	print_param
	movlw	0xD0
	call	CmdLCD		;put cursor away
	endcase
	endselect
	goto 	finish_interrupt

	
LCDTbl_1
	da "Welcome         ",0,"         Start:D",0
	da "       Options:A",0,"*:Back    Next:D",0
	da "Offset:_        ",0,"*:Back    Next:D",0
	da "Interval:_      ",0,"*:Back    Next:D",0
	da "Ready!          ",0,"*:Back   Start:D",0
	da "Deploying ...   ",0,"         Abort:C",0
	da "Done! Store&view",0,"*:End    stats:A",0
	da "   cm ( )  <>:AB",0,"*:End  TDist:   ",0

	da "#:Date    Time:A",0,"*:Back   Stats:D",0
	da "          View:A",0,"*:Back  Delete:B",0
	da "           <>:AB",0,"*:Back    View:D",0
	da "   cm ( )  <>:AB",0,"*:Back TDist:   ",0

	da "Del. all stats? ",0,"*:Back     Yes:A",0

	da "Enter Date:     ",0,"  /  /      OK:D",0
	da "Enter Time:     ",0,"  :         OK:D",0
	

	;; ****************************************
	;; Print_param prints the BCD value that's currently in the FSR to the LCD
	;; ****************************************
print_param
	;; first, find out where to put it
	;; if(PLUSW0 > 0) {
	;; write lower nibble of PLUSW0
	;; write upper nibble of INDF0
	;; write lower nibble of INDF0
	;; } else if(INDF0>15 and PLUSW==0) {
	;; write upper nibble of INDF0
	;; write lower nibble of INDF0
	;; write space
	;; } else if(INDF0>0 and PLUSW==0) {
	;; write lower nibble of INDF0
	;; write space
	;; write space
	;; } else if(INDF==0 and PLUSW==0){
	;; write 0
	;; write space
	;; write space
	;; }

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
	
	movlw	10
	mulwf	digit_2		;PROD=digit2*10

	movf	digit_1, w
	addwf	INDF1, f
	movf	PRODL, w
	addwfc	INDF1, f	;INDF1 is now digit1 + PRODL

	movlw	100
	mulwf	digit_3		;PROD=digit3*100

	movf	PRODL,w
	addwfc	INDF1,f		;add lower byte
	movf	PRODH,w
	addwf	PREINC1,f	;add upper byte to upper byte of INDF1

	
	return

	
	;; Congrats again! The display has been written! Go back and chill!

NumberToASCII
	;; add 48, because that's where the numbers start in ASCII
	movwf	tmp1
	movlw	0x30
	addwf	tmp1,w
	return

	;; ****************************************
	;; Show the next stat data set
	;; ****************************************
stats_show_next
	incf	stats_current_display, f
	movlw	1
	movwf	stats_mode	;display stat sets
	call	menu_drawscreen

	;; ****************************************
	;; Show the previous data set
	;; ****************************************
stats_show_previous
	decf	stats_current_display, f
	movlw	1
	movwf	stats_mode	;display stat sets
	call	menu_drawscreen




	
finish_interrupt
	bcf	INTCON3, INT1IF	;clear RB1 interrupt bit
	retfie
end