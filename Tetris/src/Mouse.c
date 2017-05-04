
#include "Russia.h"

/************************************************************************/
/*����ԭ�ͣ�void onLButtonDown(void *pCtrl)								*/                                                                   
/*���������ָ��ĳ����ť��ָ��											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������û����°�ť�¼�						 				*/                                                                   
/************************************************************************/
void onLButtonDown(void *pCtrl){
	 
	if (pCtrl==&theApp.StartBtn && theApp.gamestate==NotStart) 
	{
		Mix_PlayChannel( -1, theApp.audio_btnDown, 0 ); 
		theApp.StartBtn.data=strDown;  
	} 

	else if (pCtrl==&theApp.StopBtn && theApp.gamestate!=NotStart)
	{
		Mix_PlayChannel( -1, theApp.audio_btnDown, 0 ); 
		if (theApp.gamestate==Activate)
			theApp.StopBtn.data=stpDown;
		else if (theApp.gamestate==Pause)
			theApp.StopBtn.data=rsmDown;
		else if (theApp.gamestate==Terminate)
			theApp.StopBtn.data=stpOver;
	}  
	else if (pCtrl==&theApp.QuitBtn) 
	{
		theApp.QuitBtn.data=qtDown; 
		Mix_PlayChannel( -1, theApp.audio_btnDown, 0 ); 
	}
		
}

/************************************************************************/
/*����ԭ�ͣ�void loseMouse(void* pCtrl)									*/                                                                   
/*���������ָ��ĳ����ť��ָ��											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���������Ƴ���ť�¼�						 				*/                                                                   
/************************************************************************/
void loseMouse(void* pCtrl){
	 
	if (pCtrl==&theApp.StartBtn && theApp.gamestate==NotStart)
		theApp.StartBtn.data=strExpose;
	else if (pCtrl==&theApp.StopBtn)
	{	
		if (theApp.gamestate==Activate)
			theApp.StopBtn.data=stpExpose;
		if (theApp.gamestate==Pause)
			theApp.StopBtn.data=rsmExpose;
		if (theApp.gamestate==Terminate)
			theApp.StopBtn.data=retExpose;
	} 
	else if (pCtrl==&theApp.QuitBtn)
		theApp.QuitBtn.data=qtExpose; 
}

/************************************************************************/
/*����ԭ�ͣ�void onMouseMove(void *pCtrl)								*/                                                                   
/*���������ָ��ĳ����ť��ָ��											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������꾭����ť�¼�						 				*/                                                                   
/************************************************************************/
void onMouseMove(void *pCtrl){
	 
	void* pOld=getFocus();  
	if (pOld && pOld!=pCtrl)
		loseMouse(pOld);  
	if (pCtrl==&theApp.StartBtn && theApp.gamestate==NotStart)  
		theApp.StartBtn.data=strOver; 
	else if (pCtrl==&theApp.StopBtn)
	{ 
		if (theApp.gamestate==Activate)
			theApp.StopBtn.data=stpOver;
		else if (theApp.gamestate==Pause)
			theApp.StopBtn.data=rsmOver;
		else if (theApp.gamestate==Terminate)
			theApp.StopBtn.data=retOver;
	} 
	else if (pCtrl==&theApp.QuitBtn) 
		theApp.QuitBtn.data=qtOver; 
	setFocus(pCtrl);
}

/************************************************************************/
/*����ԭ�ͣ�void onLButtonUp(void *pCtrl)								*/                                                                   
/*���������ָ��ĳ����ť��ָ��											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������û��ͷŰ�ť�¼�						 				*/                                                                   
/************************************************************************/
void onLButtonUp(void* pCtrl){ 

	SDL_QuitEvent ev; 
	 
	if (pCtrl==&theApp.StartBtn && theApp.gamestate==NotStart) 
	{
		theApp.StartBtn.data=strFix; 
		theApp.gamestate=Activate;
	} 
	else if (pCtrl==&theApp.StopBtn)
	{	
		if (theApp.gamestate==Activate)
		{
			theApp.StopBtn.data=rsmOver;
			theApp.gamestate=Pause;
		}
			
		else if (theApp.gamestate==Pause)
		{
			theApp.StopBtn.data=stpOver;
			theApp.gamestate=Activate;
		} 
		else if (theApp.gamestate==Terminate)
		{
			theApp.StopBtn.data=stpOver;
			theApp.gamestate=Activate;
			StartGame();
		} 
	} 
	else if (pCtrl==&theApp.QuitBtn)
	{
		theApp.QuitBtn.data=qtOver;
		ev.type=SDL_QUIT;
		SDL_PushEvent((SDL_Event *)&ev);
	} 
	setFocus(pCtrl);
}