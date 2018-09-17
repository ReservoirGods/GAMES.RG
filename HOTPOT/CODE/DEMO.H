#ifndef	INCLUDED_DEMO_H
#define	INCLUDED_DEMO_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Demo_Init( void );
void	Demo_DeInit( void );
void	Demo_Main( void );

U16		Demo_GetActivatedFlag( void );
void	Demo_SetActivatedFlag( const U16 aFlag );


/* ################################################################################ */

#endif	/*	INCLUDED_DEMO_H	*/