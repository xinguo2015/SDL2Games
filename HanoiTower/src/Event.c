/****************************************************************** 
File name: Event.c
Date: 2015/7/28
Description: �¼������ຯ�� 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "hanoi.h"

 
/************************************************************************/
/*����ԭ�ͣ�void startGame()											*/                                                                   
/*���������Բ������													*/                                                                   
/*�� �� ֵ����															*/
/*�������ܣ�����ʼǰ��ʼ����������									*/                                                                   
/************************************************************************/
void startGame(){

	int i;
	LNode *node;  
	if (theApp.AutoRun)
	{
		theApp.AutoRun=FALSE;
		SDL_WaitThread(theApp.threadID,NULL); 
	} 
	theApp.timeElapse=5;
	setMove(0);
	clearLists();
	for (i=0;i<theApp.discs;i++)
	{
		node=MakeNode(theApp.discs-1-i);
		AddNode(theApp.tower[0].header,node);
	} 
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
		startGame();
		break;
	case evtAutoRun:  
		theApp.AutoRun=TRUE;
		theApp.threadID = SDL_CreateThread( threadFunction, "hanoi", NULL );
		break;  
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
	void *pNow;
	SDL_QuitEvent ev;  
	SDL_MouseButtonEvent* mb = (SDL_MouseButtonEvent*)event;
	SDL_MouseMotionEvent* mm = (SDL_MouseMotionEvent*)event;
	 
	switch( event->type )
	{  
	case SDL_KEYDOWN: 
		if( event->key.keysym.sym==SDLK_ESCAPE )	
		{ 
			ev.type = SDL_QUIT; 
			SDL_PushEvent( (SDL_Event*)&ev );
			break; 
		}  
	case SDL_MOUSEBUTTONDOWN:  
		pNow = GetControlAt(mb->x, mb->y);
		if( !pNow ) break;
		SetFocus(pNow);
		if ( mb->button == 1 )
			onLButtonDown(pNow,mb->x, mb->y, mb->state); 
		break; 
	case SDL_MOUSEBUTTONUP:    
		if ( mb->button == 1 )
			onLButtonUp(mb->x, mb->y, mb->state);  
		break;  
	case SDL_MOUSEMOTION:  
		pNow = GetControlAt(mm->x, mm->y);
		onMouseMove(pNow,mm->x, mm->y, mm->state);
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
	BOOL quit = 0;
	SDL_Event event;
	 
	while( !quit)
	{ 
		while( SDL_PollEvent(&event) )
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = TRUE; 
				if (theApp.AutoRun)
				{
					theApp.AutoRun=FALSE; 
					SDL_WaitThread(theApp.threadID,NULL); 
				} 
				break;

			default: 
				routeEvent(&event);
				break; 
			}
		}   
		renderApp();  
	}   
}
