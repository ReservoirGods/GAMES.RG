/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"DATALOG.H"
#include	"GAME.H"

#include	<GODLIB\ASSERT\ASSERT.H>
#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\INPUT\INPUT.H>


/* ###################################################################################
#  DATA
################################################################################### */

sDataLogEntry	gDataLog[ eDATALOG_LIMIT ];

sDataLogEntry	gDataLogFactorySettings[ eDATALOG_LIMIT ] =
{
	{	eDATALOG_CONTROL,			eINPUTTYPE_IKBD			},
	{	eDATALOG_GAMETYPE,			0						},
	{	eDATALOG_HISCORE_NAME_A,	mSTRING_TO_U32( 'P','L','A','Y' )	},
	{	eDATALOG_HISCORE_NAME_B,	mSTRING_TO_U32( 'E','R',' ','1' )	},
	{	eDATALOG_KEYUP,				eIKBDSCAN_UPARROW		},
	{	eDATALOG_KEYDOWN,			eIKBDSCAN_DOWNARROW		},
	{	eDATALOG_KEYLEFT,			eIKBDSCAN_LEFTARROW		},
	{	eDATALOG_KEYRIGHT,			eIKBDSCAN_RIGHTARROW	},
	{	eDATALOG_KEYFIRE,			eIKBDSCAN_SPACE			},
	{	eDATALOG_KEYPAUSE,			eIKBDSCAN_F1			},
	{	eDATALOG_KEYQUIT,			eIKBDSCAN_F10			},
	{	eDATALOG_MUSICONFLAG,		1						},
	{	eDATALOG_SFXONFLAG,			1						},
	{	eDATALOG_SPEAKERONFLAG,		0						},
	{	eDATALOG_STATS_GAMETIME,	0						},
};


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : DataLog_Init( void )
* ACTION   : called at start of app
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			DataLog_Init( void )
{
	U16	i;
	U16	lKey;

	for( i=0; i<eDATALOG_LIMIT; i++ )
	{
		lKey = gDataLogFactorySettings[ i ].Key;

		if( lKey < eDATALOG_LIMIT )
		{
			gDataLog[ lKey ].Value = gDataLogFactorySettings[ i ].Value;
		}
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : DataLog_DeInit( void )
* ACTION   : called at end of app
* CREATION : 26.01.01 PNK
*-----------------------------------------------------------------------------------*/

void			DataLog_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : DataLog_ReInit( void )
* ACTION   : called at start of level
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	DataLog_ReInit( void )
{
	DebugLog_Printf0( "DataLog_ReInit()\n" );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : DataLog_Clean( void )
* ACTION   : called at end of game
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	DataLog_Clean( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : DataLog_Update( void )
* ACTION   : called every game frame
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	DataLog_Update( void )
{
}


#if	0

/*-----------------------------------------------------------------------------------*
* FUNCTION : DataLog_GetEntry( U16 aKey )
* ACTION   : returns value of datalog entry aKey
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

U32				DataLog_GetEntry( U16 aKey )
{
	return( gDataLog[ aKey ].Value );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : DataLog_SetEntry( U16 aKey, U32 aValue )
* ACTION   : sets datalog entry aKey to aValue
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void			DataLog_SetEntry( U16 aKey, U32 aValue )
{
	gDataLog[ aKey ].Value = aValue;
}

#endif


/* ################################################################################ */
