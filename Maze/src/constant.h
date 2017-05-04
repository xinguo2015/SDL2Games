#ifndef _CONSTANT_H_
#define _CONSTANT_H_ 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>  
#include <SDL_thread.h>
 
#define MAXCOST 0x7fffffff
#define SCREEN_WIDTH 630	 
#define SCREEN_HEIGHT 660
#define ROW 10	//ͼ������
#define COL 10	//ͼ������ 
#define TOTAL_TILES (2*ROW+1)*(2*COL+1)-ROW*COL*2+1//��ͼ�е�ǽ������
#define MAX(a,b) a>b?a:b
#define MIN(a,b) a<b?a:b

#define BLANK 0  //��ǵ�ͼ�еĿհ�λ��
#define WALL  1	//��ͼ�е�ǽ	
#define STEP  2 //����߹���λ��

typedef int BOOL;
#define FALSE 0  
#define TRUE  1 

typedef enum { 
	btnExposed=0,			  
	btnDown				  
} BtnState;

typedef enum { 
	sNewGame = 0, 
	sAutoRun,    // �Զ����� 
	sGameFail,   // ��Ϸʧ��
	sGameWin,	 // ��Ϸʤ��
} GameState;	

typedef enum { // user defined event 
	evtStartGame=0,			// renew a game  
	evtStartTimer,			// start timing
	evtStopTimer,			// stop timing 
	evtAutoRun,				// auto run
	evtStopShow,			// stop auto run
	evtGameFail,			// the game is lost
	evtGameWin,				// win the game 
} UserEvent;

typedef struct
{
	SDL_Rect rect;
	int data; // data on the button
} ImageButton;

typedef struct {

	int mWidth;
	int mHeight;
	SDL_Texture* mTexture; 
}LTexture;

typedef struct{

	SDL_Rect rect; 
	int velx;
	int vely;

}Pumpkin;

typedef struct{

	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;   
	TTF_Font *gFont; 
	LTexture btnLT;
	LTexture partLT; 
	int nbtnSprite;
	int npartSprite;
	LTexture levelLT;
	LTexture successLT[2]; //��Ϸʤ������ʾ 
	LTexture failLT[2];	//��Ϸʧ�ܵ���ʾ 
	LTexture numbersLT[10];//0-9�������� 
	int DigitW;	//��λ�������ȣ�ȡ0-9���������ֵ
	int DigitH;	//��λ�������ȣ�ȡ0-9���������ֵ
	 
	int MGraph[ROW*COL][ROW*COL];		//�ڽӾ����������������������Թ��е�����ͨ·
	int GameBoard[ROW*2+1][ROW*2+1];	//��ͼ��־���飬gameboard[i][j]��־��Ϊǽ�ڻ��߿յ�
	SDL_Rect tiles[TOTAL_TILES];		//ǽ�ڵİ�Χ����
	SDL_Rect entryRect;
	SDL_Rect exitRect;

	SDL_TimerID timerID;	 
	ImageButton timeBtn;	//����ʱ��ť	
	ImageButton autoBtn;	//�Զ���ʾ��ť
	ImageButton manualBtn;	//�ֶ�������ť
	ImageButton upBtn;		//���ٲ����Զ���ʾ
	ImageButton downBtn;	//���ٲ����Զ���ʾ
	
	GameState gamestate;
	Pumpkin pumpkin;
	int level;//��Ϸ�Ѷȵȼ� 
	int Speed;
	BOOL autoRun;
	BOOL OnTheWay;	//��Ǵ�λ���Ƿ���ͨ�����ڵ�·����		
	int timeElapse;	//�Զ���ʾʱ���Ϲ�ÿ���ƶ���ʱ����
	void* pFocus;
	SDL_Thread* threadID;

}MineApp; 

extern MineApp theApp;
 
#endif
