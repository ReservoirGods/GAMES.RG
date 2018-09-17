#ifndef	INCLUDED_HISCORE_H
#define	INCLUDED_HISCORE_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dHISCORE_ENTRY_LIMIT	10


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eHISCORE_TABLE_A,
	eHISCORE_TABLE_B,

	eHISCORE_TABLE_LIMIT
};


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	char	Name[8];
	U32		Score;
} sHiScoreEntry;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void			HiScore_Init( void );
void			HiScore_DeInit( void );
void			HiScore_Main( void );

sHiScoreEntry *	HiScore_GetpEntry( const U16 aTableIndex, const U16 aEntryIndex );

U16				HiScore_GetActivatedFlag( void );
void			HiScore_SetActivatedFlag( const U16 aFlag );
void			HiScore_SetTableIndex( const U16 aIndex );
U16				HiScore_GetTableIndex( void );
void			HiScore_SetScore( const U16 aPlayerIndex, const U32 aScore );


/* ################################################################################ */

#endif	/*	INCLUDED_HISCORE_H	*/