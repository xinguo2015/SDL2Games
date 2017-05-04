/****************************************************************** 
File name: Draw.c
Date: 2015/7/17
Description: �����ຯ����������Ϸ�и������� 
*******************************************************************/
#include "hitword.h"

/************************************************************************/
/*����ԭ�ͣ�void DrawBackground()										*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ��������							 				*/                                                                   
/************************************************************************/
void DrawBackground(){

	SDL_Rect srcRect;
	  
	MakeRect( &srcRect,0,theApp.background.scrollingOffset,theApp.SCREEN_WIDTH,theApp.SCREEN_HEIGHT);

	SDL_RenderCopy( theApp.gRenderer, theApp.background.gback.mTexture, &srcRect, NULL ); 
	 
}	

/************************************************************************/
/*����ԭ�ͣ�void DrawWords()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��������е���										 		*/                                                                   
/************************************************************************/
void DrawWords(){

	int i;   
	for (i=0;i<theApp.screen_words;i++) 
		draw_one_word(i); 
} 

/************************************************************************/
/*����ԭ�ͣ�void DrawBombs()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����������ڵ�										 		*/                                                                   
/************************************************************************/
void DrawBombs(){

	int i;
	SDL_Rect destRect;
	for (i=0;i<theApp.screen_bombs;i++)
	{  
		MakeRect(&destRect,bombX(i),bombY(i),theApp.gbomb.mWidth,theApp.gbomb.mHeight); 
		
		SDL_RenderCopyEx(theApp.gRenderer,theApp.gbomb.mTexture,NULL,&destRect,bombAngle(i),NULL,SDL_FLIP_NONE);
	}

}

/************************************************************************/
/*����ԭ�ͣ�void DrawBooms()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��������б�ը����										 	*/                                                                   
/************************************************************************/
void DrawBooms(){

	int i,x,w,h;  
	SDL_Rect srcRect;
	 
	for (i=0;i<10;i++)
	{
		if (theApp.expls[i].valid)
		{
			w=theApp.expls[i].rect.w;
			h=theApp.expls[i].rect.h;
			x=w*theApp.expls[i].frame;
			MakeRect(&srcRect,x,0,w,h); 
			SDL_RenderCopy(theApp.gRenderer,theApp.gexplosion.mTexture,&srcRect,&theApp.expls[i].rect);
			
			//���±�ը֡���ж��Ƿ��Ѿ��������
			if (++theApp.expls[i].frame>=theApp.nExpSprite)
			{
				theApp.expls[i].valid=FALSE;
				theApp.expls[i].frame=-1;
			}
		}
		
	}

}

/************************************************************************/
/*����ԭ�ͣ�void DrawBlood()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����UFOѪ��									 				*/                                                                   
/************************************************************************/
void DrawBlood(){
	SDL_Rect srcRect,destRect;
	
	//����Ѫ������
	renderTexture(theApp.blood.gbloodBg,10,10);
	
	//����Ѫ��ֵ
	if (UFOScreenHP()>UFOHP())
	{
		theApp.blood.screen_hp-=1;
	} 
	MakeRect(&srcRect,0,0,HPWidth()*theApp.blood.screen_hp/100,HPHeight());
	MakeRect(&destRect,10,10,HPWidth()*theApp.blood.screen_hp/100,HPHeight());

	SDL_RenderCopy(theApp.gRenderer,theApp.blood.gblood.mTexture,&srcRect,&destRect); 
}

/************************************************************************/
/*����ԭ�ͣ�void DrawUFO()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����UFO										 				*/                                                                   
/************************************************************************/
void DrawUFO(){
	    
	renderTexture(theApp.ufo.gufo,UFOPosX(),UFOPosY());
}

/************************************************************************/
/*����ԭ�ͣ�void DrawFail()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����ʧ�ܽ���										 		*/                                                                   
/************************************************************************/
void DrawFail(){
	if (!theApp.gameover)
		return ; 
	renderTexture(theApp.gGameOver1,theApp.SCREEN_WIDTH/2-theApp.gGameOver1.mWidth/2,theApp.SCREEN_HEIGHT/4);
	renderTexture(theApp.gGameOver2,theApp.SCREEN_WIDTH/2-theApp.gGameOver2.mWidth/2,theApp.SCREEN_HEIGHT/4+theApp.gGameOver1.mHeight*2);
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
	DrawWords();
	DrawBombs();
	DrawBlood();
	DrawUFO(); 
	DrawBooms();  
	DrawFail();
		

	SDL_RenderPresent( theApp.gRenderer );

}
