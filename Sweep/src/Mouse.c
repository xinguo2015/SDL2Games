/****************************************************************** 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/

#include "miner.h"
 
/**************************************************************	*****************/
/*����ԭ�ͣ�void onLButtonDown(void *pCtrl, int x, int y, unsigned char flags)	*/                                                                   
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ����������������¼�												*/                                                                   
/********************************************************************************/
void onLButtonDown(void *pCtrl, int x, int y, unsigned char flags)
{  
	if( pCtrl==&theApp.mineField && ! GameOver() )
	{
		postUserEvent(evtFaceOp);
		LeftPressField(x,y,flags);
	}
	else if( pCtrl==&theApp.faceButton ) 
		theApp.faceButton.data = FaceSmileSink;  
} 

/**************************************************************	*****************/
/*����ԭ�ͣ�void onLButtonUp(void *pCtrl, int x, int y, unsigned char flags)	*/                                                                   
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ������������ͷ��¼�												*/                                                                   
/********************************************************************************/
void onLButtonUp(void *pCtrl, int x, int y, unsigned char flags)
{
	if( pCtrl==&theApp.faceButton )
	{
		postUserEvent(evtFaceSmile);
		postUserEvent(evtNewGame);
	}
	else if( pCtrl==&theApp.mineField  && ! GameOver() )
	{
		postUserEvent(evtFaceSmile);
		LeftReleaseField(x,y,flags);
	}
	SetFocus(NULL);
} 

/**************************************************************	*****************/
/*����ԭ�ͣ�void onRButtonDown(void *pCtrl, int x, int y, unsigned char flags)	*/                                                                   
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ���������Ҽ������¼�												*/                                                                   
/********************************************************************************/
void onRButtonDown(void *pCtrl, int x, int y, unsigned char flags)
{
	if( pCtrl==&theApp.mineField  && ! GameOver() )
	{
		RightPressField(x,y,flags);
	}
}

/**************************************************************	*****************/
/*����ԭ�ͣ�void onRButtonUp(void *pCtrl, int x, int y, unsigned char flags)	*/                                                                   
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ���������Ҽ��ͷ��¼�												*/                                                                   
/********************************************************************************/
void onRButtonUp(void *pCtrl, int x, int y, unsigned char flags)
{
	if( pCtrl==&theApp.mineField  && ! GameOver() )
	{
		postUserEvent(evtFaceSmile);
		RightReleaseField(x,y,flags);
	}	
}

/**************************************************************	*****************/
/*����ԭ�ͣ�void LoseMouse(void * pCtrl)										*/                                                                   
/*������������㲿����ָ��														*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ���������Ƴ���ͨ����ť�¼�											*/                                                                   
/********************************************************************************/
void LoseMouse(void * pCtrl)
{
	if( pCtrl==&theApp.faceButton )
	{
		if( theApp.faceButton.data!=FaceSmile )
			postUserEvent(evtFaceSmile);
	}
}

/**************************************************************	*****************/
/*����ԭ�ͣ�void onMouseMove(void *pCtrl, int x, int y, unsigned char flags)	*/                                                                   
/*������������㲿����ָ�룬X���꣬Y���꣬���ò���flags							*/                                                                   
/*�� �� ֵ����  																*/                                                                   
/*�������ܣ���������ƶ��¼�													*/                                                                   
/********************************************************************************/
void onMouseMove(void * pCtrl, int x, int y, unsigned char flags)
{
	void * pOld = GetFocus();

	if( pOld && pOld != pCtrl )
		LoseMouse(pOld);

	if ( ! pOld ) return; // no control to handle

	if( pOld==&theApp.mineField  && ! GameOver() )
		MoveOnField(x,y,flags);
}

