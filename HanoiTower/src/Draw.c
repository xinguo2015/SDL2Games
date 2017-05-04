/****************************************************************** 
File name: Draw.c
Date: 2015/7/28
Description: �����ຯ����������Ϸ�и������� 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "hanoi.h"


/************************************************************************/
/*����ԭ�ͣ�void drawNum(int x,int y,int num)							*/                                                                   
/*���������x���꣬y���꣬����num										*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��ԣ�x,y��Ϊ�������Ļ�������num								*/                                                                   
/************************************************************************/
void drawNum(int x,int y,int num){
	 
	int i=0,width=0,len=0;
	int numbers[10];
	for (i=0;i<10;i++)
	{
		numbers[i]=-1;
	} 

	if (num==0)
	{
		numbers[0]=0;
		width+=theApp.numbersLT[0].mWidth;
	}
	i=0;
	while (num>0)
	{
		numbers[i]=num%10;//��num�ĸ�λ���ִ���numbers
		width+=theApp.numbersLT[numbers[i]].mWidth;//����������
		num/=10;
		i++;
	}
	for (i=9;i>-1;i--)
	{
		if (numbers[i]>=0)
		{
			renderTexture(theApp.numbersLT[numbers[i]],x-width/2+len,y);
			len+=theApp.numbersLT[numbers[i]].mWidth;
		}
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void drawDisc(int x,int y,int index)						*/                                                                   
/*���������x���꣬y���꣬Բ�̱�־index									*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��ԣ�x,y��Ϊ�ײ����ĵ����indexԲ��							*/                                                                   
/************************************************************************/
void drawDisc(int x,int y,int index){

	int sx,sy;
	SDL_Rect srcRect,destRect;
	sx=x-discW()/2;
	sy=y-discHeight();
	 
	MakeRect(&srcRect,0,discHeight()*index,discW(),discHeight());
	MakeRect(&destRect,sx,sy,discW(),discHeight());
	 
	SDL_RenderCopy(theApp.gRenderer,theApp.discsLT.mTexture,&srcRect,&destRect); 
}	

/************************************************************************/
/*����ԭ�ͣ�void drawDiscFocus()										*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������ƶ��е�Բ��							 				*/                                                                   
/************************************************************************/
void drawDiscFocus(){
	 
	if (theApp.discFocus.node)
	{ 
		drawDisc(theApp.discFocus.x,theApp.discFocus.y+discHeight()/2,theApp.discFocus.node->index); 
	}
	
}	

/************************************************************************/
/*����ԭ�ͣ�void drawDiscInTower(int towerId,int disNum,int index)	*/                                                                   
/*�������������ID���·�Բ��������Բ�̱�־index							*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ָ����������Բ��							 				*/                                                                   
/************************************************************************/
void drawDiscInTower(int towerId,int disNum,int index){

	int x=HX+towerWidth()/2+(HSPACE+towerWidth())*towerId;
	int y=HY+towerHeight()-HW-discHeight()*disNum;

	drawDisc(x,y,index); 
}	

/************************************************************************/
/*����ԭ�ͣ�void DrawDiscs()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���������Բ��								 				*/                                                                   
/************************************************************************/
void DrawDiscs(){

	LNode *node;
	int i,j=0;
	int disc=0;

	for (i=0;i<3;i++)
	{
		node=theApp.tower[i].header->next;
		disc=theApp.tower[i].header->index;
		while (node)
		{
			drawDiscInTower(i,disc-1-j,node->index);
			node=node->next;
			j++;
		}
		j=0;
	}
	drawDiscFocus();
}	

/************************************************************************/
/*����ԭ�ͣ�void DrawBackground()										*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ��������							 				*/                                                                   
/************************************************************************/
void DrawBackground(){

	renderTexture(theApp.bgLT,0,0);
	
	//������ֱ��ָ��ÿ��������λ�ã�������Ӧ��ֱ��ָ�������İ�Χ��
	renderTexture(theApp.towerLT,HX,HY); 
	renderTexture(theApp.towerLT,HX+towerWidth()+HSPACE,HY); 
	renderTexture(theApp.towerLT,HX+(towerWidth()+HSPACE)*2,HY);	

	//��д�ƶ�����
	drawNum(SCREEN_WIDTH/2,SCREEN_HEIGHT-30,theApp.move);
	//��дԲ������ 
	drawNum(SCREEN_WIDTH/5+15,SCREEN_HEIGHT-30,theApp.discs);
	//��д�ɹ���ʾ 
	if (IsWinning())
	{
		renderTexture(theApp.winLT,SCREEN_WIDTH/2-theApp.winLT.mWidth/2,theApp.buttons[0].rect.y+btnHeight()+50);
	}
}	

/************************************************************************/
/*����ԭ�ͣ�void DrawButtons()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ��ť								 				*/                                                                   
/************************************************************************/
void DrawButtons(){

	int i,x,y;
	SDL_Rect srcRect;

	for (i=0;i<5;i++)
	{
		x=theApp.buttons[i].btnIndex*btnWidth();
		y=theApp.buttons[i].state*btnHeight();
		MakeRect(&srcRect,x,y,btnWidth(),btnHeight());

		SDL_RenderCopy(theApp.gRenderer,theApp.btnLT.mTexture,&srcRect,&theApp.buttons[i].rect);
		
	}
	 
}	

/************************************************************************/
/*����ԭ�ͣ�void renderApp()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ���в���											*/                                                                   
/************************************************************************/
void renderApp(){

	SDL_RenderClear( theApp.gRenderer );

	DrawBackground();  

	DrawDiscs();

	DrawButtons();

	SDL_RenderPresent( theApp.gRenderer );

}