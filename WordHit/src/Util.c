/****************************************************************** 
File name: Util.c
Date: 2015/7/17
Description: ͨ�ù����ຯ�� 
*******************************************************************/
#include "hitword.h"

/************************************************************************/
/*����ԭ�ͣ�int planetWidth()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����������Ŀ��										   		*/                                                                   
/*�������ܣ���ȡ��������Ŀ��											*/                                                                   
/************************************************************************/
int planetWidth(){

	return theApp.gplanet.mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int planetHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����������ĸ߶�										   		*/                                                                   
/*�������ܣ���ȡ��������ĸ߶�											*/                                                                   
/************************************************************************/
int planetHeight(){

	return theApp.gplanet.mHeight;
}

/************************************************************************/
/*����ԭ�ͣ�int explsWidth()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����ը����Ŀ��										   		*/                                                                   
/*�������ܣ���ȡ��ը����Ŀ��											*/                                                                   
/************************************************************************/
int explsWidth(){

	return theApp.gexplosion.mWidth/theApp.nExpSprite;
}

/************************************************************************/
/*����ԭ�ͣ�int explsHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����ը����ĸ߶�										   		*/                                                                   
/*�������ܣ���ȡ��ը����ĸ߶�											*/                                                                   
/************************************************************************/
int explsHeight(){

	return theApp.gexplosion.mHeight;
}

/************************************************************************/
/*����ԭ�ͣ�BOOL IsConflict(SDL_Rect rect1,SDL_Rect rect2)				*/                                                                   
/*�����������Χ��rect1,��Χ��rect2										*/                                                                   
/*�� �� ֵ��������ײ����TRUE,���򷵻�FALSE						   		*/                                                                   
/*�������ܣ�AABB��Χ����ײ���											*/                                                                   
/************************************************************************/
BOOL IsConflict(SDL_Rect rect1,SDL_Rect rect2){

	if (rect1.x+rect1.w<rect2.x)
		return FALSE;
	if (rect1.x>rect2.x+rect2.w)
		return FALSE;
	if (rect1.y+rect1.h<rect2.y)
		return FALSE;
	if (rect1.y>rect2.y+rect2.h)
		return FALSE;

	return TRUE;

}
 
/************************************************************************/
/*����ԭ�ͣ�void MakeRect(SDL_Rect *rect,int x,int y,int w,int h)		*/                                                                   
/*������������޸ĵ�SDL_Rect��������x,������y�����w���߶�h				*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ��趨���SDL_Rect����������								*/                                                                   
/************************************************************************/
void MakeRect(SDL_Rect *rect,int x,int y,int w,int h){

	rect->x=x;
	rect->y=y;
	rect->w=w;
	rect->h=h; 
}
  
extern char gMediaPath[256];

char * MakePath(char path[], char dir[], char filename[])
{
	strcpy(path,dir);
	return strcat(path, filename);
}

char *FullPath(char filename[])
{
	static char path[256];
	return MakePath(path, gMediaPath, filename);
}

/************************************************************************/
/*����ԭ�ͣ�BOOL LoadMedia()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ��ý��ȫ�����سɹ�����TRUE,���򷵻�FALSE   					*/                                                                   
/*�������ܣ�������Ϸ���õ���ý����Դ					 				*/                                                                   
/************************************************************************/
BOOL LoadMedia(){
	SDL_Color textColor={255,84,0,255};
	//�������� 
	theApp.gFont = TTF_OpenFont( FullPath("/media/Arial.ttf"), 16 );
	if( theApp.gFont == NULL ) 
	{
		printf("Failed to load TTF.\n");
	} 
	//��ȡ�ֵ��ļ� 
	if (!read_dic(&theApp.pdic))
	{
		printf("Failed to read_dic.\n");
		return FALSE;
	} 
	//������Ϸ��������
	theApp.background.gback=load_image(FullPath("/media/pics/background.jpg") );
	if (!theApp.background.gback.mTexture)
	{
		printf("Failed to load background.\n");
		return FALSE;
	} 
	//������������
	theApp.gplanet=load_image(FullPath("/media/pics/plane.png") );
	if (!theApp.gplanet.mTexture)
	{
		printf("Failed to load plane.\n");
		return FALSE; 
	} 
	//����UFO���� 
	theApp.ufo.gufo=load_image(FullPath("/media/pics/ufo.png") );
	if (!theApp.ufo.gufo.mTexture)
	{
		printf("Failed to load ufo.\n");
		return FALSE; 
	} 
	MakeRect( &theApp.ufo.rect,theApp.SCREEN_WIDTH/2-UFOWidth()/2,theApp.SCREEN_HEIGHT-UFOHeight(),UFOWidth(),UFOHeight());
	
	//����Ѫ������ 
	theApp.blood.gblood=load_image(FullPath("/media/pics/blood.png") );
	if (!theApp.blood.gblood.mTexture)
	{
		printf("Failed to load gblood.\n");
		return FALSE; 
	} 
	theApp.blood.gbloodBg=load_image(FullPath("/media/pics/bloodBg.png") );
	if (!theApp.blood.gbloodBg.mTexture)
	{
		printf("Failed to load gbloodBg.\n");
		return FALSE; 
	} 
	//�����ڵ�����
	theApp.gbomb=load_image(FullPath("/media/pics/bomb.png") );
	if (!theApp.gbomb.mTexture)
	{
		printf("Failed to load bomb.\n");
		return FALSE;
	} 

	//���ر�ը����
	theApp.gexplosion=load_image(FullPath("/media/pics/boom.png") );
	if (!theApp.gexplosion.mTexture)
	{
		printf("Failed to load gexplosion.\n");
		return FALSE;
	} 
	theApp.nExpSprite=20; 

	//����������ɫ26����ĸ
	if (!loadLetters())
	{
		printf("Failed to load letters.\n");
		return FALSE;
	}
	//������Ϸʧ����������
	theApp.gFont = TTF_OpenFont( FullPath("/media/Arial.ttf"), 24 ); 
	theApp.gGameOver2=load_TTF_text("Please enter SPACE to restart or ESC to quit.",theApp.gFont,textColor);
	theApp.gFont = TTF_OpenFont( FullPath("/media/Semitalic.ttf"), 56 ); 
	theApp.gGameOver1=load_TTF_text("GAME OVER",theApp.gFont,textColor); 
	if (theApp.gGameOver1.mTexture==NULL||theApp.gGameOver2.mTexture==NULL)
	{
		printf("Failed to load gameover.\n");
		return FALSE;
	}

	//Load music
	theApp.gMusic = Mix_LoadMUS( FullPath("/media/audio/bgmusic.mp3") );
	if( theApp.gMusic == NULL )
	{
		printf( "Failed to load bgmusic music! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}

	theApp.wavFire = Mix_LoadWAV( FullPath("/media/audio/fire.wav") );
	if( theApp.wavFire == NULL )
	{
		printf( "Failed to load fire sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}

	theApp.wavBomb = Mix_LoadWAV( FullPath("/media/audio/bomb.wav") );
	if( theApp.wavBomb == NULL )
	{
		printf( "Failed to load bomb sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}

	return TRUE; 
}
