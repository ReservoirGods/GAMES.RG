/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"HISCORE.H"

#include	"DATALOG.H"
#include	"PLAYER.H"

#include	"R_ENTRY.H"
#include	"R_HISCOR.H"

#include	<STRING.H>


/* ###################################################################################
#  DATA
################################################################################### */

U16				gHiScoreTableIndex;
sHiScoreEntry	gHiScoreTables[ eHISCORE_TABLE_LIMIT ][ dHISCORE_ENTRY_LIMIT ];
U16				gHiScoreActivatedFlag;
U16				gHiScoreStage;
U32				gHiScorePlayerScore;

char *			gpHiScoreDefaultNames[ dHISCORE_ENTRY_LIMIT ] = 
{
	"SH3",
	"MSG",
	"PINK",
	"NEO",
	"GRIFF",
	"RIPLEY",
	"GRAHAM",
	"CHARLES",
	"TIM",
	"ARTO"
};

U32		gHiScoreDefaultScores[ dHISCORE_ENTRY_LIMIT ] =
{
	100L,
	90L,
	80L,
	70L,
	60L,
	50L,
	40L,
	30L,
	20L,
	10L,
};



/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	HiScore_InsertScoreEntry( const U16 aTableIndex, char * apName, const U32 aScore );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HiScore_Init( void )
{
	U16	i,j;

	for( i=0; i<eHISCORE_TABLE_LIMIT; i++ )
	{
		for( j=0; j<dHISCORE_ENTRY_LIMIT; j++ )
		{
			strcpy( &gHiScoreTables[ i ][ j ].Name[ 0 ], &gpHiScoreDefaultNames[ j ][ 0 ] );
			gHiScoreTables[ i ][ j ].Score = gHiScoreDefaultScores[ j ];
		}
	}

	gHiScorePlayerScore = 0;

	gHiScoreStage = 0;

	gHiScoreTableIndex    = 0;
	gHiScoreActivatedFlag = 0;

	RenderHiScore_Init();
	RenderEntry_Init();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HiScore_DeInit( void )
{
	RenderHiScore_DeInit();
	RenderEntry_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_Main( void )
* ACTION   : main hiscore loop
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HiScore_Main( void )
{
	U32		lName[ 2 ];
	char *	lpSrc;
	char *	lpDst;
	U16		j;

	lName[ 0 ] = DataLog_GetEntry( eDATALOG_HISCORE_NAME_A );
	lName[ 1 ] = DataLog_GetEntry( eDATALOG_HISCORE_NAME_B );

	gHiScoreTableIndex = (U16)DataLog_GetEntry( eDATALOG_GAMETYPE );

	if( Player_GetpPlayer()->Score > HiScore_GetpEntry( gHiScoreTableIndex, dHISCORE_ENTRY_LIMIT-1 )->Score )
	{
		RenderEntry_SetName( (char*)&lName[0] );
		RenderEntry_Main();
		HiScore_InsertScoreEntry( gHiScoreTableIndex, RenderEntry_GetpName(), Player_GetpPlayer()->Score );
		lpSrc = RenderEntry_GetpName();
		lpDst = (char*)&lName[ 0 ];
		for( j=0; j<8; j++ )
		{
			lpDst[ j ] = lpSrc[ j ];
		}
	}

	DataLog_SetEntry( eDATALOG_HISCORE_NAME_A, lName[ 0 ] );
	DataLog_SetEntry( eDATALOG_HISCORE_NAME_B, lName[ 1 ] );

	RenderHiScore_Main( gHiScoreTableIndex );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_GetpEntry( const U16 aTableIndex, const U16 aEntryIndex )
* ACTION   : returns pointer to entry in high score table
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

sHiScoreEntry *	HiScore_GetpEntry( const U16 aTableIndex, const U16 aEntryIndex )
{
	return( &gHiScoreTables[ aTableIndex ][ aEntryIndex ] );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_GetActivatedFlag( void )
* ACTION   : returns activated flag
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		HiScore_GetActivatedFlag( void )
{
	return( gHiScoreActivatedFlag );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_SetActivatedFlag( const U16 aFlag )
* ACTION   : sets activated flag
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HiScore_SetActivatedFlag( const U16 aFlag )
{
	gHiScoreActivatedFlag = aFlag;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_SetTableIndex( const U16 aIndex )
* ACTION   : sets table index for high score entry/display
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	HiScore_SetTableIndex( const U16 aIndex )
{
	gHiScoreTableIndex = aIndex;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : HiScore_GetTableIndex( void )
* ACTION   : returns table index for high score entry/display
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		HiScore_GetTableIndex( void )
{
	return( gHiScoreTableIndex );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void HiScore_SetScore(const U16 aPlayerIndex,const U32 aScore)
* ACTION   : HiScore_SetScore
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void HiScore_SetScore(const U16 aPlayerIndex,const U32 aScore)
{
	(void)aPlayerIndex;
	gHiScorePlayerScore = aScore;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void HiScore_InsertScoreEntry(const U16 aTableIndex,char * apName,const U32 aScore)
* ACTION   : HiScore_InsertScoreEntry
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void HiScore_InsertScoreEntry(const U16 aTableIndex,char * apName,const U32 aScore)
{
	S16	lIndex;
	S16	i;
	U16	j;

	lIndex = dHISCORE_ENTRY_LIMIT-1;

	while( (lIndex) && (gHiScoreTables[ aTableIndex ][ lIndex-1 ].Score < aScore) )
	{
		lIndex--;
	}

		
	for( i=(dHISCORE_ENTRY_LIMIT-1); i>lIndex; i-- )
	{
		gHiScoreTables[ aTableIndex ][ i ] = gHiScoreTables[ aTableIndex ][ i-1 ];
	}

	gHiScoreTables[ aTableIndex ][ lIndex ].Score = aScore;

	for( j=0; j<8; j++ )
	{
		gHiScoreTables[ aTableIndex ][ lIndex ].Name[ j ] = apName[ j ];
	}
}


/* ################################################################################ */
