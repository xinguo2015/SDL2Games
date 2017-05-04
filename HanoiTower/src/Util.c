/****************************************************************** 
File name: Util.c
Date: 2015/7/28
Description: ͨ�ù����ຯ�� 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "hanoi.h"

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
/*�������ܣ���ȡ��Ļ�������ڵĲ�������ť��Բ�̻��߿գ�					*/                                                                   
/************************************************************************/
void* GetControlAt(int x,int y){

	int i;
	void* pFocus=NULL;
	 
	for (i=0;i<5;i++)
	{
		if( HitRectTest(x,y,theApp.buttons[i].rect))
			return theApp.buttons+i;
	}

	pFocus=HitDiscTest(x,y); 

	return pFocus;
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
	 SDL_Color textcolor={255,0,0,255};
	 
	 //������Ϸ�ɹ�����
	theApp.gFont = TTF_OpenFont( FullPath("/media/Arial.ttf"), 50 ); 
	theApp.winLT=load_TTF_text("Succeed",theApp.gFont,textcolor);
		  
	//������Ϸ��������
	theApp.bgLT=load_image(FullPath("/media/pics/background.jpg"));
	if (!theApp.bgLT.mTexture)
	{
		printf("Failed to load background.\n");
		return FALSE;
	}    
	

	//������������
	theApp.gFont = TTF_OpenFont( FullPath("/media/Arial.ttf"), 18 );
	for (i=0;i<10;i++)
	{
		theApp.numbersLT[i]=load_Number(i);
	}

	//���ص�������
	theApp.towerLT=load_image( FullPath("/media/pics/tower.png"));
	if (!theApp.towerLT.mTexture)
	{
		printf("Failed to load towerLT.\n");
		return FALSE;
	}   
	 
	//����Բ������
	theApp.discsLT=load_image(FullPath("/media/pics/discs.png"));
	if (!theApp.discsLT.mTexture)
	{
		printf("Failed to load discs.\n");
		return FALSE;
	} 
	theApp.ndiscSprite=9;
	setDiscs(3);

	//���ذ�ť����
	theApp.btnLT=load_image(FullPath("/media/pics/button.png"));
	if (!theApp.btnLT.mTexture)
	{
		printf("Failed to load button.\n");
		return FALSE;
	} 
	theApp.btnRow=2;
	theApp.btnCol=5;
	 
	return TRUE; 
}

/************************************************************************/
/*����ԭ�ͣ�BOOL IsBeginning()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ������disc���ڵ�һ�з���TRUE,���򷵻�FALSE   					*/                                                                   
/*�������ܣ��ж���Ϸ�Ƿ��ڳ�ʼ״̬					 				*/                                                                   
/************************************************************************/
BOOL IsBeginning(){

	if (theApp.tower[0].header->index==theApp.discs)
		return TRUE;

	return FALSE; 
}
 
/************************************************************************/
/*����ԭ�ͣ�BOOL IsWinning()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ������disc���ڵڶ��л�����з���TRUE,���򷵻�FALSE   			*/                                                                   
/*�������ܣ��ж���Ϸ�Ƿ�ɹ�							 				*/                                                                   
/************************************************************************/
BOOL IsWinning(){

	if (theApp.tower[1].header->index==theApp.discs || theApp.tower[2].header->index==theApp.discs)
		return TRUE;

	return FALSE; 
}

/************************************************************************/
/*����ԭ�ͣ�int towerCenX(int t)										*/                                                                   
/*�����������t															*/                                                                   
/*�� �� ֵ����										   					*/                                                                   
/*�������ܣ�����t���ĵ�X����							 				*/                                                                   
/************************************************************************/
int towerCenX(int t){

	return theApp.tower[t].rect.x+HW/2; 

}
  
/************************************************************************/
/*����ԭ�ͣ�int towerCenY(int t)										*/                                                                   
/*�����������t															*/                                                                   
/*�� �� ֵ����										   					*/                                                                   
/*�������ܣ�����t��СԲ�̵ײ���Y����							 		*/                                                                   
/************************************************************************/
int towerCenY(int t){

	return HY+towerHeight()-HW-discHeight()*(theApp.tower[t].header->index); 

}

/************************************************************************/
/*����ԭ�ͣ�void moves(int t1,int t2)									*/                                                                   
/*�����������t1,��t2													*/                                                                   
/*�� �� ֵ����										   					*/                                                                   
/*�������ܣ�����t1�ƶ�һ��Բ����t2						 				*/                                                                   
/************************************************************************/
void moves(int t1,int t2){
 
	int speed; 

	if (!theApp.AutoRun)
		return;
	 
	detachNode(theApp.tower[t1].header,towerCenX(t1),towerCenY(t1));
	 
	//�Ƶ�t1�϶�
	speed=-1;
	while (theApp.discFocus.y>HY-discHeight() && theApp.AutoRun)
	{ 
		theApp.discFocus.y+=speed; 
		SDL_Delay(theApp.timeElapse);
	}
	
	//�Ƶ�t2�϶� 
	speed=towerCenX(t1)<towerCenX(t2)? 1 : -1;  
	while (theApp.discFocus.x!=towerCenX(t2) && theApp.AutoRun)
	{
		theApp.discFocus.x+=speed;
		SDL_Delay(theApp.timeElapse);
	} 

	//�ӵ�����
	if(theApp.AutoRun)
	{ 
		incMove();
		JoinNode(t2); 
		SDL_Delay(200);
	}
	else
		JoinNode(t1); 
	  
}
 

