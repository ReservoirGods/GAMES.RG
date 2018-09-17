/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	"R_FADE.H"

#include	"BUILD.H"

#include	<GODLIB\ASSERT\ASSERT.H>
#include	<GODLIB\DEBUGLOG\DEBUGLOG.H>
#include	<GODLIB\FADE\FADE.H>
#include	<GODLIB\IKBD\IKBD.H>
#include	<GODLIB\MEMORY\MEMORY.H>
#include	<GODLIB\VIDEO\VIDEO.H>
#include	<GODLIB\VBL\VBL.H>


/* ###################################################################################
#  DATA
################################################################################### */

U16		gRFadeBlackPal[ 16 ];
U16		gRFadeWhitePal[ 16 ];

U16		gRFadeVblOldPal[ 16 ];
U16		gRFadeVblTmpPal[ 16 ];


U8		gRFadeVblActiveFlag;
U32		gRFadeVblAdd;
U32		gRFadeVblScale;
U16 *	gpRFadeVblTmpPal;
U16 *	gpRFadeVblOldPal;
U16 *	gpRFadeVblTargetPal;


/* ###################################################################################
#  PROTOTYPES
################################################################################### */

extern	void	RenderFade_Vbl( void );


/* ###################################################################################
#  CODE
################################################################################### */

/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_Init( void )
* ACTION   : called at start of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFade_Init( void )
{
	U16	i;

	DebugLog_Printf0( "RenderFade_Init()\n" );

	for( i=0; i<16; i++ )
	{
		gRFadeBlackPal[ i ] = 0x0000;
		gRFadeWhitePal[ i ] = 0x0FFF;
	}
#if	0
	Vbl_AddCall( RenderFade_Vbl );
#endif
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_DeInit( void )
* ACTION   : called at end of app
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFade_DeInit( void )
{
	DebugLog_Printf0( "RenderFade_ReInit()\n" );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_Main( U16 * apPal, U16 aFrames )
* ACTION   : fades palette to apPal over aFrames frames
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFade_Main( U16 * apPal, U16 aFrames )
{
	U32	lFade;
	U32	lFadeAdd;
	U32	lPos;
	U16	lNewPal[ 16 ];
	U16	lOldPal[ 16 ];
	U16	i;

	Video_GetPalST( lOldPal );

	lFade     = 0;
	lFadeAdd  = 0x1000000L;
	lFadeAdd /= aFrames;

	for( i=0; i<aFrames; i++ )
	{
		lPos = lFade>>16L;
		if( lPos > 0x100 )
		{
			lPos = 0x100;
		}

		Fade_PalSTE( &lNewPal[0], &lOldPal[0], apPal, 16, (U16)lPos);
		Video_SetNextPalST( lNewPal );
		Vbl_WaitVbl();
		lFade += lFadeAdd;
	}

	Video_SetNextPalST( apPal );
	Vbl_WaitVbl();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_Main( U16 * apPal, U16 aFrames )
* ACTION   : fades palette to apPal over aFrames frames
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFade_Main2( U16 * apPal, U16 * apSrcPal2, U16 * apNewPal2, U16 * apDstPal2, U16 aFrames )
{
	U32	lFade;
	U32	lFadeAdd;
	U32	lPos;
	U16	lNewPal[ 16 ];
	U16	lOldPal[ 16 ];
	U16	i;

	Video_GetPalST( lOldPal );

	lFade     = 0;
	lFadeAdd  = 0x1000000L;
	lFadeAdd /= aFrames;

	for( i=0; i<aFrames; i++ )
	{
		lPos = lFade>>16L;
		if( lPos > 0x100 )
		{
			lPos = 0x100;
		}

		Fade_PalSTE( &lNewPal[0], &lOldPal[0], apPal,     16, (U16)lPos);
		Fade_PalSTE( apDstPal2,   apSrcPal2,   apNewPal2, 16, (U16)lPos);
		Video_SetNextPalST( lNewPal );
		Vbl_WaitVbl();
		lFade += lFadeAdd;
	}

	Video_SetNextPalST( apPal );
	Vbl_WaitVbl();
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_StartVblFade( U16 * apPal, const U16 aFrames )
* ACTION   : inits vbl based fading
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

void	RenderFade_StartVblFade( U16 * apPal, const U16 aFrames )
{
#if	0
	gRFadeVblActiveFlag = 0;
	Video_GetPalST( &gRFadeVblOldPal[ 0 ] );
	gpRFadeVblOldPal    = &gRFadeVblOldPal[ 0 ];
	gpRFadeVblTargetPal = apPal;
	gpRFadeVblTmpPal    = &gRFadeVblTmpPal[ 0 ];
	gRFadeVblScale      = 0;
	gRFadeVblAdd        = 0x1000000L;
	gRFadeVblAdd       /= aFrames;
	gRFadeVblActiveFlag = 1;
#endif
	Fade_StartVblFade( apPal, aFrames );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_IsVblFadeFinished( void )
* ACTION   : returns true if vbl based fade is finished
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

U8		RenderFade_IsVblFadeFinished( void )
{
#if	0
	return( 0 == gRFadeVblActiveFlag );
#endif
	return( Fade_IsVblFadeFinished() );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_GetpBlackPal()
* ACTION   : returns pointer to an all black pal
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

U16 *	RenderFade_GetpBlackPal()
{
	return( gRFadeBlackPal );
}


/*-----------------------------------------------------------------------------------*
* FUNCTION : RenderFade_GetpWhitePal()
* ACTION   : returns pointer to an all white pal
* CREATION : 18.01.01 PNK
*-----------------------------------------------------------------------------------*/

U16 *	RenderFade_GetpWhitePal()
{
	return( gRFadeWhitePal );
}


/* ################################################################################ */
