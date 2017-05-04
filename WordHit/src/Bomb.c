/****************************************************************** 
File name: Bomb.c
Date:	2015/7/23
Description:	�ڵ������ຯ��
*******************************************************************/
#include "hitword.h"

/************************************************************************/
/*����ԭ�ͣ�int bombX(int bombIndex)									*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ���ڵ���X����													*/                                                                   
/*�������ܣ���ȡָ���±��ڵ���X����										*/                                                                   
/************************************************************************/
int bombX(int bombIndex){

	return theApp.bombs[bombIndex].rect.x;
}

/************************************************************************/
/*����ԭ�ͣ�int bombY(int bombIndex)									*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ���ڵ���Y����													*/                                                                   
/*�������ܣ���ȡָ���±��ڵ���Y����										*/                                                                   
/************************************************************************/
int bombY(int bombIndex){

	return theApp.bombs[bombIndex].rect.y;
}
 
/************************************************************************/
/*����ԭ�ͣ�int bombW(int bombIndex)									*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ���ڵ���Χ�еĿ��											*/                                                                   
/*�������ܣ���ȡָ���±��ڵ���Χ�еĿ��								*/                                                                   
/************************************************************************/
int bombW(int bombIndex){

	return theApp.bombs[bombIndex].rect.w;
}

/************************************************************************/
/*����ԭ�ͣ�int bombH(int bombIndex)									*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ���ڵ���Χ�еĸ߶�											*/                                                                   
/*�������ܣ���ȡָ���±��ڵ���Χ�еĸ߶�								*/                                                                   
/************************************************************************/
int bombH(int bombIndex){

	return theApp.bombs[bombIndex].rect.h;
}

/************************************************************************/
/*����ԭ�ͣ�int bombHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ���ڵ�����Ŀ��												*/                                                                   
/*�������ܣ���ȡ�ڵ�����Ŀ��											*/                                                                   
/************************************************************************/
int bombWidth(){

	return theApp.gbomb.mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int bombHeight()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ���ڵ�����ĸ߶�												*/                                                                   
/*�������ܣ���ȡ�ڵ�����ĸ߶�											*/                                                                   
/************************************************************************/
int bombHeight(){

	return theApp.gbomb.mHeight;
}

/************************************************************************/
/*����ԭ�ͣ�int bombVelX(int bombIndex)									*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ��ָ���±��ڵ�X�᷽����ٶ�									*/                                                                   
/*�������ܣ���ȡָ���±��ڵ�X�᷽����ٶ�								*/                                                                   
/************************************************************************/
int bombVelX(int bombIndex){

	return theApp.bombs[bombIndex].vel.x;
}

/************************************************************************/
/*����ԭ�ͣ�int bombVelY(int bombIndex)									*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ��ָ���±��ڵ�Y�᷽����ٶ�									*/                                                                   
/*�������ܣ���ȡָ���±��ڵ�Y�᷽����ٶ�								*/                                                                   
/************************************************************************/
int bombVelY(int bombIndex){

	return theApp.bombs[bombIndex].vel.y;
}

/************************************************************************/
/*����ԭ�ͣ�int bombAngle(int bombIndex)								*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ���ڵ�����ת�Ƕ�												*/                                                                   
/*�������ܣ���ȡָ���±��ڵ�����ת�Ƕ�									*/                                                                   
/************************************************************************/
int bombAngle(int bombIndex){
	
	return theApp.bombs[bombIndex].angle;
}
 
/************************************************************************/
/*����ԭ�ͣ�int bombAim(int bombIndex)									*/                                                                   
/*����������ڵ��������±�												*/                                                                   
/*�� �� ֵ���ڵ�Ŀ�굥�ʵ������±�										*/                                                                   
/*�������ܣ���ȡָ���±��ڵ���Ŀ�굥��									*/                                                                   
/************************************************************************/
int bombAim(int bombIndex){

	return theApp.bombs[bombIndex].aim;
}
 
/************************************************************************/
/*����ԭ�ͣ�void setBombAngle(int bombIndex,int angle)					*/                                                                   
/*���������Ŀ���ڵ��������±�,��ת�Ƕ�angle							*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨ָ���±��ڵ�����ת�Ƕȣ�˳ʱ�룩						*/                                                                   
/************************************************************************/
void setBombAngle(int bombIndex,int angle){

	theApp.bombs[bombIndex].angle=angle;
}

/************************************************************************/
/*����ԭ�ͣ�void setBombVel(int bombIndex,int x,int y)					*/                                                                   
/*���������Ŀ���ڵ��������±�,x�᷽����ٶȣ�y�᷽����ٶ�				*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨ָ���±��ڵ����ٶ�										*/                                                                   
/************************************************************************/
void setBombVel(int bombIndex,int x,int y){

	theApp.bombs[bombIndex].vel.x=x;
	theApp.bombs[bombIndex].vel.y=y;
}

/************************************************************************/
/*����ԭ�ͣ�void moveBomb(int bombIndex)								*/                                                                   
/*���������Ŀ���ڵ��������±�											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��ƶ�ָ���±���ڵ�											*/                                                                   
/************************************************************************/
void moveBomb(int bombIndex){

	int x,y; 
	theApp.bombs[bombIndex].rect.x+=bombVelX(bombIndex);
	theApp.bombs[bombIndex].rect.y+=bombVelY(bombIndex);  
	  
	if (bombVelX(bombIndex)!=0)
	{	//�ں����귽���Ѿ��ƶ���λ
		if((bombX(bombIndex)<wordX(bombAim(bombIndex)) && bombVelX(bombIndex)<0) || (bombX(bombIndex)>wordX(bombAim(bombIndex)) && bombVelX(bombIndex)>0))
		{
			x=wordX(bombAim(bombIndex))+wordWidth(bombAim(bombIndex))/2-bombWidth()/2;
			y=bombY(bombIndex)-bombW(bombIndex)/2+bombH(bombIndex)/2;
			//��ʼ�����ƶ�
			if (bombAim(bombIndex)>=0 && bombY(bombIndex)>=wordY(bombAim(bombIndex)))
			{ 
				setBombVel(bombIndex,0,-10);
				setBombAngle(bombIndex,0);
				MakeRect(&theApp.bombs[bombIndex].rect,x,y,bombWidth(),bombHeight());
			}
			else	//��ʼ�����ƶ�
			{ 
				setBombVel(bombIndex,0,10);
				setBombAngle(bombIndex,180);
				MakeRect(&theApp.bombs[bombIndex].rect,x,y,bombWidth(),bombHeight());
			}
		}  
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void fire_a_Bomb(int wordIndex)								*/                                                                   
/*���������Ŀ�굥�ʵ������±�											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����һ���ڵ�												*/                                                                   
/************************************************************************/
void fire_a_Bomb(int wordIndex){
	
	int x,y; 
	if (theApp.screen_bombs>=10)
	{
		printf("Total bomb exceed maximum(10)!\n");
		return;
	}
	Mix_PlayChannel( -1, theApp.wavFire, 0 );	  
	x=theApp.SCREEN_WIDTH/2-bombWidth()/2; 
	y=theApp.SCREEN_HEIGHT-UFOHeight();   	 
	theApp.bombs[theApp.screen_bombs].aim=wordIndex;

	if (x==wordX(wordIndex)+wordWidth(wordIndex)/2-bombWidth()/2)//���Ϸ���
	{ 
		setBombAngle(theApp.screen_bombs,0);
		setBombVel(theApp.screen_bombs,0,-10); 
		MakeRect(&theApp.bombs[theApp.screen_bombs].rect,x,y,bombWidth(),bombHeight()); 
	}
	else if (x<wordX(wordIndex)+wordWidth(wordIndex)/2-bombWidth()/2)//���ҷ���
	{ 
		setBombAngle(theApp.screen_bombs,90);
		setBombVel(theApp.screen_bombs,10,0); 
		x=x+bombWidth()/2-bombHeight()/2;
		y=y+bombHeight()/2-bombWidth()/2;
		MakeRect(&theApp.bombs[theApp.screen_bombs].rect,x,y,bombHeight(),bombWidth());
	}
	else //������
	{ 
		setBombAngle(theApp.screen_bombs,-90);
		setBombVel(theApp.screen_bombs,-10,0); 
		x=x+bombWidth()/2-bombHeight()/2;
		y=y+bombHeight()/2-bombWidth()/2;
		MakeRect(&theApp.bombs[theApp.screen_bombs].rect,x,y,bombHeight(),bombWidth());
	} 
	theApp.screen_bombs++;  
}
 
/************************************************************************/
/*����ԭ�ͣ�void fire_a_Explosion()										*/                                                                   
/*���������x���꣬y����												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���(x,y)Ϊ���ļ���һ����ըЧ��								*/                                                                   
/************************************************************************/
void fire_a_Explosion(int x,int y){

	int i; 
	//���ըЧ��
	for (i=0;i<10;i++)
	{
		if (!theApp.expls[i].valid)
		{
			Mix_PlayChannel( -1, theApp.wavBomb, 0 );	  
			theApp.expls[i].valid=TRUE;
			theApp.expls[i].frame=0;
			MakeRect(&theApp.expls[i].rect,
				x-explsWidth()/2,
				y-explsHeight()/2,
				explsWidth(),
				explsHeight()); 
			break;
		}
	}

}

/************************************************************************/
/*����ԭ�ͣ�void updateBombs()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����������ڵ�����Ϣ											*/                                                                   
/************************************************************************/
void updateBombs(){
	
	int i,aim; 
	for (i=0;i<theApp.screen_bombs;i++)
	{ 
		while(i<theApp.screen_bombs)
		{
			aim=bombAim(i);
			moveBomb(i); 
			if (aim>=0 && IsConflict(theApp.bombs[i].rect,theApp.word[aim].rect))//��Ŀ�굥�ʷ�����ײ
			{ 
				// ��������ɾ�����еĵ��� 
				delete_one_word(aim);  
				//���ըЧ��
				fire_a_Explosion(bombX(i),bombY(i)); 
				// ��������ɾ������ڵ�
				memcpy(&theApp.bombs[i],&theApp.bombs[i+1],sizeof(Bomb)*(theApp.screen_bombs-1-i));
				theApp.screen_bombs--; 
			} 
			else if (bombY(i)<-bombHeight() || bombY(i)>theApp.SCREEN_HEIGHT || bombX(i)<-bombWidth() ||bombX(i)>theApp.SCREEN_WIDTH)//�ڵ��ɳ���Ļ
			{ 
				// ��������ɾ������ڵ� 
				memcpy(&theApp.bombs[i],&theApp.bombs[i+1],sizeof(Bomb)*(theApp.screen_bombs-1-i));
				theApp.screen_bombs--;    
			}
			else	//����ڵ��Ӵ�������ѭ����������һ��
				break;  
		} 
	} 

}

/************************************************************************/
/*����ԭ�ͣ�void clearBombs()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����ڵ�����												*/                                                                   
/************************************************************************/
void clearBombs(){

	memset(theApp.bombs,0,sizeof(Bomb)*10);
}
 

