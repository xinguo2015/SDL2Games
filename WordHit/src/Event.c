/****************************************************************** 
File name: Event.c
Date: 2015/7/17
Description: �¼������ຯ�� 
*******************************************************************/
#include "hitword.h"
 
/************************************************************************/
/*����ԭ�ͣ�void startGame()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�ÿ����Ϸ��ʼǰ��ʼ������									*/                                                                   
/************************************************************************/ 
void startGame(){ 

	//��յ�������
	clearWords();
	theApp.timeout=SDL_GetTicks()+2000;
	theApp.hit=-1;//��ǰƴд������
	theApp.hitlen=0; 
	theApp.screen_words=0;		
	
	theApp.gameover=FALSE;
	theApp.background.scrollingOffset=0;
	theApp.blood.hp=100;//Ѫ��
	theApp.blood.screen_hp=100;//��Ļ��ʾ��Ѫ�� 
	//����ڵ�����
	clearBombs(); 
	//���ű�������
	if( Mix_PlayingMusic() == 0 ) 
		Mix_PlayMusic( theApp.gMusic, -1 ); 

}

/************************************************************************/
/*����ԭ�ͣ�void updateApp()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ����												*/                                                                   
/************************************************************************/ 
void updateApp()
{   
	if (theApp.gameover)
		return ;  

	//���±�������ü�λ��
	theApp.background.scrollingOffset--;
	if (theApp.background.scrollingOffset<=0)
	{
		theApp.background.scrollingOffset=theApp.background.gback.mHeight-theApp.SCREEN_HEIGHT;
	} 

	//��ʱ��������
	if (SDL_TICKS_PASSED(SDL_GetTicks(), theApp.timeout))
	{
		generate_one_word();
		theApp.timeout=SDL_GetTicks()+2000; 
	}
	//�����ڵ���Ϣ  
	updateBombs();

	//���µ�����Ϣ  
	updateWords();
	 
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

		case evtStopMusic:
			if( Mix_PausedMusic() == 1 ) 
				Mix_ResumeMusic(); 
			else 
				Mix_PauseMusic(); 
			break;
	}
}
  
/************************************************************************/
/*����ԭ�ͣ�void onKeyDown(int key)										*/                                                                   
/*������������̰���ֵ													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������û������¼�											*/                                                                   
/************************************************************************/
void onKeyDown(int key){
	
	int i; 
	if(theApp.hit > -1) // if the word was once hit
	{
		 
		if(theApp.word[theApp.hit].word[theApp.hitlen] == key) 
		{ 
			theApp.hitlen++; 
			if(theApp.hitlen == strlen(theApp.word[theApp.hit].word))
			{ 
				fire_a_Bomb(theApp.hit); 
				theApp.hit = -1;      // ��ǰ�޴��еĵ���
				theApp.hitlen = 0;   // ���е���ĸ����=0
			}
		}
		else // wrong key entered
		{  
			theApp.hit = -1;
			theApp.hitlen = 0;
		}
	}
	else // if the word is hit for the 1st time
	{
		for(i=0; i<theApp.screen_words; i++)
		{
			if(theApp.word[i].word[0] == key) 
				break; 
		}
		if(i<theApp.screen_words)
		{ 
			theApp.hit = i;
			theApp.hitlen = 1; 
			if(theApp.hitlen == strlen(theApp.word[theApp.hit].word))
			{
				fire_a_Bomb(theApp.hit); // ��ʾ�ӵ� 
				theApp.hit = -1; 
				theApp.hitlen = 0;
			}
		}  
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
	SDL_QuitEvent ev; 
	int  key; 
	switch( event->type )
	{  
	case SDL_KEYDOWN:
		key = event->key.keysym.sym; 
		if( key==SDLK_ESCAPE )	
		{//�˳���Ϸ
			ev.type = SDL_QUIT; 
			SDL_PushEvent( (SDL_Event*)&ev );
			break; 
		} 
		else if( key==SDLK_SPACE && theApp.gameover)
		{//���¿�ʼ��Ϸ
			postUserEvent(evtStartGame); 
			break; 
		}
		else if (key==SDLK_F1)
		{//��ͣ����
			postUserEvent(evtStopMusic); 
			break; 
		}
		else if (!theApp.gameover) 
		{//ƴд����
			onKeyDown(key);
			break; 
		} 	 
	case SDL_WINDOWEVENT:
		//��ק����ʱ���������µĵ���
		if (event->window.event==SDL_WINDOWEVENT_MOVED) 
			theApp.timeout = SDL_GetTicks() + 2000; 
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
			//
			switch (event.type)
			{
			case SDL_QUIT:
				quit = TRUE; 
				break;

			default:  
				routeEvent(&event); 
				break; 
			}
		}  
		//������Ϸ����
		updateApp(); 
		//������Ϸ����
		renderApp();  
	} 
}


