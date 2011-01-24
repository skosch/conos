
	code
	global start_deployment


start_deployment
	;; menu_drawscreen with "Deployed...", but don't do anything.
	;; fill the cones_deployed, cones_positions, cones_types, dist_traveled with stuff
	;; wait 2 seconds
	;; incf state
	;; call stop_deployment

	incf	state,f
	call	menu_drawscreen

	movlw	8
	movwf	cones_deployed

	movlw	upper TblCones
	movwf	TBLPTRU
	movlw	high TblCones
	movwf	TBLPTRH
	movwf	low TblCones
	lfsr	0, cone_positions
	
	tblrd	*
copy_TblCones
	movwf	POSTINC0
	tblrd	+*
	bnz	copy_TblCones	;copy all the values of TblCones into cone_positions

	lfsr	0, cone_types	;copy the types deployed into cone_types
	movlw	b'00101000'
	movwf	INDF0
	movlw	0
	movwf	PREINC0

	lfsr	0, dist_traveled
	movlw	84
	movwf	INDF0
	movlw	0
	movwf	PREINC0

	lfsr	0, timestamp
	movlw	b'01010101'
	movwf	INDF0
	movlwf	b'11110110'
	movwf	PREINC0

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