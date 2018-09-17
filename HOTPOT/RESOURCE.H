#ifndef	INCLUDED_RESOURCE_H
#define	INCLUDED_RESOURCE_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUM
################################################################################### */

enum
{
	eSECTION_NONE,
	eSECTION_INTRO,
	eSECTION_GLOBAL,

	eSECTION_LIMIT
};



/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	Resource_Init( void );
void	Resource_DeInit( void );

void	Resource_LogInit( void );
void	Resource_LogDeInit( void );
void	Resource_LogGenerate( void );

void	Resource_EnterSection( const U16 aSectionIndex );
void	Resource_LeaveSection( const U16 aSectionIndex );

U8		Resource_Attach( const U32 aSection, U8 (*fLoad)(void), U8	(*fUnLoad)(void) );

void *	Resource_Alloc(    const U32 aSize, const U8 aFastRamFlag );
void *	Resource_Calloc(    const U32 aSize, const U8 aFastRamFlag );
void *	Resource_Load(   char * apFileName, const U8 aFastRamFlag );
U8	 	Resource_LoadAt( char * apFileName, void * apAddress );
void	Resource_Free( void * apMem );
void	Resource_UnLoad( void * apMem );
S32		Resource_GetFileSize( char * apFileName );


/* ################################################################################ */

#endif	/*	INCLUDED_RESOURCE_H	*/