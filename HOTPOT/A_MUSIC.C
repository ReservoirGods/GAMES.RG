/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"A_MUSIC.H"

#include	"BUILD.H"
#include	"RESOURCE.H"

#include	<GODLIB\AUDIO\AUDIO.H>
#include	<GODLIB\PROFILER\PROFILER.H>
#include	<GODLIB\MFP\MFP.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\VBL\VBL.H>


/* ###################################################################################
#  DATA
################################################################################### */

U32 *		gpAudioMusicReplay;
sMfpTimer	gAudioMusicTimer;
U8 *		gpAudioMusicSongs[     eAMUSIC_SONG_LIMIT ];
U8 *		gpAudioMusicVoiceSets[ eAMUSIC_VOICESET_LIMIT ];
U8			gAudioMusicTunePlayingFlag;
U16			gAudioMusicVoiceSetCurrentIndex;
U16			gAudioMusicSongCurrentIndex;
U16			gAudioMusicEnabledFlag;

sTagString	gAudioMusicFileNames[ eAMUSIC_SONG_LIMIT ] =
{
	{	eAMUSIC_SONG_MAIN,	"DJVBTIVJ.TRI"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		AudioMusic_Load( void );
U8		AudioMusic_UnLoad( void );

void	AudioMusic_Start( U8 * apVoiceSet, U8 * apSong );
void	AudioMusic_Play( void );
void	AudioMusic_Stop( void );


extern	void	AudioMusic_Hbl( void );
extern	void	AudioMusic_HblDummy( void );
extern	void	AudioMusic_Vbl( void );

extern	U32		gAudioMusicHblWaitCounter;
extern	U32		gAudioMusicHblWait;
extern	U32		gAudioMusicHblPerVbl;
extern	U32		gAudioMusicHblVblCounter;
extern	U32		gAudioMusicHblCallCounter;

void	Cli_AudioMusicOn( const char * apArgs );
void	Cli_AudioMusicOff( const char * apArgs );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_Init( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMusic_Init( void )
{
	U32	lHz;
	U32	lData;

	Resource_Attach( eSECTION_GLOBAL, AudioMusic_Load, AudioMusic_UnLoad );


	lHz    = 60;
	lData  = System_GetHblRate()->w.w0;
	lData /= lHz;
	lData &= 0xFFFFL;

	gAudioMusicTimer.mData       = (U8)lData;
	gAudioMusicTimer.mMode       = 7;
	gAudioMusicTimer.mFreq       = (U16)lHz;
	gAudioMusicTimer.mfTimerFunc = AudioMusic_Play;

	gAudioMusicTunePlayingFlag = 0;
	gAudioMusicEnabledFlag     = 1;

	gAudioMusicVoiceSetCurrentIndex = 0;
	gAudioMusicSongCurrentIndex     = 0;

	Vbl_AddCall( AudioMusic_Vbl );

#ifdef	dBUILD_CLI_ACTIVE
	Build_CliCmdInit( "audiomusicon",  Cli_AudioMusicOn  );
	Build_CliCmdInit( "audiomusicoff", Cli_AudioMusicOff );
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_DeInit( void )
* ACTION   : called at end of app
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMusic_DeInit( void )
{
	AudioMusic_StopTune();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_Update( void )
* ACTION   : Audios all chus
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMusic_Update( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_PlayTune( U16 aVoiceSetID, U16 aSongID )
* ACTION   : plays a tune with voice set aVoiceSetID and song aSongID
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMusic_PlayTune( U16 aVoiceSetID, U16 aSongID )
{
#ifdef	dGODLIB_PLATFORM_ATARI
	U32	lFreq;

#ifdef	dBUILD_PROFILER_ACTIVE
	return;
#endif
/*	if( Profiler_IsProfiling() )
	{
	}*/


	if( gAudioMusicTunePlayingFlag )
	{
		if( ( aVoiceSetID == gAudioMusicVoiceSetCurrentIndex ) &&
			( aSongID     == gAudioMusicSongCurrentIndex ) )
		{
			return;
		}
	}

	gAudioMusicVoiceSetCurrentIndex = aVoiceSetID;
	gAudioMusicSongCurrentIndex     = aSongID;

	if( !gAudioMusicEnabledFlag )
	{
		return;
	}


	AudioMusic_StopTune();
	AudioMusic_Start( gpAudioMusicVoiceSets[ aVoiceSetID ], gpAudioMusicSongs[ aSongID ] );

	*(U32*)0x68 = (U32)AudioMusic_HblDummy;
	
	lFreq  = (U32)System_GetHblRate()->w.w1;
	lFreq /= 60L;

	gAudioMusicHblWaitCounter = 0;
	gAudioMusicHblWait        = lFreq;

	gAudioMusicHblCallCounter = 0;
	gAudioMusicHblPerVbl      = (U32)System_GetHblRate()->l;
	gAudioMusicHblPerVbl     /= (U32)System_GetRefreshRate()->l;
	gAudioMusicHblVblCounter  = gAudioMusicHblPerVbl;

	Vbl_WaitVbl();

	*(U32*)0x68 = (U32)AudioMusic_Hbl;
	System_SetIML( 1 );

	gAudioMusicTunePlayingFlag      = 1;
#else
	(void)aVoiceSetID;
	(void)aSongID;
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_StopTune( void )
* ACTION   : stops current tune
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMusic_StopTune( void )
{
	if( gAudioMusicTunePlayingFlag )
	{
		*(U32*)0x68 = (U32)AudioMusic_HblDummy;
		gAudioMusicTunePlayingFlag  = 0;
		AudioMusic_Stop();
/*		Audio_SoundChipOff();*/
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_Load( void )
* ACTION   : loads music
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioMusic_Load( void )
{
	U16	i;

	for( i=0; i<eAMUSIC_SONG_LIMIT; i++ )
	{
		gpAudioMusicSongs[ i ] = 0;
	}
	for( i=0; i<eAMUSIC_VOICESET_LIMIT; i++ )
	{
		gpAudioMusicVoiceSets[ i ] = 0;
	}

	gpAudioMusicReplay                                = Resource_Load( "REPLAYER.BIN", 1 );

	for( i=0; i<eAMUSIC_SONG_LIMIT; i++ )
	{
		gpAudioMusicSongs[ i ] = Resource_Load(
			sTagString_GetpString( i, &gAudioMusicFileNames[ 0 ], eAMUSIC_SONG_LIMIT ),
			1 );
	}

	gpAudioMusicVoiceSets[ eAMUSIC_VOICESET_GENERAL ] = Resource_Load( "CHU.TVS",      1 );
	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_UnLoad( void )
* ACTION   : unloads music
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

U8	AudioMusic_UnLoad( void )
{
	U16	i;

	AudioMusic_Stop();

	Resource_UnLoad( gpAudioMusicReplay );

	for( i=0; i<eAMUSIC_SONG_LIMIT; i++ )
	{
		Resource_UnLoad( gpAudioMusicSongs[ i ] );
	}
	for( i=0; i<eAMUSIC_VOICESET_LIMIT; i++ )
	{
		Resource_UnLoad( gpAudioMusicVoiceSets[ i ] );
	}
	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void AudioMusic_Enable(void)
* ACTION   : AudioMusic_Enable
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void AudioMusic_Enable(void)
{
	gAudioMusicEnabledFlag = 1;
	AudioMusic_PlayTune( gAudioMusicVoiceSetCurrentIndex, gAudioMusicSongCurrentIndex );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void AudioMusic_Disable(void)
* ACTION   : AudioMusic_Disable
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void AudioMusic_Disable(void)
{
	gAudioMusicEnabledFlag = 0;
	AudioMusic_StopTune();
}


/* ###################################################################################
#  CLI ROUTINES
################################################################################### */

#ifdef	dBUILD_CLI_ACTIVE

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_UnLoad( void )
* ACTION   : unloads music
* CREATION : 13.12.01 PNK
*-----------------------------------------------------------------------------------*/

void	Cli_AudioMusicOn( const char * apArgs )
{
	AudioMusic_PlayTune( gAudioMusicVoiceSetCurrentIndex, gAudioMusicSongCurrentIndex );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_UnLoad( void )
* ACTION   : unloads music
* CREATION : 13.12.01 PNK
*-----------------------------------------------------------------------------------*/

void	Cli_AudioMusicOff( const char * apArgs )
{
	AudioMusic_StopTune();
}

#endif


/* ################################################################################ */
