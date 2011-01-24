list P=18F4620, F=INHX32, C=160, N=80, ST=OFF, MM=OFF, R=DEC
#include <p18f4620.inc>
#include <macros.inc>
#include <menu.inc>

extern state, cones_deployed, cones_remaining, cones_positions, cones_type, timestamp, dist_traveled, stats_current_display, stats_current_set, stats_mode, tmp1


	code
	global start_deployment, stop_deployment


start_deployment
	;; menu_drawscreen with "Deployed...", but don't do anything.
	;; fill the cones_deployed, cones_positions, cones_types, dist_traveled with stuff
	;; wait 2 seconds
	;; incf state
	;; call stop_deployment

	lfsr	0, timestamp	;TESTLINE: WRITE THE CURRENT TIME INTO THE TIMESTAMP REGISTER
	movlw	b'01010101'
	movwf	INDF0
	movlw	b'11110110'
	movwf	PREINC0

	lfsr	0, cones_positions
	lfsr	1, dist_traveled
	lfsr	2, cones_type

	
	incf	state,f
	call	menu_drawscreen

	movlw	8		;TESTLINE
	movwf	cones_deployed

	movlw	upper TblCones	;TESTLINE
	movwf	TBLPTRU
	movlw	high TblCones
	movwf	TBLPTRH
	movwf	low TblCones

	
	tblrd	*
copy_TblCones
	movwf	POSTINC0
	tblrd	+*
	bnz	copy_TblCones	;copy all the values of TblCones into cone_positions


	movlw	b'00101000'	;write 0000 0000 0010 1000 into the cone_type register
	movwf	INDF2
	movlw	0
	movwf	PREINC2

	movlw	84
	movwf	INDF1
	movlw	0
	movwf	PREINC1		;write 0000 0000 0000 0084 into the distance_traveled register



	;; all the values we need for one set of stats is now in the temp stats vars.
	
	;; here we have a delay of 3 seconds

	;; now we're done deploying and go to the next screen

	call stop_deployment
	
TblCones
	db 12, 22, 25, 35, 39, 49, 59, 69, 0
	
	

stop_deployment
	;; manu_drawscreen (show the success message)
	incf	state
	call	menu_drawscreen
	
end