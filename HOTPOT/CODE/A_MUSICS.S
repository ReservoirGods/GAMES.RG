**************************************************************************************
*	A_MUSICS.S
*
*	sid sound player routs
*
*	[c] 2001 Reservoir Gods
**************************************************************************************

**************************************************************************************
;	EXPORTS / IMPORTS
**************************************************************************************

	export	AudioMusic_Start
	export	AudioMusic_Play
	export	AudioMusic_Stop

	export	AudioMusic_Hbl
	export	AudioMusic_HblDummy

	export	AudioMusic_Vbl

	export	gAudioMusicHblWait
	export	gAudioMusicHblWaitCounter

	export	gAudioMusicHblPerVbl
	export	gAudioMusicHblCallCounter
	export	gAudioMusicHblVblCounter

	import	gpAudioMusicReplay


**************************************************************************************
	TEXT
**************************************************************************************

*------------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_Start( U8 * apVoiceSet, U8 * apSong )
* ACTION   : starts a song
* CREATION : 10.01.01 PNK
*------------------------------------------------------------------------------------*

AudioMusic_Start:
	movem.l	d0-a6,-(a7)
	move.l	gpAudioMusicReplay,a2
	lea		0(a2),a2
	jsr		(a2)
	movem.l	(a7)+,d0-a6
	rts


*------------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_Play( void )
* ACTION   : interrupt based player
* CREATION : 10.01.01 PNK
*------------------------------------------------------------------------------------*

AudioMusic_Play:
	movem.l	d0-a6,-(a7)
	move.l	gpAudioMusicReplay,a0
	lea		4(a0),a0
	jsr		(a0)
	movem.l	(a7)+,d0-a6
	rts


*------------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_Stop( void )
* ACTION   : stops tune
* CREATION : 10.01.01 PNK
*------------------------------------------------------------------------------------*

AudioMusic_Stop:
	movem.l	d0-a6,-(a7)
	move.l	gpAudioMusicReplay,a0
	lea		8(a0),a0
	jsr		(a0)
	movem.l	(a7)+,d0-a6
	rts


AudioMusic_Vbl:
	movem.l	d0-d1,-(a7)

	move.l	gAudioMusicHblVblCounter,d0

	move.l	d0,d1
	sub.l	gAudioMusicHblCallCounter,d1
	sub.l	d1,gAudioMusicHblWaitCounter
	move.l	d0,gAudioMusicHblCallCounter

	add.l	gAudioMusicHblPerVbl,d0
	move.l	d0,gAudioMusicHblVblCounter

	movem.l	(a7)+,d0-d1
	rts

AudioMusic_Hbl:
	addq.l	#1,gAudioMusicHblCallCounter
	subq.l	#1,gAudioMusicHblWaitCounter
	bpl.s	.nomsx

	movem.l	d0-a6,-(a7)
	move.l	gAudioMusicHblWait,d0
	add.l	d0,gAudioMusicHblWaitCounter

	move.l	gpAudioMusicReplay,a0
	lea		4(a0),a0
	jsr		(a0)
	movem.l	(a7)+,d0-a6

.nomsx:

AudioMusic_HblDummy:
	rte

gAudioMusicHblPerVbl:		dc.l	0
gAudioMusicHblVblCounter:	dc.l	0
gAudioMusicHblCallCounter:	dc.l	0
gAudioMusicHblWaitCounter:	dc.l	0
gAudioMusicHblWait:			dc.l	0