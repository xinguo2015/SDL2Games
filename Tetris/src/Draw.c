#include "Russia.h"


/************************************************************************/
/*����ԭ�ͣ�void drawBackground()										*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ��������							 				*/                                                                   
/************************************************************************/
void drawBackground(){
	
	SDL_RenderCopy( theApp.gRenderer, theApp.imgBackground.mTexture, NULL, NULL ); 
}
 
/************************************************************************/
/*����ԭ�ͣ�void drawBox(int x,int y,BoxType boxtype)  					*/                                                                   
/*�����������Ϸ�еľ�������(x,y),�����Ʒ��������						*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ָ��λ�û���һ��ָ�����͵ķ���			 				*/                                                                   
/************************************************************************/
void drawBox(int x,int y,BoxType boxtype){

	SDL_Rect srcRect;
	SDL_Rect destRect;

	if (y<1) return;

	srcRect.x=0;
	srcRect.y=BoxHeight()*(boxtype-1);
	srcRect.w=BoxWidth();
	srcRect.h=BoxHeight();

	destRect.x=BOXSIZE*x;
	destRect.y=BOXSIZE*y;
	destRect.w=BoxWidth();
	destRect.h=BoxHeight();

	SDL_RenderCopy(theApp.gRenderer,theApp.imgBox.mTexture,&srcRect,&destRect);
}
   
/************************************************************************/
/*����ԭ�ͣ�void drawBoxes()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������������壬��δ�������ķ���			 				*/                                                                   
/************************************************************************/
void drawBoxes(){

	int i,j;
	for (j=1;j<=BOARD_HEIGHT;j++)
		for (i=1;i<=BOARD_WIDTH;i++)
		{
			drawBox(i,j,theApp.Gameboard[i][j]); 
		}

}

/************************************************************************/
/*����ԭ�ͣ�void drawBtn()												*/                                                                   
/*���������ָ��ť��ָ��															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����ָ���İ�ť								 				*/                                                                   
/************************************************************************/
void drawBtn(ImageButton* btn){

	 SDL_Rect srcRect;
	 
	 srcRect.x=0;
	 srcRect.y=ButtonHeight()*btn->data;
	 srcRect.w=ButtonWidth();
	 srcRect.h=ButtonHeight();

	 SDL_RenderCopy(theApp.gRenderer,btn->ltexture.mTexture,&srcRect,&btn->rect); 
}

/************************************************************************/
/*����ԭ�ͣ�void drawButtons()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ�еĿ�ʼ����ͣ���˳���ť			 				*/                                                                   
/************************************************************************/
void drawButtons(){

	drawBtn(&theApp.StartBtn);
	drawBtn(&theApp.StopBtn);
	drawBtn(&theApp.QuitBtn);

}
 
/************************************************************************/
/*����ԭ�ͣ�void drawBlock(int BlockIndex,int sx,int sy)				*/                                                                   
/*���������������ͼ�ε�������ȫ�����꣨sx,sy��							*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ȫ�����꣨sx��sy��������BlockIndex���͵���״ 				*/                                                                   
/************************************************************************/
void drawBlock(int BlockIndex,int sx,int sy){
	int i;
	for (i=0;i<7;i+=2)  
		drawBox(arrayBLOCK[BlockIndex].arrXY[i]+sx,arrayBLOCK[BlockIndex].arrXY[i+1]+sy,arrayBLOCK[BlockIndex].boxtype); 

}

/************************************************************************/
/*����ԭ�ͣ�void drawShape()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ���������ͼ�κ��¸�ͼ����ʾ		 				*/                                                                   
/************************************************************************/
void drawShape(){
	 
	int x,y,blockindex;
	if (theApp.gamestate==NotStart || theApp.gamestate==Terminate)
		return;

	x=theApp.shape.X;
	y=theApp.shape.Y;
	blockindex=theApp.shape.nCurrent_block_index;
	drawBlock(blockindex,x,y); 

	x=25; 
	y=12;
	blockindex=theApp.shape.nNext_block_index; 
	drawBlock(blockindex,x,y); 

}

/************************************************************************/
/*����ԭ�ͣ�void drawLevel()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����Ƶ�ǰ��Ϸ�Ѷȵȼ�	 					 				*/                                                                   
/************************************************************************/
void drawLevel(){

	SDL_RenderCopy(theApp.gRenderer,theApp.Level.ltexture.mTexture,NULL,&theApp.Level.rect);
}

/************************************************************************/
/*����ԭ�ͣ�void drawScore()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����Ƶ�ǰ�÷�			 					 				*/                                                                   
/************************************************************************/
void drawScore(){
	 
	SDL_RenderCopy(theApp.gRenderer,theApp.Score.ltexture.mTexture,NULL,&theApp.Score.rect); 
}

/************************************************************************/
/*����ԭ�ͣ�void drawFailBg()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����ʧ������			 					 				*/                                                                   
/************************************************************************/
void drawFailBg(){

	SDL_Rect rect={30,50,theApp.imgFail.mWidth,theApp.imgFail.mHeight};
	SDL_RenderCopy( theApp.gRenderer, theApp.imgFail.mTexture, NULL, &rect );
}

/************************************************************************/
/*����ԭ�ͣ�void renderApp()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ��������ť��������ͼ�Σ�δ�������飬�Ʒֺ͵ȼ�		*/                                                                   
/************************************************************************/
void renderApp(){
	 
	SDL_RenderClear( theApp.gRenderer );
	
	drawBackground();
	drawButtons();
	drawShape();
	drawBoxes();
	drawScore();
	drawLevel();
	if (theApp.gamestate==Terminate)
	{
		drawFailBg();
	}

	SDL_RenderPresent( theApp.gRenderer );

}


