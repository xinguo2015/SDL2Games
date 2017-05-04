/****************************************************************** 
File name: Util.c
Date: 2015/8/8
Description: �����ຯ�� 
*******************************************************************/
#include "maze.h"

  
/************************************************************************/
/*����ԭ�ͣ�int pumpkinX()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ���Ϲϵ�X����					 								*/                                                                   
/*�������ܣ���ȡ�Ϲϵ�X����												*/                                                                   
/************************************************************************/
int pumpkinX(){

	return theApp.pumpkin.rect.x;
} 

/************************************************************************/
/*����ԭ�ͣ�int pumpkinY()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ���Ϲϵ�Y����													*/                                                                   
/*�������ܣ���ȡ�Ϲϵ�Y����												*/                                                                   
/************************************************************************/
int pumpkinY(){

	return theApp.pumpkin.rect.y;
} 

/************************************************************************/
/*����ԭ�ͣ�void incPumpkinX(int x)										*/                                                                   
/*����������ƶ�����													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨�Ϲ���ˮƽ�����ϵ��ƶ���								*/                                                                   
/************************************************************************/
void incPumpkinX(int x){

	theApp.pumpkin.rect.x+=x;
}

/************************************************************************/
/*����ԭ�ͣ�void incPumpkinY(int y)										*/                                                                   
/*����������ƶ�����													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨�Ϲ�����ֱ�����ϵ��ƶ���								*/                                                                   
/************************************************************************/
void incPumpkinY(int y){

	theApp.pumpkin.rect.y+=y;
}
 
/************************************************************************/
/*����ԭ�ͣ�int pumpkinVelX()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ���Ϲ�ˮƽ������ƶ��ٶ�										*/                                                                   
/*�������ܣ���ȡ�Ϲ�ˮƽ������ƶ��ٶ�									*/                                                                   
/************************************************************************/
int pumpkinVelX(){

	return theApp.pumpkin.velx;
}

/************************************************************************/
/*����ԭ�ͣ�void setpumpkinVelX(int velx)								*/                                                                   
/*����������Ϲ�ˮƽ������ƶ��ٶ�										*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨�Ϲ�ˮƽ������ƶ��ٶ�									*/                                                                   
/************************************************************************/
void setpumpkinVelX(int velx){

	theApp.pumpkin.velx=velx; 
}

/************************************************************************/
/*����ԭ�ͣ�int pumpkinVelY()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ���Ϲ���ֱ������ƶ��ٶ�										*/                                                                   
/*�������ܣ���ȡ�Ϲ���ֱ������ƶ��ٶ�									*/                                                                   
/************************************************************************/
int pumpkinVelY(){

	return theApp.pumpkin.vely; 
}

/************************************************************************/
/*����ԭ�ͣ�void setpumpkinVelY(int vely)								*/                                                                   
/*����������Ϲ���ֱ������ƶ��ٶ�										*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨�Ϲ���ֱ������ƶ��ٶ�									*/                                                                   
/************************************************************************/
void setpumpkinVelY(int vely){

	theApp.pumpkin.vely=vely;   
}

/************************************************************************/
/*����ԭ�ͣ�int verticalTest(int x,int y,int velx)						*/                                                                   
/*���������X���꣬Y���꣬ˮƽ������ٶ�								*/                                                                   
/*�� �� ֵ����ֱ�����ϵ��ƶ���											*/                                                                   
/*�������ܣ����Ϲ���ͼ����ת���������ת�䣬����������ֱ�����Ƿ���Ҫ�ƶ�*/                                                                   
/************************************************************************/
int verticalTest(int x,int y,int velx){

	int i,j;
	i=y/partW()-1;//���꣨x,y����ӦGameBoard[][]������±�,��Ļ������һ����ʾ��������-1
	j=x/partH();
	//�����x,y��������������ҷ���BLANK���Ϲ���ͼ�����ƶ�����������Ļ�Ϸ��ƶ�
	if (theApp.GameBoard[i][j+1]==BLANK && velx>0)
		return -(MAX(theApp.Speed/2,1));
	//�����x,y�����������������BLANK���Ϲ���ͼ�����ƶ�����������Ļ�Ϸ��ƶ�
	else if (theApp.GameBoard[i][j-1]==BLANK && velx<0)
		return -(MAX(theApp.Speed/2,1));
	//�����x,y��������������·���BLANK���Ϲ���ͼ�����ƶ�����������Ļ�·��ƶ�
	else if(theApp.GameBoard[i+1][j+1]==BLANK && velx>0) 
		return MAX(theApp.Speed/2,1);
	//�����x,y��������������·���BLANK���Ϲ���ͼ�����ƶ�����������Ļ�·��ƶ�
	else if(theApp.GameBoard[i+1][j-1]==BLANK && velx<0) 
		return MAX(theApp.Speed/2,1);
	else
		return 0;
}	

/************************************************************************/
/*����ԭ�ͣ�int horizontalTest(int x,int y,int vely)					*/                                                                   
/*���������X���꣬Y���꣬��ֱ������ٶ�								*/                                                                   
/*�� �� ֵ��ˮƽ�����ϵ��ƶ���											*/                                                                   
/*�������ܣ����Ϲ���ͼ����ת���������ת�䣬��������ˮƽ�����Ƿ���Ҫ�ƶ�*/                                                                   
/************************************************************************/
int horizontalTest(int x,int y,int vely){

	int i,j;
	i=y/partW()-1;//���꣨x,y����ӦGameBoard[][]������±�,��Ļ������һ����ʾ��������-1
	j=x/partH(); 
	//�����x,y��������������Ϸ���BLANK���Ϲ���ͼ�����ƶ�����������Ļ���ƶ�
	if (theApp.GameBoard[i-1][j]==BLANK && vely<0) 
		return -(MAX(theApp.Speed/2,1)); 
	//�����x,y��������������·���BLANK���Ϲ���ͼ�����ƶ�����������Ļ���ƶ�
	else if (theApp.GameBoard[i+1][j]==BLANK && vely>0)  
		return -(MAX(theApp.Speed/2,1)); 
	//�����x,y��������������Ϸ���BLANK���Ϲ���ͼ�����ƶ�����������Ļ�ҷ��ƶ�
	else if(theApp.GameBoard[i-1][j+1]==BLANK && vely<0)  
		return MAX(theApp.Speed/2,1); 
	//�����x,y��������������·���BLANK���Ϲ���ͼ�����ƶ�����������Ļ�ҷ��ƶ�
	else if(theApp.GameBoard[i+1][j+1]==BLANK && vely>0) 
		return MAX(theApp.Speed/2,1);
	return 0;
}	

/************************************************************************/
/*����ԭ�ͣ�void updatePumpkin()										*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������Ϲϵ�λ��												*/                                                                   
/************************************************************************/
void updatePumpkin(){
	
	if (GameOver())
		return;
	incPumpkinX(pumpkinVelX());
	//��ˮƽ�����ƶ�ʱ������ײ�����
	if (touchesWall( theApp.pumpkin.rect, theApp.tiles, TOTAL_TILES))
	{   
		incPumpkinX(-pumpkinVelX());
		if (pumpkinVelY()==0)
		{ //��ת��λ�û���ת��
			incPumpkinY(verticalTest(pumpkinX(),pumpkinY(),pumpkinVelX()));
		}
	}

	incPumpkinY(pumpkinVelY());
	//����ֱ�����ƶ�ʱ������ײ�����
	if (touchesWall( theApp.pumpkin.rect, theApp.tiles, TOTAL_TILES))
	{    
		incPumpkinY(-pumpkinVelY());
		if (pumpkinVelX()==0)  
		{//��ת��λ�û���ת�� 
			incPumpkinX(horizontalTest(pumpkinX(),pumpkinY(),pumpkinVelY())); 
		} 
	}
	//�ж���Ϸ�Ƿ�ɹ�
	if (IsSucceed())
	{
		postUserEvent(evtGameWin);
	}
}
 
/************************************************************************/
/*����ԭ�ͣ�void moveUp(int destY)										*/                                                                   
/*���������Ŀ��λ��Y����												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�ʹ�Ϲ���ֱ�����ƶ���destY									*/                                                                   
/************************************************************************/
void moveUp(int destY){  
	if (!theApp.autoRun)
		return;   
	//�趨�Ϲϵ��ٶ�
	setpumpkinVelY(-theApp.Speed); 
	//�Ϲϳ��������ƶ�
	while (pumpkinY()>destY && theApp.autoRun)
	{ 
		//����Ϲ���Ŀ��λ�õľ���С���ٶȵĴ�С����ı��ٶ�
		if (pumpkinY()+pumpkinVelY()<destY)
		{
			setpumpkinVelY(destY-pumpkinY()); 
		}
		//�����Ϲϵ�λ��
		updatePumpkin();  
		SDL_Delay(theApp.timeElapse); 
	}
	setpumpkinVelY(0);
}

/************************************************************************/
/*����ԭ�ͣ�void moveDown(int destY)									*/                                                                   
/*���������Ŀ��λ��Y����												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�ʹ�Ϲ���ֱ�����ƶ���destY									*/                                                                   
/************************************************************************/
void moveDown(int destY){  
	if (!theApp.autoRun)
		return;  
	//�趨�Ϲϵ��ٶ�
	setpumpkinVelY(theApp.Speed); 
	//�Ϲϳ��������ƶ�
	while (pumpkinY()<destY && theApp.autoRun)
	{ 
		//����Ϲ���Ŀ��λ�õľ���С���ٶȵĴ�С����ı��ٶ�
		if (pumpkinY()+pumpkinVelY()>destY)
		{
			setpumpkinVelY(pumpkinY()-destY);
		}
		//�����Ϲϵ�λ��	
		updatePumpkin();  
		SDL_Delay(theApp.timeElapse);  
	}
	setpumpkinVelY(0);
}

/************************************************************************/
/*����ԭ�ͣ�void moveLeft(int destX)									*/                                                                   
/*���������Ŀ��λ��X����												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�ʹ�Ϲ�ˮƽ�����ƶ���destX									*/                                                                   
/************************************************************************/
void moveLeft(int destX){  
	if (!theApp.autoRun)
		return; 
	//�趨�Ϲϵ��ٶ�
	setpumpkinVelX(-theApp.Speed); 
	//�Ϲϳ��������ƶ�
	while (pumpkinX()>destX && theApp.autoRun)
	{ 
		//����Ϲ���Ŀ��λ�õľ���С���ٶȵĴ�С����ı��ٶ�
		if (pumpkinX()+pumpkinVelX()<destX)
		{
			setpumpkinVelX(destX-pumpkinX());
		}
		//�����Ϲϵ�λ��
		updatePumpkin();   
		SDL_Delay(theApp.timeElapse); 
	}
	setpumpkinVelX(0);
}

/************************************************************************/
/*����ԭ�ͣ�void moveRight(int destX)									*/                                                                   
/*���������Ŀ��λ��X����												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�ʹ�Ϲ�ˮƽ�����ƶ���destX									*/                                                                   
/************************************************************************/
void moveRight(int destX){ 
	if (!theApp.autoRun)
		return; 
	//�趨�Ϲϵ��ٶ�
	setpumpkinVelX(theApp.Speed); 
	//�Ϲϳ��������ƶ�
	while (pumpkinX()<destX && theApp.autoRun)
	{ 
		//����Ϲ���Ŀ��λ�õľ���С���ٶȵĴ�С����ı��ٶ�
		if (pumpkinX()+pumpkinVelX()>destX)
		{
			setpumpkinVelX(pumpkinX()-destX);
		} 
		//�����Ϲϵ�λ��
		updatePumpkin(); 
		SDL_Delay(theApp.timeElapse); 
	}
	setpumpkinVelX(0);
}