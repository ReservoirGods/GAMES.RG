#ifndef	INCLUDED_BALLS_H
#define	INCLUDED_BALLS_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eBALLS_STATE_NORMAL,
	eBALLS_STATE_FALLING,
	eBALLS_STATE_DEAD,
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void		Balls_Init( void );
void		Balls_DeInit( void );
void		Balls_GameInit( void );
void		Balls_LevelInit( void );
void		Balls_Update( void );

U16			Balls_GetState( void );


/* ################################################################################ */

#endif	/*	INCLUDED_BALLS_H	*/