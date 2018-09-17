#ifndef	INCLUDED_R_BACKGROUND_H
#define	INCLUDED_R_BACKGROUND_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>

#include	<GODLIB\PICTYPES\DEGAS.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderBackGround_Init( void );
void	RenderBackGround_DeInit( void );
void	RenderBackGround_GameInit( void );
void	RenderBackGround_LevelInit( void );
void	RenderBackGround_Update( void );

void	RenderBackGround_FadeDown( void );
void	RenderBackGround_FadeUp( void );

sDegas *	RenderBackGround_GetpPic( void );

 
/* ################################################################################ */

#endif	/*	INCLUDED_R_BACKGROUND_H	*/