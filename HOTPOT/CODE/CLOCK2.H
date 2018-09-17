#ifndef	INCLUDED_CLOCKS_H
#define	INCLUDED_CLOCKS_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>
#include	<GODLIB\MFP\MFP.H>
#include	<GODLIB\CLOCK\CLOCK.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eCLOCK_APP,
	eCLOCK_GAME,
	eCLOCK_LEVEL,
	eCLOCK_FE,

	eCLOCK_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */


void			Clocks_Init( void );
void			Clocks_DeInit( void );

void			Clocks_GameInit( void );
void			Clocks_GameDeInit( void );
void			Clocks_LevelInit( void );
void			Clocks_LevelDeInit( void );

void			Clocks_Update( void );

void			Clocks_StartClock( const U16 aClockIndex );
void			Clocks_StopClock( const U16 aClockIndex );
void			Clocks_PauseClock( const U16 aClockIndex );
void			Clocks_UnPauseClock( const U16 aClockIndex );
void			Clocks_StartCountDown( const U16 aClockIndex, const U8 aMins, const U8 aSecs );

extern	sClock		gClocks[ eCLOCK_LIMIT ];

#define			Clocks_GetState( aClockIndex )			gClocks[ aClockIndex ].mState
#define			Clocks_GetpElapsedTime( aClockIndex )	(&gClocks[ aClockIndex ].mElapsedTime)
#define			Clocks_GetpCountDownTime( aClockIndex )	(&gClocks[ aClockIndex ].mCountDownTime)
#define			Clocks_GetDuration( aClockIndex )		gClocks[ aClockIndex].mDuration
#define			Clocks_GetElapsedTicks( aClockIndex )	(gClocks[ aClockIndex].mElapsedTicks)


/* ################################################################################ */

#endif	/*	INCLUDED_CLOCKS_H	*/