extern int gLinkerHelper;
#if	0
/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"PLATFORM.H"

#include	"BUILD.H"

#include	<GODLIB\AUDIO\AUDIO.H>
#include	<GODLIB\EXCEPT\EXCEPT.H>
#include	<GODLIB\FILE\FILE.H>
#include	<GODLIB\GRAPHIC\GRAPHIC.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\SCRNGRAB\SCRNGRAB.H>
#include	<GODLIB\SYSTEM\SYSTEM.H>
#include	<GODLIB\VBL\VBL.H>
#include	<GODLIB\VIDEO\VIDEO.H>


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Platform_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Platform_Init( void )
{
	System_Init();
	Video_Init();
	Vbl_Init();
	IKBD_Init();
	Audio_Init();
	System_DataCacheDisable();
	IKBD_EnableJoysticks();
	Graphic_Init();
/*	Except_Init();*/
#ifdef	dBUILD_PROFILER_ACTIVE
	Profiler_Init( dBUILD_NUMBER_HI, dBUILD_NUMBER_LO );
#endif

	ScreenGrab_Init();
	ScreenGrab_SetDirectory( "SCRNGRAB\\" );
	ScreenGrab_Enable();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Platform_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Platform_DeInit( void )
{
	ScreenGrab_Disable();
	ScreenGrab_DeInit();

#ifdef	dBUILD_PROFILER_ACTIVE
	Profiler_DeInit();
#endif
/*	Except_DeInit();*/
	Graphic_DeInit();
	IKBD_EnableMouse();
	IKBD_DeInit();
	Video_DeInit();
	Vbl_DeInit();
	System_DeInit();
	Audio_DeInit();
	Vbl_WaitVbl();
	IKBD_FlushGemdos();
	Audio_SoundChipOff();
}


/* ################################################################################ */
#endif