/****************************************************************** 
File name: Draw.c
Date: 2015/8/7
Description: �����ຯ�� 
*******************************************************************/
#include "maze.h"

/************************************************************************/
/*����ԭ�ͣ�void drawNum(int x,int y,int num)							*/                                                                   
/*���������x���꣬y���꣬����num(0-999)								*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��ԣ�x,y��Ϊ���Ļ�������										*/                                                                   
/************************************************************************/
void drawNum(int x,int y,int num){

	int i=0,len=0,width=0;
	int numbers[3]={0};

	for (i=0;i<3;i++)
	{
		numbers[i]=-1;
	} 
	//��num�ĸ�λ���ִ���numbers���飬������num���������ܳ���
	if (num==0) 
	{
		numbers[0]=0;
		width=theApp.DigitW; 
	}
		
	i=0;
	while (num>0)
	{
		numbers[i]=num%10;
		width+=theApp.DigitW;//ÿλ���ִ�Сһ�£����⵹��ʱ�Ķ�������
		num/=10;
		i++;
	} 
	//��λ��������
	for (i=2;i>=0;i--)
	{ 
		if (numbers[i]>=0)
		{
			renderTexture(theApp.numbersLT[numbers[i]],x-width/2+len,y-theApp.DigitH/2);
			len+=theApp.DigitW; 
		}
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void drawBtn(ImageButton* btn)								*/                                                                   
/*�����������ťָ��													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����ư�ťbtn													*/                                                                   
/************************************************************************/
void drawBtn(ImageButton* btn){

	int x=0,y;
	int w=btnW(),h=btnH();

	SDL_Rect srcRect;
	//���ݰ�ťѡ����Ӧ������
	if (btn==&theApp.autoBtn)
		y=0;//�Զ���������
	else if (btn==&theApp.manualBtn)
		y=btnH();//�ֶ���������
	else if (btn==&theApp.timeBtn)
		y=btnH()*2; //��ʱ����������
	else if (btn==&theApp.upBtn)
	{
		//���ٲ������� 
		y=btnH()*3;
		w=btnW()/2;
	}
	else if (btn==&theApp.downBtn)
	{
		//���ٲ�������
		x=btnW()/2;
		y=btnH()*3; 
		w=btnW()/2;
	} 

	MakeRect(&srcRect,x,y,w,h); 
	SDL_RenderCopy(theApp.gRenderer,theApp.btnLT.mTexture,&srcRect,&btn->rect); 
	
	if (btn==&theApp.timeBtn)
	{//���Ƽ�ʱ����
		drawNum(SCREEN_WIDTH/2,partH()/2+3,theApp.timeBtn.data);
	}
		
}

/************************************************************************/
/*����ԭ�ͣ�void drawLevel()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ�Ѷȵȼ�											*/                                                                   
/************************************************************************/
void drawLevel(){

	 renderTexture(theApp.levelLT,10,partH()/2-theApp.levelLT.mHeight/2);
	 drawNum(theApp.levelLT.mWidth+15+theApp.DigitW,partH()/2+2,theApp.level+1);
}
  
/************************************************************************/
/*����ԭ�ͣ�void DrawWall()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸǽ��								 				*/                                                                   
/************************************************************************/
void DrawWall(){

	int i,j,x,y; 
	//����ǽ��
	for (i=0;i<2*ROW+1;i++)
	{
		for(j=0;j<2*COL+1;j++)
		{
			if (theApp.GameBoard[i][j]==WALL)
			{  
				x=j*partW();
				y=(i+1)*partH(); 
				renderPart(theApp.partLT,0,theApp.npartSprite,x,y);
			}
		}
	}
}
 
/************************************************************************/
/*����ԭ�ͣ�void DrawToolBar()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ļ���˹�����								 			*/                                                                   
/************************************************************************/
void DrawToolBar(){

	//���ƹ�������ɫ����
	SDL_Rect fillRect={0,0,SCREEN_WIDTH,partH()};
	SDL_SetRenderDrawColor(theApp.gRenderer,29,90,111,0xFF); 
	SDL_RenderFillRect(theApp.gRenderer,&fillRect);
	//�����Ѷȵȼ�
	drawLevel();
	//���Ƽ�ʱ��
	 drawBtn(&theApp.timeBtn);
	//���ư�ť
	 drawBtn(&theApp.manualBtn);
	 if (theApp.autoRun)
	 { 
		 //�����ǰ�����Զ���ʾ״̬������ʾ���ټ��ٰ�ť
		 drawBtn(&theApp.upBtn);
		 drawBtn(&theApp.downBtn);
	 }
	 else
	 {
		 //������ʾ�Զ���ʾ��ť
		 drawBtn(&theApp.autoBtn);
	 }
	 
}

/************************************************************************/
/*����ԭ�ͣ�void DrawDoors()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ�����								 				*/                                                                   
/************************************************************************/
void DrawDoors(){
	
	SDL_Rect srcRect={0,partH(),partW(),partH()};
	//�������
	SDL_RenderCopy(theApp.gRenderer,theApp.partLT.mTexture,&srcRect,&theApp.entryRect);
	//���Ƴ���
	SDL_RenderCopy(theApp.gRenderer,theApp.partLT.mTexture,&srcRect,&theApp.exitRect); 
}

/************************************************************************/
/*����ԭ�ͣ�void DrawPumpkin()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������Ϲ�									 				*/                                                                   
/************************************************************************/
void DrawPumpkin(){
	
	SDL_Rect srcRect={0,partH()*2,partW(),partH()};

	SDL_RenderCopy(theApp.gRenderer,theApp.partLT.mTexture,&srcRect,&theApp.pumpkin.rect);
}

/************************************************************************/
/*����ԭ�ͣ�void DrawTips()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������Ϸ������������ʾ										*/                                                                   
/************************************************************************/
void DrawTips(){

	if(theApp.gamestate==sGameWin)
	{
		//�����Ϸ�ɹ������Ƴɹ���ʾ 
		renderTexture(theApp.successLT[0],SCREEN_WIDTH/2-theApp.successLT[0].mWidth/2,SCREEN_HEIGHT/4);
		renderTexture(theApp.successLT[1],SCREEN_WIDTH/2-theApp.successLT[1].mWidth/2,SCREEN_HEIGHT/4+theApp.successLT[0].mHeight*2);
	
	}
	else if (theApp.gamestate==sGameFail)
	{ //�����Ϸʧ�ܣ�����ʧ����ʾ 
		renderTexture(theApp.failLT[0],SCREEN_WIDTH/2-theApp.failLT[0].mWidth/2,SCREEN_HEIGHT/4);
		renderTexture(theApp.failLT[1],SCREEN_WIDTH/2-theApp.failLT[1].mWidth/2,SCREEN_HEIGHT/4+theApp.failLT[0].mHeight*2); 
	}
}

/************************************************************************/
/*����ԭ�ͣ�void renderApp()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ���в���											*/                                                                   
/************************************************************************/
void renderApp(){

	SDL_SetRenderDrawColor(theApp.gRenderer,16,38,52,255);
	SDL_RenderClear( theApp.gRenderer );

	//����ǽ��
	DrawWall();
	//���ƹ�����
	DrawToolBar();
	//���Ƴ����
	DrawDoors();
	//�����Ϲ�
	DrawPumpkin();
	//������ʾ
	DrawTips();
	
	SDL_RenderPresent( theApp.gRenderer );

}



