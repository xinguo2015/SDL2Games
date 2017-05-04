/****************************************************************** 
File name: Mouse.c
Date: 2015/7/31
Description:��괦���� 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "hanoi.h"
 

/**************************************************************	*****************/
/*����ԭ�ͣ�void onLButtonDown(void* pCtrl,int x, int y, unsigned char flags)	*/                                                                   
/*������������㲿��pCtrl,X���꣬Y���꣬���ò���flags							*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ����������������¼�												*/                                                                   
/********************************************************************************/
void onLButtonDown(void* pCtrl,int x, int y, unsigned char flags)
{   
	if (pCtrl>=(void*)(theApp.buttons) && pCtrl<=(void*)(theApp.buttons+4))
		pressBtn((Button*)pCtrl); 
	else if (!theApp.AutoRun)
	{
		detachNode((LNode*)pCtrl,x,y); 
	} 
} 

/**************************************************************	*****************/
/*����ԭ�ͣ�void onLButtonUp(int x, int y, unsigned char flags)					*/                                                                   
/*���������X���꣬Y���꣬���ò���flags											*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ������������ͷ��¼�												*/                                                                   
/********************************************************************************/
void onLButtonUp(int x, int y, unsigned char flags)
{   
	void* pNow;
	if (IsDraging())
	{
		RejoinNode(x,y); 
	} 
	else
	{
		pNow = GetControlAt(x, y);
		if( ! pNow || pNow!=GetFocus() )  
			return;
		releaseBtn((Button*)pNow);
	}

} 

/**************************************************************	*****************/
/*����ԭ�ͣ�void onMouseMove(void * pCtrl,int x, int y, unsigned char flags)	*/                                                                   
/*���������X���꣬Y���꣬���ò���flags											*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ���������ƶ��¼�													*/                                                                   
/********************************************************************************/
void onMouseMove(void * pCtrl,int x, int y, unsigned char flags)
{ 
	void * pOld = GetFocus();
	  
	if (IsDraging())
	{
		theApp.discFocus.x=x;
		theApp.discFocus.y=y;  
	}
	else if (pOld && (!pCtrl))
	{  
		LoseMouse((Button*) pOld);
	}
	 
}
 
/**************************************************************	*****************/
/*����ԭ�ͣ�void LoseMouse(void * pCtrl)										*/                                                                   
/*������������㲿����ָ��														*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ���������Ƴ���ť�¼�												*/                                                                   
/********************************************************************************/
void LoseMouse(Button* pCtrl)
{
	if(pCtrl>=theApp.buttons && pCtrl<=theApp.buttons+4)
	{
		pCtrl->state=btnExposed;	 
	}
}
