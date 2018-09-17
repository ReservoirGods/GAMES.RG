#ifndef	INCLUDED_HOTPOT_KERNEL_H
#define	INCLUDED_HOTPOT_KERNEL_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eKERNELSTATE_INTRO,
	eKERNELSTATE_FRONTEND,
	eKERNELSTATE_DEMO,
	eKERNELSTATE_GAME,
	eKERNELSTATE_HIGHSCORES,
	eKERNELSTATE_EXIT,

	eKERNELSTATE_LIMIT
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	HotPotKernel_Init( void );
void	HotPotKernel_DeInit( void );
void	HotPotKernel_Main( void );

void	HotPotKernel_RequestShutdown( void );


/* ################################################################################ */

#endif	/*	INCLUDED_KERNEL_H	*/