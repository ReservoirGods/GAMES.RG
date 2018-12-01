/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"GAMESAVE.H"

#include	"DATALOG.H"
#include	"HISCORE.H"

#include	<GODLIB\FILE\FILE.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dGAMESAVE_ID		mSTRING_TO_U32( 'H', 'P', 'S', 'V' )
#define	dGAMESAVE_VERSION	11
#define	dGAMESAVE_ENCRYPTOR	0xF1E35D7C


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef struct
{
	U32				ID;
	U32				Version; 
} sGameSaveHeader;


typedef	struct
{
	U32				DataLog[ eDATALOG_LIMIT ];
	sHiScoreEntry	HiScoreTables[ eHISCORE_TABLE_LIMIT ][ dHISCORE_ENTRY_LIMIT ];
	U32				CheckSum;
} sGameSaveData;


typedef	struct
{
	sGameSaveHeader	Header;
	sGameSaveData	Data;
} sGameSave;


/* ###################################################################################
#  DATA
################################################################################### */

sGameSave	gGameSave;

U8			gGameSaveEncryptionKey[ 16 ] =
{
	0xF1,0xE3,0x5D,0x7C,
	0xB8,0x66,0xAA,0xCF,
	0x13,0x42,0x5E,0x87,
	0x01,0x2D,0x30,0xC4
};

/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	GameSave_Encrypt( sGameSave * apGame );
void	GameSave_Decrypt( sGameSave * apGame );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : GameSave_Load( void )
* ACTION   : loads save file
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	GameSave_Load( void )
{
	sFileHandle	lHandle;
	S32			lSize;
	U16			i,j;
	
	lHandle = File_Open( "HOTPOT.SAV" );
	if( File_HandleIsValid( lHandle ) )
	{
		lSize = File_Read( lHandle, sizeof(sGameSave), &gGameSave );		
		File_Close( lHandle );

		if( lSize == sizeof(sGameSave) )
		{
			if( (gGameSave.Header.ID == dGAMESAVE_ID) && (gGameSave.Header.Version == dGAMESAVE_VERSION) )
			{
				GameSave_Decrypt( &gGameSave );
				for( i=0; i<eDATALOG_LIMIT; i++ )
				{
					DataLog_SetEntry( i, gGameSave.Data.DataLog[ i ] );
				}
				for( i=0; i<eHISCORE_TABLE_LIMIT; i++ )
				{
					for( j=0; j<dHISCORE_ENTRY_LIMIT; j++ )
					{
						*HiScore_GetpEntry( i, j ) = gGameSave.Data.HiScoreTables[ i ][ j ];
					}
				}
			}
		}
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : GameSave_Save( void )
* ACTION   : saves game file
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	GameSave_Save( void )
{
	U16		i,j;

	gGameSave.Header.ID      = dGAMESAVE_ID;
	gGameSave.Header.Version = dGAMESAVE_VERSION;

	for( i=0; i<eDATALOG_LIMIT; i++ )
	{
		gGameSave.Data.DataLog[ i ] = DataLog_GetEntry( i );
	}
	for( i=0; i<eHISCORE_TABLE_LIMIT; i++ )
	{
		for( j=0; j<dHISCORE_ENTRY_LIMIT; j++ )
		{
			gGameSave.Data.HiScoreTables[ i ][ j ] = *HiScore_GetpEntry( i, j );
		}
	}

	GameSave_Encrypt( &gGameSave );
	File_Save( "HOTPOT.SAV", &gGameSave, sizeof(sGameSave) );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : GameSave_Encrypt( sGameSave * apGame )
* ACTION   : encrypts save file
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	GameSave_Encrypt( sGameSave * apGame )
{
	U32		lCheckSum;
	U8 *	lpData;
	U16		i,j;

	(void)apGame;
	lCheckSum = 0;
	lpData    = (U8*)&gGameSave.Data;
	for( i=0; i<sizeof(sGameSaveData)-4; i++ )
	{
		lCheckSum += lpData[ i ];
	}
	gGameSave.Data.CheckSum = lCheckSum;
	
	j = 3;
	for( i=0; i<sizeof(sGameSaveData); i++ )
	{
		lpData[ i ] ^= (gGameSaveEncryptionKey[ j&15 ]^(i&0xFF));
		j += i;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : GameSave_Decrypt( sGameSave * apGame )
* ACTION   : decrypts save file
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	GameSave_Decrypt( sGameSave * apGame )
{
	U8 *	lpData;
	U16		i,j;

	(void)apGame;
	lpData    = (U8*)&gGameSave.Data;
	
	j = 3;
	for( i=0; i<sizeof(sGameSaveData); i++ )
	{
		lpData[ i ] ^= (gGameSaveEncryptionKey[ j&15 ]^(i&0xFF));
		j += i;
	}

}


/* ################################################################################ */
