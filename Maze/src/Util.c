/****************************************************************** 
File name: Util.c
Date: 2015/8/8
Description: �����ຯ�� 
*******************************************************************/
#include "maze.h"
 
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

/************************************************************************/
/*����ԭ�ͣ�BOOL checkCollision( SDL_Rect a, SDL_Rect b )				*/                                                                   
/*������������ΰ�Χ��a,���ΰ�Χ��b										*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��жϰ�Χ��a���Χ��b�Ƿ���ײ								*/                                                                   
/************************************************************************/
BOOL checkCollision( SDL_Rect a, SDL_Rect b ){

	//���ΰ�Χ�еı߽�
	int leftA,leftB; 
	int rightA,rightB; 
	int topA,topB; 
	int buttomA,buttomB; 

	//���� rect A�ı߽�
	leftA=a.x;
	rightA=a.x+a.w;
	topA=a.y;
	buttomA=a.y+a.h;

	//���� rect B�ı߽�
	leftB=b.x;
	rightB=b.x+b.w;
	topB=b.y;
	buttomB=b.y+b.h;

	//�������A�б߽���B֮��
	if (rightA<=leftB)
	{
		return FALSE;
	}
	if (leftA>=rightB)
	{
		return FALSE;
	}
	if (buttomA<=topB)
	{
		return FALSE;
	}
	if (topA>=buttomB)
	{
		return FALSE;
	} 
	 
	return TRUE;
}
 
/************************************************************************/
/*����ԭ�ͣ�void setDigitWH()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����										   					*/                                                                   
/*�������ܣ��趨��λ�������ȸ߶�						 				*/                                                                   
/************************************************************************/
void setDigitWH(){
	int maxw=0,maxh=0,i;
	//��ȡ0-9ʮ�����������п����߶ȵ����ֵ
	for (i=1;i<10;i++)
	{
		if (theApp.numbersLT[i].mWidth>theApp.numbersLT[maxw].mWidth)
		{
			maxw=i;
		}
		if (theApp.numbersLT[i].mHeight>theApp.numbersLT[maxh].mHeight)
		{
			maxh=i;
		}
	}
	//�趨��������Ϊ���ֵ
	theApp.DigitW=theApp.numbersLT[maxw].mWidth;
	theApp.DigitH=theApp.numbersLT[maxh].mHeight;
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
	 int i;  
	//���ؽ��沿������
	theApp.partLT=load_image(FullPath("/media/part.png"));
	if (!theApp.partLT.mTexture)
	{
		printf("Failed to load parts.png.\n");
		return FALSE;
	}    
	theApp.npartSprite=3;

	//���ذ�ť����
	theApp.btnLT=load_image(FullPath("/media/button.png"));
	if (!theApp.btnLT.mTexture)
	{
		printf("Failed to load buttons.png.\n");
		return FALSE;
	}    
	theApp.nbtnSprite=4;

	//������������
	theApp.gFont = TTF_OpenFont( FullPath("/media/Digit.ttf"), 24 );
	for (i=0;i<10;i++)
	{
		theApp.numbersLT[i]=load_Number(i);
	}
	setDigitWH();
	
	//������Ϸ������ʾ����
	theApp.gFont = TTF_OpenFont( FullPath("/media/Semitalic.ttf"), 80 ); 
	theApp.successLT[0]=load_TTF_text("Success",theApp.gFont); 
	theApp.failLT[0]=load_TTF_text("Fail",theApp.gFont); 

	theApp.gFont = TTF_OpenFont( FullPath("/media/ingleby.ttf"), 24 ); 
	theApp.successLT[1]=load_TTF_text("Please press SPACE to next level or ESC to quit.",theApp.gFont); 
	theApp.failLT[1]=load_TTF_text("Please press SPACE to restart or ESC to quit.",theApp.gFont); 
	
	//������Ϸ�ȼ���ʾ
	theApp.levelLT=load_TTF_text("Level:",theApp.gFont); 


	return TRUE; 
}
 
/************************************************************************/
/*����ԭ�ͣ�BOOL IsSucceed()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ���Ϲϵִ�Ŀ�ĵط���TRUE,���򷵻�FALSE	   					*/                                                                   
/*�������ܣ��ж���Ϸ�Ƿ�ɹ�							 				*/                                                                   
/************************************************************************/
BOOL IsSucceed(){

	if (checkCollision(theApp.pumpkin.rect,theApp.exitRect))
	{
		//�������������������
		return TRUE;
	}

	return FALSE;
}

/************************************************************************/
/*����ԭ�ͣ�BOOL GameOver()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����Ϸʤ��������Ϸʧ�ܷ���TRUE,���򷵻�FALSE 					*/                                                                   
/*�������ܣ��ж���Ϸ����								 				*/                                                                   
/************************************************************************/
BOOL GameOver(){

	if (theApp.gamestate==sGameFail || theApp.gamestate==sGameWin)
	{
		return TRUE;
	}
	return FALSE;

}

/************************************************************************/
/*����ԭ�ͣ�int btnW()													*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ��������ť����Ŀ��											*/                                                                   
/*�������ܣ���ȡ������ť����Ŀ��										*/                                                                   
/************************************************************************/
int btnW(){

	return theApp.btnLT.mWidth;
}   

/************************************************************************/
/*����ԭ�ͣ�int btnH()													*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ��������ť����ĸ߶�											*/                                                                   
/*�������ܣ���ȡ������ť����ĸ߶�										*/                                                                   
/************************************************************************/
int btnH(){

	return theApp.btnLT.mHeight/theApp.nbtnSprite;
}

/************************************************************************/
/*����ԭ�ͣ�void * GetFocus()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ȡ���㲿����ָ��											*/                                                                   
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
/*����ԭ�ͣ�void* GetControlAt(int x,int y)								*/                                                                   
/*���������������x,������y												*/                                                                   
/*�� �� ֵ���������ڵĲ���						   						*/                                                                   
/*�������ܣ���ȡ��Ļ����(x,y)���ڵİ�ť									*/                                                                   
/************************************************************************/
void* GetControlAt(int x,int y){
	 
	void* pFocus=NULL;
	
	if( HitRectTest(x,y,theApp.manualBtn.rect))
		pFocus = &theApp.manualBtn;

	if( !theApp.autoRun && HitRectTest(x,y,theApp.autoBtn.rect))
		 pFocus = &theApp.autoBtn;
	  
	if( theApp.autoRun && HitRectTest(x,y,theApp.upBtn.rect))
		pFocus = &theApp.upBtn;

	if( theApp.autoRun && HitRectTest(x,y,theApp.downBtn.rect))
		pFocus = &theApp.downBtn;

	return pFocus;
}
  
