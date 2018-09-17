#ifndef	INCLUDED_RENDERGAME_H
#define	INCLUDED_RENDERGAME_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderGame_Init( void );
void	RenderGame_DeInit( void );

void	RenderGame_GameInit( void );
void	RenderGame_LevelInit( void );
void	RenderGame_LevelDeInit( void );

void	RenderGame_Update( void );


/* ################################################################################ */

#endif	/*	INCLUDED_RENDERGAME_H	*/