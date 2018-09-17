/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"A_MAIN.H"

#include	"A_MUSIC.H"
#include	"A_SPL.H"

#include	<GODLIB\AUDIO\AUDIO.H>
#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\MEMORY\MEMORY.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMain_Init( void )
* ACTION   : called at start of game
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMain_Init( void )
{
	AudioMusic_Init();
	AudioSample_Init();
}




/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMain_Clean( void )
* ACTION   : called at end of game
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMain_DeInit( void )
{
	AudioMusic_DeInit();
	AudioSample_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : AudioMain_Update( void )
* ACTION   : Audios all chus
* CREATION : 20.12.00 PNK
*-----------------------------------------------------------------------------------*/

void	AudioMain_Update( void )
{
	AudioMusic_Update();
	AudioSample_Update();
}

void	AudioMain_SpeakerEnable( void )
{
	if( System_GetMCH() == MCH_FALCON )
	{
		Audio_SetInternalSpeakerState( 0 );
	}
}

void	AudioMain_SpeakerDisable( void )
{
	if( System_GetMCH() == MCH_FALCON )
	{
		Audio_SetInternalSpeakerState( 1 );
	}
}
