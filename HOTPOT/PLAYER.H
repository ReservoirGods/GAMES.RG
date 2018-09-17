#ifndef	INCLUDED_PLAYER_H
#define	INCLUDED_PLAYER_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>

#include	<GODLIB\INPUT\INPUT.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	ePLAYER_POS_LEFT,
	ePLAYER_POS_MID,
	ePLAYER_POS_RIGHT,
};


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	U16		State;
	U16		Score;
	U16		Pos;
	S16		LeftDrain;
	S16		RightDrain;
	sInput	Input;
	sInput	InputB;
} sPlayer;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void		Player_Init( void );
void		Player_DeInit( void );
void		Player_GameInit( void );
void		Player_LevelInit( void );
void		Player_Update( void );

void		Player_InputUpdate( void );
void		Player_AddScore( U16 aScore );
sPlayer *	Player_GetpPlayer( void );
void		Player_CombinedInputUpdate( void );
sInput *	Player_GetpCombinedInput( void );

U16			Player_GetPos( void );


/* ################################################################################ */

#endif	/*	INCLUDED_PLAYER_H	*/