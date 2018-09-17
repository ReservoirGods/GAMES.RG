#ifndef	INCLUDED_DATALOG_H
#define	INCLUDED_DATALOG_H

/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\BASE\BASE.H>


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eDATALOG_CONTROL,

	eDATALOG_GAMETYPE,

	eDATALOG_HISCORE_NAME_A,
	eDATALOG_HISCORE_NAME_B,

	eDATALOG_KEYUP,
	eDATALOG_KEYDOWN,
	eDATALOG_KEYLEFT,
	eDATALOG_KEYRIGHT,
	eDATALOG_KEYFIRE,
	eDATALOG_KEYPAUSE,
	eDATALOG_KEYQUIT,

	eDATALOG_MUSICONFLAG,
	eDATALOG_SFXONFLAG,
	eDATALOG_SPEAKERONFLAG,

	eDATALOG_STATS_GAMETIME,

	eDATALOG_LIMIT
};


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct
{
	U16	Key;
	U32	Value;
} sDataLogEntry;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void			DataLog_Init( void );
void			DataLog_ReInit( void );
void			DataLog_DeInit( void );

#if	0

U32				DataLog_GetEntry( U16 aKey );
void			DataLog_SetEntry( U16 aKey, U32 aValue );

#else


#define			DataLog_GetEntry( aKey )			gDataLog[ aKey ].Value
#define			DataLog_SetEntry( aKey, aValue )	gDataLog[ aKey ].Value = aValue


extern	sDataLogEntry	gDataLog[ eDATALOG_LIMIT ];

#endif


/* ################################################################################ */

#endif	/*	INCLUDED_DATALOG_H	*/