#include "Russia.h"


/************************************************************************/
/*����ԭ�ͣ�void handleUp()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����Ұ���UP��ʱ�任ͼ��						 			*/                                                                   
/************************************************************************/ 
void handleUp(){
	 
	int NextBlockId,i;
	static int arrayOffset[5]={0,-1,1,-2,2};
	 
	NextBlockId = arrayBLOCK[getCurrentBlockID()].nNext; 
	for (i=0;i<5;i++)
	{
		if (!IsConflict(NextBlockId,getShapeX()+arrayOffset[i],getShapeY()))
		{
			setCurrentBlockID(NextBlockId);
			alterShapeX(arrayOffset[i]);
			break;
		}
	} 
} 

/************************************************************************/
/*����ԭ�ͣ�void handleLeft()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����Ұ���LEFT��ʱ��������ͼ��						 		*/                                                                   
/************************************************************************/  
void handleLeft(){

	if (!IsConflict(getCurrentBlockID(),getShapeX()-1,getShapeY()))
			alterShapeX(-1);
}

/************************************************************************/
/*����ԭ�ͣ�void handleRight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����Ұ���RIGHT��ʱ��������ͼ��						 		*/                                                                   
/************************************************************************/  
void handleRight(){

	if (!IsConflict(getCurrentBlockID(),getShapeX()+1,getShapeY()))
		alterShapeX(1);
}

/************************************************************************/
/*����ԭ�ͣ�void handleDown()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������״���������									 		*/                                                                   
/************************************************************************/  
void handleDown(){
	SDL_Event ev; 
	int x,y,i,BlockIndex;
	int NumLinesKilled;		
	x=getShapeX();
	y=getShapeY();
	BlockIndex=getCurrentBlockID();
	if (!IsConflict(BlockIndex,x,y+1))
	{  
		alterShapeY(1); 
		return; 
	}
	else 
	{ 
		Mix_PlayChannel( -1, theApp.audio_attach, 0 ); 
		//�޸�Gameboard
		for (i=0;i<=7;i+=2)
		{
			if (y+arrayBLOCK[BlockIndex].arrXY[i+1]<1) 
				continue;  
			theApp.Gameboard[x+arrayBLOCK[BlockIndex].arrXY[i]][y+arrayBLOCK[BlockIndex].arrXY[i+1]]=arrayBLOCK[BlockIndex].boxtype; 
		}  
		//���㲢�޸Ŀ���ȥ����
		NumLinesKilled=KillLines(y); 
		
		//������ȥ���������µ÷�,�����Ѷ�
		if (NumLinesKilled>0)
		{
			Mix_PlayChannel( -1, theApp.audio_score, 0 );

			switch (NumLinesKilled)
			{
			case 1: 
				incScore(100);
				break;
			case 2:
				incScore(300);
				break;
			case 3:
				incScore(500);
				break;
			case 4:
				incScore(800);
				break;
			}
		}
		nextShape();
		 
		if (IsScoreUp())
		{
			Mix_PlayChannel( -1, theApp.audio_levelUp, 0 ); 
			incLevel(); 
		} 
		if (IsGameOver())
		{
			Mix_PlayChannel( -1, theApp.audio_fail, 0 );
			theApp.gamestate=Terminate;
			setFocus(&theApp.StopBtn); 
  			ev.type=SDL_MOUSEMOTION;
			SDL_PushEvent(&ev); 
		} 
	}
	
}

/************************************************************************/
/*����ԭ�ͣ�void onKeyDown(int key) 									*/                                                                   
/*������������̼�ֵ													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���������¼�									 			*/                                                                   
/************************************************************************/
void onKeyDown(int key){

	SDL_QuitEvent ev; 
	
	if (key==SDLK_ESCAPE)
	{
		ev.type=SDL_QUIT;
		SDL_PushEvent((SDL_Event *)&ev);
	}
	//�����Ϸ���ڽ���״̬
	if (theApp.gamestate==Activate)
	{
		switch (key)
		{ 
		case SDLK_UP: 
			handleUp();	
			break;
		case SDLK_LEFT: 
			handleLeft();	
			break;
		case SDLK_RIGHT: 
			handleRight();	
			break;
		case SDLK_DOWN: 
			setAccel(TRUE);
			break;
		}
	}
	 
}
 
/************************************************************************/
/*����ԭ�ͣ�void handleEvents(SDL_Event *event)							*/                                                                   
/*���������SDL_Event													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������¼����ͣ����������������������			 			*/                                                                   
/************************************************************************/
void handleEvents(SDL_Event *event){
 
	SDL_MouseButtonEvent* mb=(SDL_MouseButtonEvent*) event;
	SDL_MouseMotionEvent* mm=(SDL_MouseMotionEvent*) event;
	void* pNow;

	switch (event->type)
	{
	case SDL_KEYDOWN:
			onKeyDown(event->key.keysym.sym);
		break; 
	case SDL_KEYUP:
		if (event->key.keysym.sym==SDLK_DOWN)
			setAccel(FALSE);
		break; 
	case SDL_MOUSEMOTION:
		pNow=getControlAt(mb->x,mb->y); 
		onMouseMove(pNow);
		break;
	case SDL_MOUSEBUTTONDOWN: 
		if (mb->button==1)
		{
			pNow=getControlAt(mb->x,mb->y); 
			if(!pNow) break;
			setFocus(pNow); 
			onLButtonDown(pNow);
		} 
		break;
	case SDL_MOUSEBUTTONUP:
		if (mb->button==1)
		{
			pNow=getControlAt(mb->x,mb->y);
			if(!pNow || pNow!=getFocus()) break; 
			onLButtonUp(pNow);
		}
		break; 
	} 
}
 
/************************************************************************/
/*����ԭ�ͣ�void RunApp()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���Ϸ����ܣ�������Ҵ������¼� �����ƽ���  					*/                                                                   
/************************************************************************/
void RunApp(){

	BOOL quit=FALSE;
	SDL_Event event;

	StartGame(); 

	while (!quit)
	{ 
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit=TRUE;
				break;
			default:
				handleEvents(&event);
				break;
			}
		} 
		if (theApp.gamestate==Activate && (IsAccel()|| IsTimeUp(400-50*getLevel()))) 
			handleDown();
		renderApp();  
		SDL_Delay(50);
	}

}






