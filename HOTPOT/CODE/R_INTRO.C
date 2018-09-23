/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_INTRO.H"

#include	"RESOURCE.H"

#include	"R_FADE.H"

#include	<GODLIB\FADE\FADE.H>
#include	<GODLIB\PICTYPES\DEGAS.H>
#include	<GODLIB\SCREEN\SCREEN.H>


/* ###################################################################################
#  DATA
################################################################################### */

sDegas *	gpRIntroRgPic[ eRINTRO_LIMIT ];

sTagString	gRIntroFileNames[ eRINTRO_LIMIT ] =
{
	{	eRINTRO_TEAMHOT,	"TEAM-HOT.PI1"	},
	{	eRINTRO_PRESENTS,	"PRESENTS.PI1"	},
	{	eRINTRO_RGPROD,		"RG-PROD.PI1"	},
	{	eRINTRO_DBLOGO,		"DOUB-JUG.PI1"	},
	{	eRINTRO_VBLOGO,		"VB.PI1"		},
	{	eRINTRO_THIS,		"TIVJ2002.PI1"	},
};


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

U8		RenderIntro_Load( void );
U8		RenderIntro_UnLoad( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderIntro_Init( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderIntro_Init( void )
{
	Resource_Attach( eSECTION_INTRO, RenderIntro_Load, RenderIntro_UnLoad );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderIntro_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderIntro_DeInit( void )
{
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderIntro_Update( void )
* ACTION   : called at end of game
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderIntro_Update( void )
{
	Screen_Update();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderIntro_Title1FadeIn( void )
* ACTION   : fades in title screen
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderIntro_RgFadeIn( const U16 aIndex )
{
	Fade_Main( Fade_GetpBlackPal(), 16 );
/*	RenderScreen_CopyScreen( &gpRIntroRgPic[ aIndex ]->mPixels[ 0 ], RenderScreen_GetpLogic() );*/
	Screen_GetpLogicGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), &gpRIntroRgPic[ aIndex ]->mPixels[ 0 ] );
	Screen_Update();
/*	RenderScreen_CopyScreen( &gpRIntroRgPic[ aIndex ]->mPixels[ 0 ], RenderScreen_GetpLogic() );*/
	Screen_GetpLogicGraphic()->mpFuncs->CopyScreen( Screen_GetpLogicGraphic(), &gpRIntroRgPic[ aIndex ]->mPixels[ 0 ] );
	Fade_Main( &gpRIntroRgPic[ aIndex ]->mHeader.mPalette[ 0 ], 16 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderIntro_Load( void )
* ACTION   : loads all resources for Intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderIntro_Load( void )
{
	U16	i;

	for( i=0; i<eRINTRO_LIMIT; i++ )
	{
		gpRIntroRgPic[ i ] = Resource_Load( sTagString_GetpString( i, &gRIntroFileNames[0], eRINTRO_LIMIT ),   1 );
	}

	return( 1 );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderIntro_UnLoad( void )
* ACTION   : releases memory used by Intro
* CREATION : 21.11.01 PNK
*-----------------------------------------------------------------------------------*/

U8	RenderIntro_UnLoad( void )
{
	U16	i;

	for( i=0; i<eRINTRO_LIMIT; i++ )
	{
		Resource_UnLoad( gpRIntroRgPic[ i ] );
	}

	return( 1 );
}


/* ################################################################################ */
