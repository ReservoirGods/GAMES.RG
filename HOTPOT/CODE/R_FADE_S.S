**************************************************************************************
*	R_FADE_S.S
*
*	interrupt based fade rout
*
*	[c] 2001 Reservoir Gods
**************************************************************************************

**************************************************************************************
;	EXPORTS / IMPORTS
**************************************************************************************

	export	RenderFade_Vbl

	import	Fade_PalSTE
	import	Video_SetNextPalST

	import	gRFadeVblActiveFlag
	import	gRFadeVblAdd
	import	gRFadeVblScale
	import	gpRFadeVblTmpPal
	import	gpRFadeVblOldPal
	import	gpRFadeVblTargetPal


**************************************************************************************
;	STRUCTS
**************************************************************************************



**************************************************************************************
	TEXT
**************************************************************************************

*------------------------------------------------------------------------------------*
* FUNCTION : RenderTile_PutTile( sBlitterSprite * apSprite, U16 * apScreen, U16 aX, U16 aY )
* ACTION   : interrupt at end of replay
* CREATION : 11.04.01 PNK
*------------------------------------------------------------------------------------*

RenderFade_Vbl:
	
	tst.b	gRFadeVblActiveFlag
	beq.s	.nofade

	tas.b	gRFadeVblLockFlag
	bne		.nofade

	movem.l	d0-a6,-(a7)

	move.l	gRFadeVblAdd,d0
	add.l	d0,gRFadeVblScale

	move.w	gRFadeVblScale,d1
	cmp.w	#$100,d1
	blt.s	.less
	move.w	#$100,d1
	clr.b	gRFadeVblActiveFlag
.less:

	move.l	gpRFadeVblTmpPal,a0
	move.l	gpRFadeVblOldPal,a1
	moveq	#16,d0
	move.l	gpRFadeVblTargetPal,-(a7)
	jsr		Fade_PalSTE
	addq.l	#4,a7

	move.l	gpRFadeVblTmpPal,a0
	jsr		Video_SetNextPalST

	movem.l	(a7)+,d0-a6
	clr.b	gRFadeVblLockFlag	

.nofade:
	rts

gRFadeVblLockFlag:	dc.b	0