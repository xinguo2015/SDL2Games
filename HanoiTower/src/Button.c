/****************************************************************** 
File name: Button.c
Date:	2015/8/4
Description:	��ť��غ��� 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "hanoi.h"
 
/************************************************************************/
/*����ԭ�ͣ�int btnWidth()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ���ȡ������ť�Ŀ��											*/                                                                   
/************************************************************************/
int btnWidth(){

	return theApp.btnLT.mWidth/theApp.btnCol;
}

/************************************************************************/
/*����ԭ�ͣ�int btnHeight()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ���ȡ������ť�ĸ߶�											*/                                                                   
/************************************************************************/
int btnHeight(){

	return theApp.btnLT.mHeight/theApp.btnRow;
}

/************************************************************************/
/*����ԭ�ͣ�void pressBtn(Button* pCtrl)								*/                                                                   
/*��������������°�ť��ָ��											*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ����°�ť������											*/                                                                   
/************************************************************************/
void pressBtn(Button* pCtrl){
	 
	pCtrl->state=btnDown;  
}

/************************************************************************/
/*����ԭ�ͣ�void handleAdd()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ�����ӺŰ�ť�¼�											*/                                                                   
/************************************************************************/
void handleAdd()
{
	if (IsBeginning())
	{ 
		incDiscs();
		postUserEvent(evtStartGame);
	}
	else if (theApp.AutoRun && theApp.timeElapse>1)
	{
		theApp.timeElapse--;
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void handleMinus()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ�������Ű�ť�¼�											*/                                                                   
/************************************************************************/
void handleMinus()
{
	if (IsBeginning())
	{ 
		decDiscs();
		postUserEvent(evtStartGame);
	}
	else if (theApp.AutoRun && theApp.timeElapse<10)
	{
		theApp.timeElapse++;
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void releaseBtn(Button* pCtrl)								*/                                                                   
/*����������ͷŰ�ť��ָ��												*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ��ͷŰ�ť������											*/                                                                   
/************************************************************************/
void releaseBtn(Button* pCtrl){

	LoseMouse(pCtrl);

	if (pCtrl==&theApp.buttons[0])
		handleAdd();

	else if (pCtrl==&theApp.buttons[1]) 
		handleMinus(); 

	else if (pCtrl==&theApp.buttons[2] && IsBeginning()) 
		postUserEvent(evtAutoRun);  
	 
	else if (pCtrl==&theApp.buttons[3]) 
		theApp.AutoRun=FALSE;  

	else if (pCtrl==&theApp.buttons[4])
		postUserEvent(evtStartGame);
}