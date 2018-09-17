/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"A_INTRO.H"

#include	"RESOURCE.H"

#include	"A_MUSIC.H"
#include	"A_SPL.H"

#include	<GODLIB\AUDIO\AMIXER.H>


/* ###################################################################################
#  DATA
################################################################################### */

sAudioDmaSound	gAIntroSounds[ eAINTRO_LIMIT ];

sTagString		gAIntroFileNames[ eAINTRO_LIMIT ] =
{
	{ eAINTRO_CHING,			"CHING.SPL"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8	AudioIntro_Load( void );
U8	AudioIntro_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_Init( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioIntro_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, AudioIntro_Load, AudioIntro_UnLoad );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_ReInit( void )
* ACTION   : called at end of app
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioIntro_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_IntroInit( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioIntro_IntroInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_LevelInit( void )
* ACTION   : called at start of level
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioIntro_LevelInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_Update( void )
* ACTION   : Audios all chus
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioIntro_Update( void )
{
	AudioMusic_Update();
	AudioSample_Update();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_PlaySample( const U16 aIndex )
* ACTION   : plays sample without queing
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioIntro_PlaySample( const U16 aIndex )
{
	AudioSample_PlaySampleDirect( &gAIntroSounds[ aIndex ], eASPL_PAN_CENTRE );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_Load( void )
* ACTION   : loads all samples for the game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioIntro_Load( void )
{
	U16		i;

	for( i=0; i<eAINTRO_LIMIT; i++ )
	{
		gAIntroSounds[ i ].mBits        = eAUDIO_BITS_8;
		gAIntroSounds[ i ].mFreq        = eAUDIO_FREQ_12;
		gAIntroSounds[ i ].mLength      = 0;
		gAIntroSounds[ i ].mLoopingFlag = 0;
		gAIntroSounds[ i ].mpSound      = 0;
		gAIntroSounds[ i ].mStereoFlag  = 0;

		gAIntroSounds[ i ].mLength = Resource_GetFileSize( sTagString_GetpString( i, &gAIntroFileNames[ 0 ], eAINTRO_LIMIT ) );
		gAIntroSounds[ i ].mpSound = Resource_Calloc( gAIntroSounds[ i ].mLength + 2048, 0 );
		Resource_LoadAt( sTagString_GetpString( i, &gAIntroFileNames[ 0 ], eAINTRO_LIMIT ), gAIntroSounds[ i ].mpSound );
	}

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioIntro_Load( void )
* ACTION   : unloads all samples for the game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioIntro_UnLoad( void )
{
	U16		i;

	for( i=0; i<eAINTRO_LIMIT; i++ )
	{
		Resource_Free( gAIntroSounds[ i ].mpSound );
	}

	return( 1 );
}


/* ################################################################################ */
