/****************************************************************** 
Description�����ļ����������ຯ��������ע���е��׿��ʾ��Ϸ�����ÿ������������ʾ��Щ������ɵ�����
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/

#include "miner.h"

/************************************************************************/
/*����ԭ�ͣ�void CalcLayout()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ���ڴ�С����ʱ���Ȳ�����Rect			 			*/                                                                   
/************************************************************************/
void CalcLayout()
{
	int w = theApp.SCREEN_WIDTH;
	int h = theApp.SCREEN_HEIGHT;
	int w1 = DigitsWidth()*6 + FacesWidth();
	int w2 = FieldsWidth();
	int w3 = w2>w1 ? w2 : w1;
	int h1 = DigitsHeight() > FacesHeight() ? DigitsHeight() : FacesHeight();
	int h2 = FieldsHeight() + h1;
	int mgY = h>h2 ? (h-h2)/3 : 0;
	int mgX = w>w3 ? (w-w3)/2 : 0;

	MakeRect(& theApp.taskButton.rect, mgX, mgY, 
		DigitsWidth()*3, DigitsHeight());
	MakeRect(& theApp.timeButton.rect, w - mgX - DigitsWidth()*3, mgY, 
		DigitsWidth()*3, DigitsHeight());
	MakeRect(& theApp.faceButton.rect, w/2-FacesWidth()/2, mgY, 
		FacesWidth(), FacesHeight());
	MakeRect(& theApp.mineField.rect, mgX, mgY + h1 + mgY,
		FieldsWidth(), FieldsHeight());
	theApp.taskButton.rect.x += 3;
	theApp.timeButton.rect.x -= 3;
}

/************************************************************************/
/*����ԭ�ͣ�LTexture load_image(char path[])							*/                                                                   
/*���������ͼƬ��Դ��Ӳ���ϵ����·��									*/                                                                   
/*�� �� ֵ��LTexture													*/                                                                   
/*�������ܣ�������Ӳ���ϵ�ͼƬ��Դ����������			 				*/                                                                   
/************************************************************************/
LTexture load_image(char path[]){

	LTexture ltexture;

	SDL_Surface* loadedSurface=SDL_LoadBMP(path);

	if(loadedSurface==NULL)
	{
		printf("Unable to load image %s!SDL Error: %s\n",path,SDL_GetError());
	} 
	else
	{  
		ltexture.mTexture=SDL_CreateTextureFromSurface(theApp.gRenderer,loadedSurface);

		if (ltexture.mTexture==NULL)
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
		} 
		else{
			ltexture.mWidth=loadedSurface->w;
			ltexture.mHeight=loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	} 

	return ltexture;	
}

/************************************************************************/
/*����ԭ�ͣ�void freeLTexture(LTexture *ltexture)		 				*/
/*������������ͷŵ�LTexture											*/
/*�� �� ֵ����															*/
/*�������ܣ��ͷ�LTexture��Դ						 					*/
/************************************************************************/
void freeLTexture(LTexture *ltexture){

	if (ltexture->mTexture != NULL){

		SDL_DestroyTexture(ltexture->mTexture);
		ltexture->mWidth = 0;
		ltexture->mHeight = 0;
		ltexture->mTexture = NULL;
	}
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
  
	theApp.imgFaces=load_image(FullPath("/media/pics/430.bmp"));
	if (!theApp.imgFaces.mTexture)
	{
		printf("Failed to load imgFaces");
		return FALSE;
	}
	 
	theApp.imgDigits=load_image(FullPath("/media/pics/420.bmp"));
	if (!theApp.imgDigits.mTexture)
	{
		printf("Failed to load imgDigits");
		return FALSE;
	}
	 
	theApp.imgBombs=load_image(FullPath("/media/pics/410.bmp"));
	if (!theApp.imgBombs.mTexture)
	{
		printf("Failed to load imgBombs");
		return FALSE;
	} 

	//���ؿ�ʼ��Ϸ��Ƶ
	theApp.audio_start = Mix_LoadWAV( FullPath("/media/audio/start.wav") );
	if( !theApp.audio_start)
	{
		printf( "Failed to load start sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}

	//�����Զ�������Ƶ
	theApp.audio_reveal = Mix_LoadWAV( FullPath("/media/audio/reveal.wav") );
	if( !theApp.audio_reveal)
	{
		printf( "Failed to load reveal sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}

	//���ر�ը��Ƶ
	theApp.audio_bomb = Mix_LoadWAV( FullPath("/media/audio/bomb.wav") );
	if( !theApp.audio_bomb)
	{
		printf( "Failed to load bomb sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}

	//����ʤ����Ƶ
	theApp.audio_win = Mix_LoadWAV( FullPath("/media/audio/win.wav") );
	if( !theApp.audio_win)
	{
		printf( "Failed to load win sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}
 
	theApp.nFaceSprite = 5;
	theApp.nDigitSprite = 12;
	theApp.nBombSprite = 16;

	return TRUE;
}

/************************************************************************/
/*����ԭ�ͣ�int DigitsWidth()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ������������				   								*/                                                                   
/*�������ܣ���ȡ0-9��������Ŀ��										*/                                                                   
/************************************************************************/
int DigitsWidth()
{
	return theApp.imgDigits.mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int DigitsHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����������߶�				   								*/                                                                   
/*�������ܣ���ȡ0-9��������ĸ߶�										*/                                                                   
/************************************************************************/
int DigitsHeight()
{
	return theApp.imgDigits.mHeight/theApp.nDigitSprite;
}

/************************************************************************/
/*����ԭ�ͣ�int CellsWidth()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ�������׿�Ŀ��				   								*/                                                                   
/*�������ܣ���ȡ�����׿�Ŀ��											*/                                                                   
/************************************************************************/
int CellsWidth()
{
	return theApp.imgBombs.mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int CellsHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ�������׿�ĸ߶�				   								*/                                                                   
/*�������ܣ���ȡ�����׿�ĸ߶�											*/                                                                   
/************************************************************************/
int CellsHeight()
{
	return theApp.imgBombs.mHeight/theApp.nBombSprite;
}

/************************************************************************/
/*����ԭ�ͣ�int FieldsWidth()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ�������Ŀ��				   								    */                                                                   
/*�������ܣ���ȡ���������Ŀ��											*/                                                                   
/************************************************************************/
int FieldsWidth()
{
	return CellsWidth() * theApp.mineField.fldSize[0];
}

/************************************************************************/
/*����ԭ�ͣ�int FieldsHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ�������ĸ߶�				   								    */                                                                   
/*�������ܣ���ȡ���������ĸ߶�											*/                                                                   
/************************************************************************/
int FieldsHeight()
{
	return CellsHeight() * theApp.mineField.fldSize[1];
}
 
/************************************************************************/
/*����ԭ�ͣ�int FacesWidth()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����ͨ����ť�Ŀ��				   							*/                                                                   
/*�������ܣ���ȡ��ͨ����ť�Ŀ��										*/                                                                   
/************************************************************************/
int FacesWidth()
{
	return theApp.imgFaces.mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int FacesHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����ͨ����ť�ĸ߶�				   							*/                                                                   
/*�������ܣ���ȡ��ͨ����ť�ĸ߶�										*/                                                                   
/************************************************************************/
int FacesHeight()
{
	return theApp.imgFaces.mHeight/theApp.nFaceSprite;
}

/************************************************************************/
/*����ԭ�ͣ�void MakeRect(SDL_Rect *rect,int x,int y,int w,int h)		*/                                                                   
/*������������޸ĵ�SDL_Rect��������x,������y�����w���߶�h				*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ��趨���SDL_Rect����������								*/                                                                   
/************************************************************************/
void MakeRect(SDL_Rect* rect, int x, int y, int w, int h)
{
	rect->x = x;
	rect->y = y;
	rect->w = w;
	rect->h = h;
}

/************************************************************************/
/*����ԭ�ͣ�BOOL HitRectTest(int x, int y, SDL_Rect rect)				*/                                                                   
/*������������޸ĵ�SDL_Rect��������x,������y�����w���߶�h				*/                                                                   
/*�� �� ֵ������λ�ھ��������ڷ���TRUE�����򷵻�FALSE					*/                                                                   
/*�������ܣ��ж����꣨x��y���Ƿ�λ�ھ���������							*/                                                                   
/************************************************************************/
BOOL HitRectTest(int x, int y, SDL_Rect rect)
{
	return (x>=rect.x && y>=rect.y && x<rect.x+rect.w && y<rect.y+rect.h );
}

/************************************************************************/
/*����ԭ�ͣ�void * GetFocus()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ȡ���㲿����ָ�루����Ц����ť��							*/                                                                   
/************************************************************************/
void * GetFocus()
{
	return theApp.pFocus;
}

/************************************************************************/
/*����ԭ�ͣ�void * SetFocus(void * pCtrl)								*/                                                                   
/*��������������͵�ָ��												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨����ΪpCtrl 											*/                                                                   
/************************************************************************/
void * SetFocus(void * pCtrl)
{
	theApp.pFocus = pCtrl;
	return pCtrl;
}

/************************************************************************/
/*����ԭ�ͣ�void* GetControlAt(int x, int y)							*/                                                                   
/*���������X���꣬Y����												*/                                                                   
/*�� �� ֵ������λ��ĳ�������ڷ�����ָ�룬���򷵻ؿ�					*/                                                                   
/*�������ܣ���ȡ���꣨x��y�����ڵĲ��� 									*/                                                                   
/************************************************************************/
void* GetControlAt(int x, int y)
{
	if( HitRectTest(x,y,theApp.faceButton.rect) )
		return & theApp.faceButton;
	if( HitRectTest(x,y,theApp.mineField.rect) )
		return & theApp.mineField;
	return NULL;
}

/************************************************************************/
/*����ԭ�ͣ�BOOL IsCell(void *p)										*/                                                                   
/*��������������͵�ָ��												*/                                                                   
/*�� �� ֵ��ָ����ָ������һ���׿鷵��TRUE�����򷵻�FALSE				*/                                                                   
/*�������ܣ��ж�ָ����ָ�����Ƿ�Ϊ�׿�									*/                                                                   
/************************************************************************/
BOOL IsCell(void *p)
{
	MineField *fld = & theApp.mineField;
	void * plast = fld->pCells + fld->fldSize[2];
	return InRange(p, (void*)fld->pCells, plast);
}

/************************************************************************/
/*����ԭ�ͣ�Coord2D CellCoord(MineCell *p)								*/                                                                   
/*����������׿�ָ��													*/                                                                   
/*�� �� ֵ��ָ����ָ�׿�����꣨���׿���Ϊ��λ��						*/                                                                   
/*�������ܣ�����ָ���׿������											*/                                                                   
/************************************************************************/
Coord2D CellCoord(MineCell *p)
{
	MineField *fld = & theApp.mineField;
	Coord2D xy;
	int n = p - fld->pCells;
	xy.x = n % fld->fldSize[0];
	xy.y = n / fld->fldSize[0];
	return xy;
}
