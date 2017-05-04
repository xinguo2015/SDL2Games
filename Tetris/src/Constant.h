#ifndef _CONSTANT_H_
#define _CONSTANT_H_ 
#define BOXSIZE 20		/**ÿ������ռ20������**/
#define BOARD_WIDTH 12	/**��Ϸ���Ŀ�ȣ���һ������Ŀ��Ϊ��λ**/
#define BOARD_HEIGHT 22	/**��Ϸ���ĸ߶ȣ���һ������Ŀ��Ϊ��λ**/
#define SCREEN_WIDTH 640	/**��Ϸ��Ļ�Ŀ�ȣ���һ������Ϊ��λ**/
#define SCREEN_HEIGHT 480	/**��Ϸ��Ļ�ĸ߶ȣ���һ������Ϊ��λ**/
 
typedef int BOOL;
#define FALSE 0  
#define TRUE  1   

typedef enum{
	NotStart,
	Activate,
	Pause,
	Terminate
}GameState;

typedef enum{	 
	strExpose=0,		//������ʾ��ť
	strOver,		//��꾭����ť
	strDown,		//��ť�ѱ�����
	strFix,			//��Ϸ�Ѿ���ʼ����ť���ɲ��� 
}StartBtnState;

typedef enum{	 
	stpExpose=0,		//��ʾ��ͣ	 
	stpOver,		 
	stpDown,	
	rsmExpose,		//��ʾ����
	rsmOver,		 
	rsmDown,
	retExpose,		//��ʾ����
	retOver
}StopBtnState;

typedef enum{	 
	qtExpose=0,		//������ʾ�˳� 
	qtOver,			//��꾭���˳�
	qtDown			//��ť�ѱ����� 
}QuitBtnState;
 
typedef enum{ 
	BOX_BLANK=0,	/*�շ��飨��ʾ��ǰλ��û�з��飩*/
	BOX_BLUE,	 	
	BOX_CYAN,
	BOX_GREEN,
	BOX_PINK,
	BOX_RED,
	BOX_YELLOW,
	BOX_ORANGE
} BoxType;

typedef struct {
	int arrXY[8];
	BoxType boxtype;
	int nNext;
} Block;

typedef struct  
{ 
	int nCurrent_block_index;     
	int nNext_block_index;  
	BOOL bAccel;
	int X;
	int Y; 
}Shape; 

typedef struct {

	SDL_Texture* mTexture; 
	int mWidth;
	int mHeight;
}LTexture;

typedef struct  {
	SDL_Rect rect;//dstRect
	int data;
	LTexture ltexture;
}ImageButton;
 
typedef struct{
	
	SDL_Window *gWindow;
	SDL_Renderer *gRenderer;   
	TTF_Font *gFont;  
	Uint32 time;

	LTexture imgBackground; 
	LTexture imgFail; 
	LTexture imgBox;
	Shape shape;
	ImageButton StartBtn;
	ImageButton StopBtn;
	ImageButton QuitBtn;
	ImageButton Score;
	ImageButton Level;

	int nStartBtnSprite;
	int nStopBtnSprite;
	int nQuitBtnSprite;
	int nBoxSprite;

	Mix_Chunk *audio_attach;
	Mix_Chunk *audio_levelUp;
	Mix_Chunk *audio_btnDown;
	Mix_Chunk *audio_score;
	Mix_Chunk *audio_fail;
	
	void* pFocus;
	GameState gamestate;
	BoxType Gameboard[BOARD_WIDTH+2][BOARD_HEIGHT+2];
	

}MineApp; 

extern MineApp theApp;
 
extern Block arrayBLOCK[19];/**��Ϸ���ܹ���19�ֲ�ͬ����״**/
 
#endif