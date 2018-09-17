/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"KERNEL.H"

#include	"RESOURCE.H"

#include	"A_INTRO.H"
#include	"A_MUSIC.H"
#include	"A_SPL.H"

#include	"R_FADE.H"

#include	"R_INTRO.H"

#include	<GODLIB\VBL\VBL.H>


/* ###################################################################################
#  DEFINES
################################################################################### */

#define	dINTRO_PAUSE	64


/* ###################################################################################
#  ENUMS
################################################################################### */

enum
{
	eINTRO_SHOW_RG,
	eINTRO_EXIT,

	eINTRO_LIMIT
};


/* ###################################################################################
#  DATA
################################################################################### */

U16	gIntroMode;
U16	gIntroPause;
U16	gIntroPicIndex;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8	Intro_Load( void );
U8	Intro_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : Intro_Init( void )
* ACTION   : calls all initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Intro_Init( void )
{
	Resource_Attach( eSECTION_GLOBAL, Intro_Load, Intro_UnLoad );
	AudioIntro_Init();
	RenderIntro_Init();

	gIntroMode = 0;
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Intro_DeInit( void )
* ACTION   : calls all de-initialisation routines
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

void	Intro_DeInit( void )
{
	AudioIntro_DeInit();
	RenderIntro_DeInit();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Intro_Load( void )
* ACTION   : loads all resources for intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	Intro_Load( void )
{
	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Intro_UnLoad( void )
* ACTION   : releases memory used by intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	Intro_UnLoad( void )
{
	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : Intro_Main( void )
* ACTION   : main intro loop
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U16		Intro_Main( void )
{
	U16	lExitFlag;


	lExitFlag = 0;

	gIntroPicIndex = 0;

	while( !lExitFlag )
	{
		RenderIntro_Update();
		AudioIntro_Update();

		if( gIntroPause )
		{
			gIntroPause--;
		}
		else
		{
			switch( gIntroMode )
			{

			case	eINTRO_SHOW_RG:
				RenderIntro_RgFadeIn( gIntroPicIndex );
				gIntroPause = dINTRO_PAUSE;

				gIntroPicIndex++;
				if( gIntroPicIndex >= eRINTRO_LIMIT )
				{
					gIntroMode  = eINTRO_EXIT;
				}
				break;

			case	eINTRO_EXIT:
				lExitFlag = 1;
				break;

			}
		}

	}

	return( 1 );
}


/* ################################################################################ */
