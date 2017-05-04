/****************************************************************** 
File name: LNode.c
Date: 2015/8/11
Description:����¼������� 
*******************************************************************/
#include "maze.h"

/************************************************************************/
/*����ԭ�ͣ�void scale_downBtn(ImageButton* pCtrl)						*/                                                                   
/*�����������ťָ��pCtrl												*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ����°�ť���ð�ť��״��С��90%								*/                                                                   
/************************************************************************/
void scale_downBtn(ImageButton* pCtrl){

	int x,y,w,h; 
	x=pCtrl->rect.x;
	y=pCtrl->rect.y;
	w=pCtrl->rect.w;
	h=pCtrl->rect.h;

	//��ť��״��С��90%	
	if (pCtrl->data==btnExposed)
	{
		x=x+w/18;
		y=y+h/18;
		w=w*9/10;
		h=h*9/10; 
		MakeRect(&pCtrl->rect,x,y,w,h); 

		pCtrl->data=btnDown;
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void scale_upBtn(ImageButton* pCtrl)						*/                                                                   
/*�����������ťָ��pCtrl												*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ�ʹ��ť��״�ָ�����											*/                                                                   
/************************************************************************/
void scale_upBtn(ImageButton* pCtrl){

	int x,y,w,h;  
	x=pCtrl->rect.x;
	y=pCtrl->rect.y;
	w=pCtrl->rect.w;
	h=pCtrl->rect.h;

	//��ť��״�ָ�����
	if (pCtrl->data==btnDown)
	{
		x=x-w/18;
		y=y-h/18;
		w=w*10/9;
		h=h*10/9; 
		MakeRect(&pCtrl->rect,x,y,w,h); 

		pCtrl->data=btnExposed;
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void releaseBtn(ImageButton* pCtrl)							*/                                                                   
/*�����������ťָ��pCtrl												*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ��ͷŰ�ť���ð�ť��״�ָ�����								*/                                                                   
/************************************************************************/
void releaseBtn(ImageButton* pCtrl){
	
	//ť��״�ָ�����
	scale_upBtn(pCtrl);
	//����ͷŵ����Զ���ʾ��ť
	if (pCtrl==&theApp.autoBtn)
	{ 
		postUserEvent(evtAutoRun); 
	}
	//����ͷŵ����ֶ�������ť	
	if (pCtrl==&theApp.manualBtn)
	{
		theApp.autoRun=FALSE;  
		postUserEvent(evtStartTimer);
	}
	//����ͷŵ��Ǽ��ٲ��Ű�ť
	if (pCtrl==&theApp.upBtn)
	{
		theApp.timeElapse=MAX(theApp.timeElapse/2,4);
	}
	//����ͷŵ��Ǽ��ٲ��Ű�ť
	if (pCtrl==&theApp.downBtn)
	{
		theApp.timeElapse=MIN(theApp.timeElapse*2,1024);
	}
}

/************************************************************************/
/*����ԭ�ͣ�void onLButtonDown(void* pCtrl)								*/                                                                   
/*���������������ָ��pCtrl												*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ��������������°�ť�¼�									*/                                                                   
/************************************************************************/
void onLButtonDown(void* pCtrl)
{   
	if (!GameOver())
	{
		scale_downBtn((ImageButton *)pCtrl); 
	}
	
} 
 
/************************************************************************/
/*����ԭ�ͣ�void onLButtonUp(void* pCtrl)								*/                                                                   
/*���������������ָ��pCtrl												*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ������������ͷ��¼�										*/                                                                   
/************************************************************************/
void onLButtonUp(void* pCtrl)
{     
	if( ! pCtrl ||GameOver())  
		return;
	//���pCtrlָ��ť 
	releaseBtn((ImageButton *)pCtrl);
} 

/************************************************************************/
/*����ԭ�ͣ�void onMouseMove(void* pCtrl)								*/                                                                   
/*���������������ָ��pCtrl												*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ���������ƶ��¼�											*/                                                                   
/************************************************************************/
void onMouseMove(void * pCtrl)
{ 
	void * pOld; 
	if (GameOver())
		return; 
	pOld = GetFocus();
	//�������Ƴ���ť
	if (pOld && (!pCtrl))
	{   
		scale_upBtn((ImageButton*) pOld);
		SetFocus(NULL);
	}   
}