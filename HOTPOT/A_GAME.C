/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"A_GAME.H"

#include	"BUILD.H"
#include	"PLAYER.H"
#include	"RESOURCE.H"

#include	"A_MUSIC.H"
#include	"A_SPL.H"

#include	<GODLIB\AUDIO\AMIXER.H>
#include	<GODLIB\AUDIO\AUDIO.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>


/* ###################################################################################
#  DATA
################################################################################### */

sAudioDmaSound	gAGameSounds[ eAGAME_LIMIT ];
U8				gAudioGamePanX[ 320 ];

sTagString		gAGameFileNames[ eAGAME_LIMIT ] =
{
	{	eAGAME_BALL_MOVE,		"MOVE.PCM"		},
	{	eAGAME_BALL_CATCH,		"CATCH2.PCM"	},
	{	eAGAME_BALL_DROP,		"GLASS.RAW"		},

};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8	AudioGame_Load( void );
U8	AudioGame_UnLoad( void );

void	AudioGame_splpan_CLI( const char * apArgs );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_Init( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioGame_Init( void )
{
	U16	i;
	U16	lPos;

	Resource_Attach( eSECTION_GLOBAL, AudioGame_Load, AudioGame_UnLoad );

	for( i=0; i<160; i++ )
	{
		gAudioGamePanX[ i ] = eASPL_PAN_LEFT;
	}
	for( i=160; i<320; i++ )
	{
		gAudioGamePanX[ i ] = eASPL_PAN_RIGHT;
	}

	for( i=54; i<245; i++ )
	{
		lPos  = (eASPL_PAN_RIGHT-eASPL_PAN_LEFT);
		lPos *= (i-54);
		lPos /= (245-54);
		lPos += eASPL_PAN_LEFT;
		gAudioGamePanX[ i ] = (U8)lPos;
	}

	Build_CliCmdInit( "splpan", AudioGame_splpan_CLI );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_ReInit( void )
* ACTION   : called at end of app
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioGame_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_GameInit( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioGame_GameInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_LevelInit( void )
* ACTION   : called at start of level
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioGame_LevelInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_Update( void )
* ACTION   : Audios all chus
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioGame_Update( void )
{
	AudioMusic_Update();
	AudioSample_Update();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_PlayFX( const U16 aIndex, const U16 aPriority )
* ACTION   : plays sound fx aIndex
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioGame_PlaySample( const U16 aIndex, const U16 aPriority, const U8 aPan )
{
	AudioSample_PlaySample( &gAGameSounds[ aIndex ], aPriority, aPan );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_PlayGameDirect( const U16 aIndex )
* ACTION   : plays sample without queing
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioGame_PlaySampleDirect( const U16 aIndex, const U8 aPan )
{
	AudioSample_PlaySampleDirect( &gAGameSounds[ aIndex ], aPan );
}

U8		AudioGame_GetPanX( const S16 aX )
{
	return( gAudioGamePanX[ aX ] );
}

#ifdef	dBUILD_CLI_ACTIVE

void	AudioGame_splpan_CLI( const char * apArgs )
{
	S32	lX;

	lX = Cli_GrabNumber( apArgs);

	if( (lX >=0) && (lX<320) )
	{
		AudioGame_PlaySampleDirect( eAGAME_BALL_MOVE, AudioGame_GetPanX( (S16)lX ) );
		Build_CliPrintfLine1( "pan %d", AudioGame_GetPanX( (S16)lX ) );
	}
}

#endif

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_Load( void )
* ACTION   : loads all samples for the game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioGame_Load( void )
{
	U16		i;

	for( i=0; i<eAGAME_LIMIT; i++ )
	{
		gAGameSounds[ i ].mBits        = eAUDIO_BITS_8;
		gAGameSounds[ i ].mFreq        = eAUDIO_FREQ_12;
		gAGameSounds[ i ].mLength      = 0;
		gAGameSounds[ i ].mLoopingFlag = 0;
		gAGameSounds[ i ].mpSound      = 0;
		gAGameSounds[ i ].mStereoFlag  = 0;

		gAGameSounds[ i ].mLength = Resource_GetFileSize( sTagString_GetpString( i, &gAGameFileNames[ 0 ], eAGAME_LIMIT ) );
		gAGameSounds[ i ].mpSound = Resource_Calloc( gAGameSounds[ i ].mLength + 2048, 0 );
		Resource_LoadAt( sTagString_GetpString( i, &gAGameFileNames[ 0 ], eAGAME_LIMIT ), gAGameSounds[ i ].mpSound );

		Audio_DmaScaleSignedVol( &gAGameSounds[ i ], 0x80 );
	}

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioGame_Load( void )
* ACTION   : unloads all samples for the game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioGame_UnLoad( void )
{
	U16		i;

	for( i=0; i<eAGAME_LIMIT; i++ )
	{
		Resource_Free( gAGameSounds[ i ].mpSound );
	}

	return( 1 );
}


/* ################################################################################ */
