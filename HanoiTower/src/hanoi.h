/****************************************************************** 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#ifndef _HANIO_H_
#define _HANIO_H_ 
#include "constant.h"


int threadFunction( void* data );
//==========================������Util.c��ʵ��========================//
BOOL LoadMedia();
void * GetFocus();
void * SetFocus(void * pCtrl);
void* GetControlAt(int x,int y);
BOOL HitRectTest(int x,int y,SDL_Rect rect);
void MakeRect(SDL_Rect *rect,int x,int y,int w,int h);
BOOL IsBeginning();
BOOL IsWinning();
void moves(int t1,int t2);

//==========================������LTexture.c��ʵ��========================//
LTexture load_image(char* path);  
LTexture load_TTF_text( char* text,TTF_Font* gFont,SDL_Color color);
LTexture load_Number( int num);
void freeLTexture(LTexture *ltexture) ;
void renderTexture(LTexture ltexture,int x,int y);

//==========================������Draw.c��ʵ��========================//
void renderApp();

//==========================������Event.c��ʵ��========================//
void postUserEvent(int code);
void RunApp();

//==========================������LNode.c��ʵ��========================//
LNode* MakeNode(int index);
LNode* deleteNode(LNode* header);
void AddNode(LNode* header,LNode *node);
void RejoinNode(int x,int y);
void JoinNode(int t);
void detachNode(LNode* header,int x,int y);
void freeList(LNode* header);
void clearLists();
void initList();
void clearNodes();

//==========================������Mouse.c��ʵ��========================//
void onLButtonDown(void* pCtrl,int x, int y, unsigned char flags);
void onLButtonUp(int x, int y, unsigned char flags);
void onMouseMove(void * pCtrl,int x, int y, unsigned char flags);
void LoseMouse(Button * pCtrl);

//==========================������Disc.c��ʵ��========================//
int discW();
int discWidth();
int discHeight();
int towerWidth();
int towerHeight(); 
void setDiscs(int discs);
void incDiscs();
void decDiscs();
void setMove(int move);
void incMove();
BOOL IsDraging();
void* HitDiscTest(int x,int y);
BOOL IsDiscConflict(int x,int y,int index,SDL_Rect rect);
LNode* FindTouchedTower(int x,int y,int index);

//==========================������Button.c��ʵ��========================//
int btnWidth();
int btnHeight();
void pressBtn(Button *pCtrl);
void releaseBtn(Button* pCtrl);

#endif