#ifndef	INCLUDED_R_HISCORE_H
#define	INCLUDED_R_HISCORE_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderHiScore_Init( void );
void	RenderHiScore_DeInit( void );
void	RenderHiScore_GameInit( void );
void	RenderHiScore_LevelInit( void );
void	RenderHiScore_Update( void );

void	RenderHiScore_Main( const U16 aTableIndex );
 

/* ################################################################################ */

#endif	/*	INCLUDED_R_HISCORE_H	*/