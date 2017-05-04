/****************************************************************** 
File name: LNode.c
Date: 2015/7/31
Description: ������غ��� 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "hanoi.h"


/************************************************************************/
/*����ԭ�ͣ�void MakeNode(int index)									*/                                                                   
/*����������������index												*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ�����һ������Ϊindex�Ľ��									*/                                                                   
/************************************************************************/
LNode* MakeNode(int index){
	LNode *node;
	node=(LNode *)malloc(sizeof(LNode));
	node->index=index;
	node->next=NULL;  
	return node;
}

/************************************************************************/
/*����ԭ�ͣ�void AddNode(LNode* header,LNode *node)						*/                                                                   
/*�������������ͷ���ָ�룬���������ָ��								*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ�������ͷ����һ���½��										*/                                                                   
/************************************************************************/	
void AddNode(LNode* header,LNode *node){
	
	if (!header||!node)
		return; 
	node->next=header->next;
	header->next=node;
	header->index++;
}

/************************************************************************/
/*����ԭ�ͣ�void RejoinNode(int x,int y)								*/                                                                   
/*���������X����,Y����													*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ���ָ��λ���ͷ�ʱ�������������ƶ����Ż�					*/                                                                   
/************************************************************************/
void RejoinNode(int x,int y){

	LNode* header=FindTouchedTower(x,y,theApp.discFocus.node->index); 
	 
	if (!header)  
		header=theApp.discFocus.h;  
		  
	if (header!=theApp.discFocus.h)
		incMove();
	  
	AddNode(header,theApp.discFocus.node);
	theApp.discFocus.node=NULL;
	theApp.discFocus.h=NULL; 
}

/************************************************************************/
/*����ԭ�ͣ�void RejoinNode(int t)										*/                                                                   
/*�����������t															*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ����ƶ����ӵ���t��											*/                                                                   
/************************************************************************/
void JoinNode(int t){ 
	
	AddNode(theApp.tower[t].header,theApp.discFocus.node);
	theApp.discFocus.node=NULL;
	theApp.discFocus.h=NULL; 
}

/************************************************************************/
/*����ԭ�ͣ�LNode* deleteNode(LNode* header)							*/                                                                   
/*�������������ͷ���ָ��												*/                                                                   
/*�� �� ֵ����ժ�½��											   		*/                                                                   
/*�������ܣ�ժ�������һ�����											*/                                                                   
/************************************************************************/	
LNode* deleteNode(LNode* header){
 
	LNode* node;
	if (!header->next)
		return NULL;
	
	node=header->next;
	header->next=node->next;
	node->next=NULL;
	header->index--;

	return node;
}

/************************************************************************/
/*����ԭ�ͣ�void detachNode(LNode* header,int x,int y)					*/                                                                   
/*�������������ͷ���ָ��,X����,Y����									*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ�ժ�������һ�������Ϊ�ƶ����								*/                                                                   
/************************************************************************/
void detachNode(LNode* header,int x,int y){

	theApp.discFocus.node=deleteNode(header);
	theApp.discFocus.h=header;
	theApp.discFocus.x=x;
	theApp.discFocus.y=y;  
}

/************************************************************************/
/*����ԭ�ͣ�void initList()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ���ʼ����������ͷ���										*/                                                                   
/************************************************************************/
void initList(){

	int i; 
	for (i=0;i<3;i++) 
		theApp.tower[i].header=MakeNode(0);  
}

/************************************************************************/
/*����ԭ�ͣ�void freeList(LNode* header)								*/                                                                   
/*�������������ͷ���ָ��												*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ����һ������												*/                                                                   
/************************************************************************/
void freeList(LNode* header){
	
	LNode *node;
	while (header->next)
	{
		node=header->next;
		header->next=node->next;
		free(node);
	}
	header->index=0;
}
 
/************************************************************************/
/*����ԭ�ͣ�void clearLists()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ������Ϸ����������											*/                                                                   
/************************************************************************/
void clearLists(){
	int i;
	for (i=0;i<3;i++)
	{
		freeList(theApp.tower[i].header);  
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void clearHeaders()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ��ͷ�����ͷ���												*/                                                                   
/************************************************************************/
void clearHeaders(){

	int i;
	for (i=0;i<3;i++)
	{
		free(theApp.tower[i].header);
	}
	 
}

/************************************************************************/
/*����ԭ�ͣ�void clearNodes()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����													   		*/                                                                   
/*�������ܣ��ͷ����н��												*/                                                                   
/************************************************************************/
void clearNodes(){

	clearLists();
	clearHeaders();
	if (theApp.discFocus.node)
	{
		free(theApp.discFocus.node);
	}
}