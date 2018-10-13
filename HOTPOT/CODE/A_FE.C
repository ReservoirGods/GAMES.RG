/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"A_FE.H"

#include	"RESOURCE.H"

#include	"A_MUSIC.H"
#include	"A_SPL.H"

#include	<GODLIB\AUDIO\AMIXER.H>
#include	<GODLIB\AUDIO\AUDIO.H>


/* ###################################################################################
#  DATA
################################################################################### */

sAudioDmaSound	gAFrontEndSounds[ eAFRONTEND_LIMIT ];

sTagString		gAFrontEndFileNames[ eAFRONTEND_LIMIT ] =
{
	{	eAFRONTEND_CURSOR_MOVE,			"MOVE.PCM"	},
	{	eAFRONTEND_MENU_ENTER,			"CATCH2.PCM"	},
	{	eAFRONTEND_MENU_LEAVE,			"CATCH2.PCM"	},
	{	eAFRONTEND_ITEM_SELECT,			"MOVE.PCM"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8	AudioFrontEnd_Load( void );
U8	AudioFrontEnd_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_Init( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioFrontEnd_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, AudioFrontEnd_Load, AudioFrontEnd_UnLoad );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_ReInit( void )
* ACTION   : called at end of app
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioFrontEnd_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_FrontEndInit( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioFrontEnd_FrontEndInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_LevelInit( void )
* ACTION   : called at start of level
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioFrontEnd_LevelInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_Update( void )
* ACTION   : Audios all chus
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioFrontEnd_Update( void )
{
	AudioMusic_PlayTune( eAMUSIC_VOICESET_GENERAL, eAMUSIC_SONG_MAIN );
	AudioMusic_Update();
	AudioSample_Update();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_PlayFX( const U16 aIndex, const U16 aPriority )
* ACTION   : plays sound fx aIndex
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioFrontEnd_PlayFrontEnd( const U16 aIndex, const U16 aPriority, const U8 aPan )
{
	AudioSample_PlaySample( &gAFrontEndSounds[ aIndex ], aPriority, aPan );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_PlayFrontEndDirect( const U16 aIndex )
* ACTION   : plays sample without queing
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioFrontEnd_PlaySampleDirect( const U16 aIndex, const U8 aPan )
{
	AudioSample_PlaySampleDirect( &gAFrontEndSounds[ aIndex ], aPan );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_Load( void )
* ACTION   : loads all samples for the game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioFrontEnd_Load( void )
{
	U16		i;

	for( i=0; i<eAFRONTEND_LIMIT; i++ )
	{
		gAFrontEndSounds[ i ].mBits        = eAUDIO_BITS_8;
		gAFrontEndSounds[ i ].mFreq        = eAUDIO_FREQ_12;
		gAFrontEndSounds[ i ].mLength      = 0;
		gAFrontEndSounds[ i ].mLoopingFlag = 0;
		gAFrontEndSounds[ i ].mpSound      = 0;
		gAFrontEndSounds[ i ].mStereoFlag  = 0;

		gAFrontEndSounds[ i ].mLength = Resource_GetFileSize( sTagString_GetpString( i, &gAFrontEndFileNames[ 0 ], eAFRONTEND_LIMIT ) );
		gAFrontEndSounds[ i ].mpSound = Resource_Calloc( gAFrontEndSounds[ i ].mLength + 2048, 0 );
		Resource_LoadAt( sTagString_GetpString( i, &gAFrontEndFileNames[ 0 ], eAFRONTEND_LIMIT ), gAFrontEndSounds[ i ].mpSound );
		Audio_ScaleVolumeSigned( &gAFrontEndSounds[ i ], 0x80 );
	}

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioFrontEnd_Load( void )
* ACTION   : unloads all samples for the game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioFrontEnd_UnLoad( void )
{
	U16		i;

	for( i=0; i<eAFRONTEND_LIMIT; i++ )
	{
		Resource_Free( gAFrontEndSounds[ i ].mpSound );
	}

	return( 1 );
}


/* ################################################################################ */
