/****************************************************************** 
File name: Map.c
Date: 2015/8/9
Description: ��ͼ��غ��� 
*******************************************************************/
#include "maze.h"

/************************************************************************/
/*����ԭ�ͣ�int partW()													*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ������ǽ����Ŀ��											*/                                                                   
/*�������ܣ���ȡ����ǽ����Ŀ��										*/                                                                   
/************************************************************************/
int partW(){

	return theApp.partLT.mWidth;
}   

/************************************************************************/
/*����ԭ�ͣ�int partH()													*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ������ǽ����ĸ߶�											*/                                                                   
/*�������ܣ���ȡ����ǽ����ĸ߶�										*/                                                                   
/************************************************************************/
int partH(){

	return theApp.partLT.mHeight/theApp.npartSprite;
}

/************************************************************************/
/*����ԭ�ͣ�void initGraph(int row,int col)								*/                                                                   
/*���������ͼ��������ͼ������ 											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ʼ��ͼ���ڽӾ����������Ҹ���һ�����ڽڵ�				*/                                                                   
/************************************************************************/
void initGraph(int row,int col){

	int i,j,vertexCur; 
	int vertex=row*col;

	for (i=0;i<vertex;i++) {
		for (j=0;j<vertex;j++){
			theApp.MGraph[i][j]=MAXCOST;
		} 
	} 
	for(i=0;i<row;i++){
		for (j=0;j<col;j++){
			//���Ǳ߽磬�����������Ҿ������ڽڵ㣨ÿ���ڵ����һ����λ��
			vertexCur=i*col+j;
			if (i>0)
				theApp.MGraph[vertexCur][vertexCur-col]=1; 
			if (i<row-1)
				theApp.MGraph[vertexCur][vertexCur+col]=1; 
			if (j>0)
				theApp.MGraph[vertexCur][vertexCur-1]=1; 
			if (j<col-1)
				theApp.MGraph[vertexCur][vertexCur+1]=1; 
		} 
	} 	  
}
 
/************************************************************************/
/*����ԭ�ͣ�int* primTree(int vertex,int col)							*/                                                                   
/*���������ͼ�Ľڵ�������ͼÿ�е�����									*/                                                                   
/*�� �� ֵ�����������ӹ�ϵ����											*/                                                                   
/*�������ܣ�ͨ��prim�㷨���������										*/                                                                   
/************************************************************************/
int* primTree(int vertex,int col){

	int *lowcost=(int *)malloc(vertex*sizeof(int));//ÿ�����㵽��ǰ�������ľ��� 
	int *mst=(int *)malloc(vertex*sizeof(int));//mst[i]Ϊ�ڵ�i���������еĸ��ڵ�
	int *joinable=(int *)malloc(vertex*sizeof(int));//��ǰ���Լ��뵽�������Ķ��㣨��Ϊÿ���߳�����1������һ�ο����ж����� 
	int i, j, temp,minid,m=0;	//minid��ǰѡ���������Ľڵ㣬m��ʾjoinable[]�нڵ���� 
	srand(time(NULL));

	for (i = 1; i < vertex; i++)  
	{  
		lowcost[i] = MAXCOST;  //��lowcost[i]Ϊ����
		mst[i] = 0;  
	}  
	//���ڵ�0������������
	mst[0] = -1;   
	minid = 0;
	lowcost[0]=0;
	//ÿ��ѭ��Ϊ��������һ���½��
	for (i = 1; i < vertex; i++)
	{    
		for (j = 1; j <= 4; j++)  
		{  //��֤���������ĸ�����Ľڵ��Ƿ���Լ���joinable
			switch (j)
			{
			case 1:
				temp=minid-col;
				break;
			case 2:
				temp=minid-1;
				break;
			case 3:
				temp=minid+1;
				break;
			case 4:
				temp=minid+col;
				break;
			}
			if (temp<0 || temp>=vertex)//������temp�ڵ����˳�����ѭ��
				continue;
			if (theApp.MGraph[minid][temp] < lowcost[temp])  
			{	//�����ýڵ�δ����joinable������joinable����
				lowcost[temp] = theApp.MGraph[minid][temp]; 
				joinable[m++]=temp;   
				mst[temp]=minid;
			}   
			else if (theApp.MGraph[minid][temp] == lowcost[temp] && rand()%2==0)//)
			{
				//���ýڵ��Ѿ�����joinable,��δ��������������������Ƿ�ı��丸�ڵ�(�����Թ���ͼ�������)
				mst[temp] = minid;  
			}  
		}  
		//��joinable�����ѡȡһ���ڵ㲢������������lowcostΪ0��
		temp=rand()%m;
		minid=joinable[temp]; 
		memcpy(&joinable[temp], &joinable[temp+1], sizeof(int)*(m-1-temp));
		m--;
		lowcost[minid] = 0;  
	}   
	//�ͷ���ʱ����
	free(lowcost);
	free(joinable);
	 
	return mst; 
}
 
/************************************************************************/	
/*����ԭ�ͣ�void setGameBoard(int mst[],int n)							*/                                                                   
/*����������������ڵ�ĸ��ӹ�ϵ����MST���ڵ���n						*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����������趨gameboard����									*/                                                                   
/************************************************************************/
void setGameBoard(int *mst,int row,int col){

	int i,j,temp;
	int r,c;
	int k=0;
	 
	//��ʼ��GameBoard
	for (i=0;i<=2*row;i++)
	{
		for (j=0;j<=2*col;j++)
		{ 
			if (i%2==1 && j%2==1) 
				theApp.GameBoard[i][j]=BLANK; 
			else 
				theApp.GameBoard[i][j]=WALL; 
				
		}
	}  
	//�������ڵ����ͨ·����ΪBLANK 
	for (i=1;i<row*col;i++)
	{
		temp=mst[i]-i;
		//�ڵ�i��Ӧgameboard��ά���������Ϊr,c
		r=(i/row)*2+1;
		c=(i%col)*2+1;
		//�ѽ������ڵ�֮���λ�ã�ԭΪǽ�ڣ�����Ϊ�յ�
		if (temp==-col)
			theApp.GameBoard[r-1][c]=BLANK;
		else if (temp==-1)
			theApp.GameBoard[r][c-1]=BLANK;
		else if (temp==1)
			theApp.GameBoard[r][c+1]=BLANK;
		else if (temp==col)
			theApp.GameBoard[r+1][c]=BLANK;   
	}   
}

/************************************************************************/
/*����ԭ�ͣ�void setTiles(int row,int col)								*/                                                                   
/*���������ͼ��������ͼ������											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ������Թ������趨ǽ�İ�Χ��									*/                                                                   
/************************************************************************/
void setTiles(int row,int col){
	int i,j,k=0;
	for (i=0;i<=row*2;i++)
	{
		for (j=0;j<=col*2;j++)
		{
			if (theApp.GameBoard[i][j]==WALL)
			{	//����GameBoard���飬�趨ǽ�İ�Χ���� 
				MakeRect(&theApp.tiles[k++],j*partW(),(i+1)*partH(),partW(),partH());
			} 
		}
	} 
}
  
/************************************************************************/
/*����ԭ�ͣ�void setDoors(int row,int col)								*/                                                                   
/*����������ڽӾ�������������											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨����ڵ�λ��											*/                                                                   
/************************************************************************/
void setDoors(int row,int col){
	int k;
	while (TRUE)
	{
		//������������Ļ�ڶ��е�ĳ����λ��
		k=rand()%(2*row)+1;
		if (theApp.GameBoard[k][1]==BLANK)
		{
			MakeRect(&theApp.entryRect,partW(),(k+1)*partH(),partW(),partH());
			//���ϹϷ������λ��
			MakeRect(&theApp.pumpkin.rect,partW(),(k+1)*partH(),partW(),partH());
			break;
		}
	}
	while (TRUE)
	{
		//�������������Ļ�����ڶ��е�ĳ����λ��
		k=rand()%(2*row)+1;
		if (theApp.GameBoard[k][2*col-1]==BLANK)
		{
			MakeRect(&theApp.exitRect,SCREEN_WIDTH-2*partW(),(k+1)*partH(),partW(),partH());
			break;
		}
	}

}

/************************************************************************/
/*����ԭ�ͣ�void generateMap(int row,int col)							*/                                                                   
/*���������ͼ��������ͼ������											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���������Թ����趨ǽ���Χ��								*/                                                                   
/************************************************************************/
void generateMap(int row,int col){

	int *mst=NULL;
	int vertex=row*col;
	//��ʼ���ڽӾ���
	initGraph(row,col);
	//���ɴ���ͨ·�������
	mst=primTree(vertex,col);
	//�趨��ͼ��־����
	setGameBoard(mst,row,col);
	free(mst);
	//�趨ǽ���Χ����
	setTiles(row,col);
	//�趨����ڵİ�Χ��
	setDoors(row,col);
	 
}

/********************************************************************************/
/*����ԭ�ͣ�BOOL touchesWall( SDL_Rect box, SDL_Rect tiles[], int totle_tiles )	*/                                                                   
/*�����������Χ��box,ǽ�İ�Χ����tiles,ǽ�İ�Χ�и���							*/                                                                   
/*�� �� ֵ����ײ����TRUE,���򷵻�FALSE											*/                                                                   
/*�������ܣ��жϰ�Χ��box�Ƿ���ǽ����ײ											*/                                                                   
/********************************************************************************/
BOOL touchesWall( SDL_Rect box, SDL_Rect tiles[], int totle_tiles ){
	int i;
	for (i=0;i<totle_tiles;i++)
	{ 
		 //�����Χ������ǽ��
		if( checkCollision( box, tiles[ i ]) )
		{  
			return TRUE;   
		} 	
	} 
	return FALSE;
}
  
/************************************************************************/	
/*����ԭ�ͣ�void resetGameBoard()										*/                                                                   
/*�����������															*/                                                                   
/*�������ܣ���GameBoard��ֵΪSTEP������ΪBLANK							*/                                                                   
/************************************************************************/
void resetGameBoard(int row,int col){
	int i,j;
	for (i=0;i<=2*row;i++)
	{
		for (j=0;j<=2*col;j++)
		{
			//ɾ���Ϲ��Զ�����ʱ���㼣
			if (theApp.GameBoard[i][j]==STEP) 
				theApp.GameBoard[i][j]=BLANK;  

		}
	} 

}