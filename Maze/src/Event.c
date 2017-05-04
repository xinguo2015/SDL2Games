/****************************************************************** 
File name: Event.c
Date: 2015/8/7
Description: �¼������ຯ�� 
*******************************************************************/
#include "maze.h"

/************************************************************************/
/*����ԭ�ͣ�Uint32 onTimer(Uint32 interval, void *param)				*/                                                                   
/*�����������ǰ�ε��õ�ʱ����interval��������ָ��param				*/                                                                   
/*�� �� ֵ����һ�ε��ñ�������ʱ����									*/                                                                   
/*�������ܣ�SDL��׼��ʱ�ص�������ÿ�����е���ʱ��һ						*/                                                                   
/************************************************************************/ 
Uint32 onTimer(Uint32 interval, void *param)
{ 

	theApp.timeBtn.data--; 
	if( theApp.timeBtn.data<=0 )
	{ 
		//����ʱ��������Ϸʧ��
		postUserEvent(evtGameFail);
	}
	//����ͬ��ʱ�����ٴδ����˼�ʱ�ص�����
	return interval;
}

/************************************************************************/
/*����ԭ�ͣ�void postUserEvent(int code)								*/                                                                   
/*����������¼����� code												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���SDL�¼������������Զ����¼�								*/                                                                   
/************************************************************************/
void postUserEvent(int code)
{ 
	SDL_UserEvent ev;
	ev.type = SDL_USEREVENT;
	ev.code = code;
	ev.data1 = NULL;
	ev.data2 = NULL; 

	SDL_PushEvent((SDL_Event*)&ev);
}

/************************************************************************/
/*����ԭ�ͣ�void onUserEvent( SDL_UserEvent *pEvent )					*/                                                                   
/*���������SDL_UserEvent												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������Զ�����û��¼�										*/                                                                   
/************************************************************************/
void onUserEvent( SDL_UserEvent *pEvent ){

	switch (pEvent->code){  

	case evtStartGame:  
		//Ϊ��Ϸ���߼�������ֵ
		theApp.Speed=3;  
		setpumpkinVelX(0);//ʹ�Ϲ��ٶ�Ϊ0
		setpumpkinVelY(0);
		theApp.timeBtn.data=199;  
		theApp.OnTheWay=FALSE;	
		theApp.timeElapse=32;
		theApp.gamestate=sNewGame;
		 //��������Թ�
		generateMap(ROW,COL);  
		postUserEvent(evtStartTimer);	
		break;
	//��ʼ����ʱ
	case evtStartTimer: 
		if (!theApp.timerID)
		{
			theApp.timerID = SDL_AddTimer(MAX(500-theApp.level*40,1), onTimer, NULL);
		} 
		break; 
	//��ͣ����ʱ
	case evtStopTimer: 
		if (theApp.timerID)
		{
			SDL_RemoveTimer(theApp.timerID);
			theApp.timerID = NULL;  
		} 
		break;
	//�����Զ���ʾ
	case evtAutoRun:   
		if (!theApp.autoRun)
		{ 
			theApp.autoRun=TRUE;
			theApp.threadID = SDL_CreateThread( threadFunction, "maze", NULL ); 
			postUserEvent(evtStopTimer);
		} 
		break;  
	//�ر��Զ���ʾ
	case evtStopShow:  
		if (theApp.autoRun)
		{
			theApp.autoRun=FALSE; 
			SDL_WaitThread(theApp.threadID,NULL);  
			resetGameBoard(ROW,COL);
		}  
		break;
	
	case evtGameWin:
		if (!GameOver())
		{
			postUserEvent(evtStopTimer);
			postUserEvent(evtStopShow);
			theApp.gamestate=sGameWin; 
		} 
		break; 

	case evtGameFail:
		if (!GameOver())
		{
			postUserEvent(evtStopTimer);
			postUserEvent(evtStopShow);
			theApp.gamestate=sGameFail;
		} 
		break;
	}
}

/************************************************************************/
/*����ԭ�ͣ�void onKeyDown(int key)										*/                                                                   
/*������������̰���ֵ													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������û����¼����¼�										*/                                                                   
/************************************************************************/
void onKeyDown(int key){

	if (theApp.gamestate==sGameWin && key==SDLK_SPACE)
	{//���سɹ����Ѷ�����
		theApp.level++;
		postUserEvent(evtStartGame);
	}
	else if (theApp.gamestate==sGameFail && key==SDLK_SPACE)
	{//��Ϸʧ�ܣ����¿�ʼ
		theApp.level=0;
		postUserEvent(evtStartGame);
	}
	else if (!theApp.autoRun)
	{//��Ϸ���ڽ��У������Ϲ��ƶ�
		switch(key){

		case SDLK_UP: 
			setpumpkinVelY(-theApp.Speed); 
			break;

		case SDLK_DOWN:
			setpumpkinVelY(theApp.Speed); 
			break;

		case SDLK_LEFT: 
			setpumpkinVelX(-theApp.Speed); 
			break;

		case SDLK_RIGHT: 
			setpumpkinVelX(theApp.Speed); 
			break; 
		}  
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void onKeyUp(int key)										*/                                                                   
/*������������̰���ֵ													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������û��ͷŷ�����¼�										*/                                                                   
/************************************************************************/
void onKeyUp(int key){
	
	if (GameOver() || theApp.autoRun) 
		return; 
	
	if (key== SDLK_UP || key==SDLK_DOWN)
	{ 
		setpumpkinVelY(0);
	}
	else if (key=SDLK_LEFT || key==SDLK_RIGHT)
	{ 
		setpumpkinVelX(0);
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void routeEvent(SDL_Event* event)							*/                                                                   
/*���������SDL_Event													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����ĺ��������ڴ�������Ϸ�еĸ����¼����簴�¸��ְ�����		*/                                                                   
/************************************************************************/
void routeEvent(SDL_Event* event)
{  
	int key;
	void *pNow;
	SDL_QuitEvent ev;  
	SDL_MouseButtonEvent* mb = (SDL_MouseButtonEvent*)event;
	SDL_MouseMotionEvent* mm = (SDL_MouseMotionEvent*)event;

	switch( event->type )
	{   
	case SDL_KEYDOWN:  
		key = event->key.keysym.sym; 
		if( key==SDLK_ESCAPE )	{ 
			ev.type = SDL_QUIT; 
			SDL_PushEvent( (SDL_Event*)&ev ); 
		}   
		else  
			onKeyDown(key); 
		break;   
	case SDL_KEYUP:   
		key = event->key.keysym.sym;  
		onKeyUp(key);
		break;  
	case SDL_MOUSEBUTTONDOWN:  
		pNow = GetControlAt(mb->x, mb->y);
		if( !pNow ) break;
		SetFocus(pNow);
		if ( mb->button == 1 )
			onLButtonDown(pNow); 
		break;   
	case SDL_MOUSEBUTTONUP:    
		pNow = GetControlAt(mm->x, mm->y);
		onLButtonUp(pNow);
		break; 
	case SDL_MOUSEMOTION:  
		pNow = GetControlAt(mm->x, mm->y);
		onMouseMove(pNow);
		break;  
	default:
		if( event->type >= SDL_USEREVENT && event->type < SDL_LASTEVENT )
			onUserEvent((SDL_UserEvent*)event);
		break;
	}
}

/************************************************************************/
/*����ԭ�ͣ�void RunApp()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���Ϸ����ܣ�������Ҵ������¼� �����ƽ���  					*/                                                                   
/************************************************************************/
void RunApp()
{
	BOOL quit = FALSE;
	SDL_Event event;

	while( !quit)
	{ 
		//�����¼�
		while( SDL_PollEvent(&event) )
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = TRUE;  
				postUserEvent(evtStopShow);
				break;

			default: 
				routeEvent(&event);
				break; 
			}
		}

		//�����Ϲϵ�λ��
		if (!theApp.autoRun)
		{
			updatePumpkin();
		}  
		//������Ϸ����
		renderApp();	
	}   
}