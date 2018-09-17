#ifndef	INCLUDED_R_PAUSE_H
#define	INCLUDED_R_PAUSE_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderPause_Init( void );
void	RenderPause_DeInit( void );
void	RenderPause_GameInit( void );
void	RenderPause_LevelInit( void );
void	RenderPause_Update( void );

void	RenderPause_Draw( void );
void	RenderPause_UnDraw( void );

void	RenderPause_Enable( void );
void	RenderPause_Disable( void );

 
/* ################################################################################ */

#endif	/*	INCLUDED_R_PAUSE_H	*/