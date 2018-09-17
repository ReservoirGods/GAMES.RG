#ifndef	INCLUDED_R_ENTRY_H
#define	INCLUDED_R_ENTRY_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	RenderEntry_Init( void );
void	RenderEntry_DeInit( void );
void	RenderEntry_GameInit( void );
void	RenderEntry_LevelInit( void );
void	RenderEntry_Update( void );

void	RenderEntry_Main( void );
char *	RenderEntry_GetpName( void );
void	RenderEntry_SetName( char * apName ); 


/* ################################################################################ */

#endif	/*	INCLUDED_R_ENTRY_H	*/