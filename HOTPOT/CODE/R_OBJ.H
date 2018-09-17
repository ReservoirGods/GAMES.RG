#ifndef	INCLUDED_R_OBJECTS_H
#define	INCLUDED_R_OBJECTS_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>

/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eROBJ_BALL,
	eROBJ_ARM_LEFT_0,
	eROBJ_ARM_LEFT_1,
	eROBJ_ARM_LEFT_2,
	eROBJ_ARM_RIGHT_0,
	eROBJ_ARM_RIGHT_1,
	eROBJ_ARM_RIGHT_2,
	eROBJ_EYE_0,
	eROBJ_EYE_1,
	eROBJ_EYE_2,
	eROBJ_LEG_LEFT_0,
	eROBJ_LEG_LEFT_1,
	eROBJ_LEG_RIGHT_0,
	eROBJ_LEG_RIGHT_1,
	eROBJ_BALL_CRACKED,
	eROBJ_BALL_SQUISHED,
	eROBJ_BUTTON,

	eROBJ_LIMIT
};

/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderObjects_Init( void );
void	RenderObjects_DeInit( void );
void	RenderObjects_GameInit( void );
void	RenderObjects_LevelInit( void );
void	RenderObjects_Update( void );

void	RenderObjects_Enable( void );
void	RenderObjects_Disable( void );

void *	RenderObjects_GetpBallSprite( void );

void *	RenderObjects_GetpObject( const U16 aIndex );

 
/* ################################################################################ */

#endif	/*	INCLUDED_R_OBJECTS_H	*/