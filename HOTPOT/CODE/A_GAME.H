#ifndef	INCLUDED_A_GAME_H
#define	INCLUDED_A_GAME_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>

#include	<GODLIB\AUDIO\AUDIO.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eAGAME_BALL_MOVE,		
	eAGAME_BALL_CATCH,
	eAGAME_BALL_DROP,

	eAGAME_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	AudioGame_Init( void );
void	AudioGame_DeInit( void );
void	AudioGame_GameInit( void );
void	AudioGame_LevelInit( void );
void	AudioGame_Update( void );

void	AudioGame_PlaySample( const U16 aIndex, const U16 aPriority, const U8 aPan );
void	AudioGame_PlaySampleDirect( const U16 aIndex, const U8 aPan );

U8		AudioGame_GetTilePan( const U16 aBoardIndex, const U16 aTileCol );
U8		AudioGame_GetBoardPan( const U16 aBoardIndex );

U8		AudioGame_GetPanX( const S16 aX );

/* ################################################################################ */

#endif	/*	INCLUDED_A_GAME_H	*/ 