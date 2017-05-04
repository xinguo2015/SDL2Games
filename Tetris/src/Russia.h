#ifndef _RUSSIA_H_
#define _RUSSIA_H_ 
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h> 
#include <SDL_mixer.h>
#include "Constant.h"

//=========================������Russia.c��ʵ��=======================// 
void CalcLayout();
BOOL InitApp(int argc,char* args[]); 
void StartGame();
void CleanApp();	 
 
//==========================������Button.c��ʵ��========================// 
int ScoreWidth();
int ScoreHeight(); 
BOOL IsScoreUp();
int LevelWidth();
int LevelHeight();
int getLevel();
int ButtonWidth();
int ButtonHeight();	
void updateLevel();	
void incLevel();
void resetLevel();
void updateScore();						 
void incScore(int increment);
void resetScore();
void* getControlAt(int x,int y);

//==========================������Util.c��ʵ��========================//
LTexture load_image(char path[]);
LTexture load_TTF_text( char text[]);
LTexture load_Number( int num);
void freeLTexture(LTexture *ltexture);
BOOL LoadMedia();
int BoxWidth();
int BoxHeight(); 
void MakeRect(SDL_Rect *rect,int x,int y,int w,int h);
BOOL IsConflict(int BlockIndex,int x,int y); 		 
int KillLines(int y);								 
void KillLine(int y);								 
BOOL IsLineFull(int y);		
BOOL IsGameOver();
BOOL IsTimeUp(int timecount);
BOOL HitRectTest(int x,int y,SDL_Rect rect);
void* getFocus();
void* setFocus(void* pCtrl);

//==========================������Event.c��ʵ��========================// 
void handleEvents(SDL_Event *event); 
void onKeyDown(int key);
void handleUp();
void handleDown();
void handleLeft();
void handleRight(); 
void RunApp();

//==========================������Draw.c��ʵ��========================// 
void drawBackground();
void drawBox(int x,int y,BoxType boxtype); 
void drawBoxes();
void drawBlock(int BlockIndex,int sx,int sy);
void drawShape();
void drawBtn(ImageButton* btn);
void drawLevel();
void drawScore();
void drawButtons();
void drawFailBg();
void renderApp();

//==========================������Shape.c��ʵ��========================// 
void resetShape();
void nextShape();
void setAccel(BOOL accel);
BOOL IsAccel(); 
int getShapeX();
void alterShapeX(int increment);
int getShapeY();	
void alterShapeY(int increment);
int getCurrentBlockID();
void setCurrentBlockID(int blockindex);

//==========================������Mouse.c��ʵ��========================// 
void loseMouse(void* pCtrl);
void onLButtonDown(void *pCtrl);
void onLButtonUp(void* pCtrl);
void onMouseMove(void *pCtrl);

#endif