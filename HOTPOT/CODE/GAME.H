#ifndef	INCLUDED_GAME_H
#define	INCLUDED_GAME_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eGAME_STATE_STARTING,
	eGAME_STATE_PLAYING,
	eGAME_STATE_LOSING,
	eGAME_STATE_WINNING,
	eGAME_STATE_PAUSE,
	eGAME_STATE_EXIT,

	eGAME_STATE_LIMIT
};

enum
{
	eGAME_TYPE_PRACTICE,
	eGAME_TYPE_NORMAL,
	eGAME_TYPE_STAGE,
	eGAME_TYPE_TIME,
	eGAME_TYPE_PUZZLE,
	eGAME_TYPE_STORY,

	eGAME_TYPE_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Game_Init( void );
void	Game_DeInit( void );
void	Game_Main( void );

void	Game_Begin( void );
void	Game_DetermineHiScores( void );

U32		Game_GetPanelsToMake( void );
void	Game_SetPanelsToMake( const U32 aCount );

U16		Game_GetMode( void );
void	Game_SetMode( U16 aMode );

U32		Game_GetStage( void );
U16		Game_GetGameOverFlag( void );

U8		Game_GetQuitFlag( void );
U16		Game_GetStoryChapter( void );
void	Game_SetStoryChapter( const U16 aChapter );

U16		Game_GetWinner( void );


/* ################################################################################ */

#endif	/*	INCLUDED_GAME_H	*/