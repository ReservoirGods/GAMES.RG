/* ###################################################################################
#  INCLUDES
################################################################################### */

#include	<GODLIB\SPRITE\SPRITE.H>

sSprite *	lpsBlitterSprite;

U32 *	lpU32;
U16 *	lpU16;
U8 *	lpU8;
S32 *	lpS32;
S16 *	lpS16;
S8 *	lpS8;
U32 	lU32;
U16 	lU16;
U8		lU8;
S32 	lS32;
S16 	lS16;
S8		lS8;


U32		gAudioMusicHblWaitCounter;
U32		gAudioMusicHblWait;
U32		gAudioMusicHblPerVbl;
U32		gAudioMusicHblVblCounter;
U32		gAudioMusicHblCallCounter;

void	AudioMusic_Start( U8 * apVoiceSet, U8 * apSong )
{
	lpU8 = apVoiceSet;
	lpU8 = apSong;
}
void	AudioMusic_Play( void )	{}
void	AudioMusic_Stop( void )	{}

void	AudioMusic_Hbl( void )	{}
void	AudioMusic_HblDummy( void )	{}
void	AudioMusic_Vbl( void ){}





void	RenderFade_Vbl( void )	{}
void	RenderScreen_ClearScreen( U16 * apScreen )
{
	lpU16 = apScreen;
}

void	RenderScreen_CopyScreen( U16 * apSrc, U16 * apDst )
{
	lpU16 = apSrc;
	lpU16 = apDst;
}



