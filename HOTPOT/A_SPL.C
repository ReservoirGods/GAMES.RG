/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"A_SPL.H"

#include	"BUILD.H"
#include	"DATALOG.H"

#include	<GODLIB\AUDIO\AMIXER.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dASPL_QUEUE_LIMIT	16
#define	dASPL_USE_MIXER		1


/* ###################################################################################
#  STRUCTS
################################################################################### */

typedef	struct sAudioSampleQueueEntry
{
	sAudioDmaSound *				pSound;
	U16								Priority;
	U16								ActiveFlag;
	U8								Pan;
	U8								Volume;
	U16								Pad;
	struct sAudioSampleQueueEntry *	pNext;
	struct sAudioSampleQueueEntry *	pPrev;
} sAudioSampleQueueEntry;


/* ###################################################################################
#  DATA
################################################################################### */

sAudioSampleQueueEntry		gASPLQueue[ dASPL_QUEUE_LIMIT ];
sAudioSampleQueueEntry *	gpASPLQueueHead;
sAudioSampleQueueEntry *	gpASPLQueueTail;
U16							gAudioSampleEnabledFlag;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

void	AudioSample_QueueMoveToBack( sAudioSampleQueueEntry * apQ );
void	AudioSample_QueueUnLink( sAudioSampleQueueEntry * apQ );
void	AudioSample_QueueLinkAfter( sAudioSampleQueueEntry * apSrc,  sAudioSampleQueueEntry * apDst );
void	AudioSample_QueueLinkBefore( sAudioSampleQueueEntry * apSrc,  sAudioSampleQueueEntry * apDst );

void	Cli_AudioSampleMixerOff( const char * apArgs );
void	Cli_AudioSampleMixerOn( const char * apArgs );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_Init( void )
* ACTION   : called at start of game
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_Init( void )
{
	gAudioSampleEnabledFlag = 1;
	AudioSample_QueueClear();

#ifndef	dBUILD_PROFILER_ACTIVE
#ifdef	dASPL_USE_MIXER
	AudioMixer_Init();
	AudioMixer_Enable();
#endif
#endif

#ifdef	dBUILD_CLI_ACTIVE
	Build_CliCmdInit( "audiomixeron",  Cli_AudioSampleMixerOn  );
	Build_CliCmdInit( "audiomixeroff", Cli_AudioSampleMixerOff );
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_DeInit( void )
* ACTION   : called at end of app
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_DeInit( void )
{
	gAudioSampleEnabledFlag = 0;
#ifdef	dASPL_USE_MIXER
	AudioMixer_DeInit();
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_QueueClear( void )
* ACTION   : clear queue, inits all pointers
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_QueueClear( void )
{
	U16	i;

	for( i=0; i<dASPL_QUEUE_LIMIT; i++ )
	{
		gASPLQueue[ i ].ActiveFlag = 0;

		if( i )
		{
			gASPLQueue[ i ].pPrev = &gASPLQueue[ i-1 ];
		}
		else
		{
			gASPLQueue[ i ].pPrev = 0;
		}

		if( (i+1)<dASPL_QUEUE_LIMIT )
		{
			gASPLQueue[ i ].pNext = &gASPLQueue[ i+1 ];
		}
		else
		{
			gASPLQueue[ i ].pNext = 0;
		}
	}

	gpASPLQueueHead = &gASPLQueue[ 0 ];
	gpASPLQueueTail = &gASPLQueue[ dASPL_QUEUE_LIMIT-1 ];
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_QueueUnLink( sAudioSampleQueueEntry * apQ )
* ACTION   : unlinks entry from sample queue
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_QueueUnLink( sAudioSampleQueueEntry * apQ )
{
	if( apQ )
	{
		if( apQ->pPrev )
		{
			apQ->pPrev->pNext = apQ->pNext;
		}

		if( apQ->pNext )
		{
			apQ->pNext->pPrev = apQ->pPrev;
		}

		if( apQ == gpASPLQueueHead )
		{
			gpASPLQueueHead = apQ->pNext;
		}
		if( apQ == gpASPLQueueTail )
		{
			gpASPLQueueTail = apQ->pPrev;
		}

		apQ->pPrev = 0;
		apQ->pNext = 0;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_QueueMoveToBack( sAudioSampleQueueEntry * apQ )
* ACTION   : moves sample to back of queue
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_QueueMoveToBack( sAudioSampleQueueEntry * apQ )
{
	if( apQ )
	{
		AudioSample_QueueLinkAfter( apQ, gpASPLQueueTail );
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_QueueLinkAfter( sAudioSampleQueueEntry * apSrc,  sAudioSampleQueueEntry * apDst )
* ACTION   : links sample apSrc in queue after sample apDst
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_QueueLinkAfter( sAudioSampleQueueEntry * apSrc,  sAudioSampleQueueEntry * apDst )
{
	if( apSrc == apDst )
	{
		return;
	}
	AudioSample_QueueUnLink( apSrc );

	apSrc->pPrev = apDst;
	if( apDst )
	{
		apSrc->pNext = apDst->pNext;
		apDst->pNext = apSrc;
	}
	else
	{
		apSrc->pNext = 0;
	}
	if( apDst == gpASPLQueueTail )
	{
		gpASPLQueueTail = apSrc;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_QueueLinkBefore( sAudioSampleQueueEntry * apSrc,  sAudioSampleQueueEntry * apDst )
* ACTION   : links sample apSrc in queue before sample apDst
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_QueueLinkBefore( sAudioSampleQueueEntry * apSrc,  sAudioSampleQueueEntry * apDst )
{
	if( apSrc == apDst )
	{
		return;
	}
	AudioSample_QueueUnLink( apSrc );

	apSrc->pNext = apDst;
	if( apDst )
	{
		apSrc->pPrev = apDst->pPrev;
		apDst->pPrev = apSrc;
	}
	else
	{
		apSrc->pPrev = 0;
	}
	if( apDst == gpASPLQueueHead )
	{
		gpASPLQueueHead = apSrc;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_Update( void )
* ACTION   : Audios all chus
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_Update( void )
{
	sAudioSampleQueueEntry *	lpQ;

	if( !gAudioSampleEnabledFlag )
	{
		return;
	}

	lpQ = gpASPLQueueHead;

	while( (lpQ) && (!lpQ->ActiveFlag) )
	{
		lpQ = lpQ->pNext;
	}

	if( lpQ )
	{
#ifdef	dASPL_USE_MIXER
		if( AudioMixer_CanPlayNewSpl() )
#else
		if( !Audio_DmaIsSoundPlaying() )
#endif
		{
			if( (lpQ->pSound) && (lpQ->pSound->mLength) )
			{
				if( DataLog_GetEntry( eDATALOG_SFXONFLAG ) )
				{
#ifdef	dASPL_USE_MIXER
					AudioMixer_PlaySample( lpQ->pSound, lpQ->Pan );
#else
					Audio_DmaPlaySound( lpQ->pSound );
#endif
				}
			}
			lpQ->ActiveFlag = 0;
			AudioSample_QueueMoveToBack( lpQ );
		}
	}

	lpQ = gpASPLQueueHead;
	while( lpQ )
	{
		if( lpQ->ActiveFlag )
		{
			lpQ->ActiveFlag--;
			if( !lpQ->ActiveFlag )
			{
				AudioSample_QueueMoveToBack( lpQ );
			}
		}
		lpQ = lpQ->pNext;
	}

}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_PlayFX( const U16 aIndex, const U16 aPriority )
* ACTION   : plays sound fx aIndex
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_PlaySample( sAudioDmaSound * apSound, const U16 aPriority, const U8 aPan )
{
	sAudioSampleQueueEntry *	lpQ;
	sAudioSampleQueueEntry *	lpQnew;

	if( !gAudioSampleEnabledFlag )
	{
		return;
	}

	lpQnew = gpASPLQueueHead;
	while( (lpQnew) && (lpQnew->ActiveFlag) )
	{
		lpQnew = lpQnew->pNext;
	}

	if( !lpQnew )
	{
		lpQnew = gpASPLQueueTail;
	}

	if( lpQnew->ActiveFlag )
	{
		if( lpQnew->Priority > aPriority )
		{
			return;
		}
	}


	lpQ    = gpASPLQueueHead;

	while( lpQ )
	{
		if( (lpQ->Priority < aPriority) || (!lpQ->ActiveFlag) )
		{
			lpQnew->ActiveFlag = 30;
			lpQnew->Priority   = aPriority;
			lpQnew->pSound     = apSound;
			lpQnew->Pan        = aPan;
			AudioSample_QueueLinkBefore( lpQnew, lpQ );
			return;
		}
			
		lpQ = lpQ->pNext;
	}
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioSample_PlaySampleDirect( const U16 aIndex )
* ACTION   : plays sample without queing
* CREATION : 06.02.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioSample_PlaySampleDirect( sAudioDmaSound * apSound, const U8 aPan )
{
	if( !gAudioSampleEnabledFlag )
	{
		return;
	}

	if( (apSound) && (apSound->mLength) )
	{
		if( DataLog_GetEntry( eDATALOG_SFXONFLAG ) )
		{
#ifdef	dASPL_USE_MIXER
			AudioMixer_PlaySampleDirect( apSound, aPan );
#else
			Audio_DmaPlaySound( apSound );
#endif
		}
	}
}


void	AudioSample_Enable( void )
{
	gAudioSampleEnabledFlag = 1;
#ifdef	dASPL_USE_MIXER
	AudioMixer_Enable();
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : void AudioSample_Disable(void)
* ACTION   : AudioSample_Disable
* CREATION : 01.04.2004 PNK
*-----------------------------------------------------------------------------------*/

void AudioSample_Disable(void)
{
	AudioSample_QueueClear();
	gAudioSampleEnabledFlag = 0;
#ifdef	dASPL_USE_MIXER
	AudioMixer_Disable();
#endif
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

void	Cli_AudioSampleMixerOn( const char * apArgs )
{
	AudioMixer_Enable();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMusic_UnLoad( void )
* ACTION   : unloads music
* CREATION : 13.12.01 PNK
*-----------------------------------------------------------------------------------*/

void	Cli_AudioSampleMixerOff( const char * apArgs )
{
	AudioMixer_Disable();
}

#endif


/* ################################################################################ */
