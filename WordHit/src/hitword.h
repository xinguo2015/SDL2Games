#ifndef __HITWORD_H___
#define __HITWORD_H___

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define InRange(x,a,b)    ((x)>=(a) && (x)<(b))
#define MAX(a,b) ((a)>(b)?(a):(b)) 

typedef int BOOL;
#define FALSE 0  
#define TRUE  1  

typedef enum { // user defined event 
	evtStartGame=1,			// renew a game 
	evtStopMusic,			// stop music
	evtGameFail				// the game is lost 
} UserEvent;

typedef struct
{
	int x;
	int y;
} Coord2D;

typedef struct { 

	SDL_Texture* mTexture;  
	int mWidth;
	int mHeight;
}LTexture;
  
typedef struct{
	LTexture gback;
	int scrollingOffset;
}ScolBack;	//Scrolling Backgrounds

typedef struct{
	LTexture gufo; 
	SDL_Rect rect;	//������ײ���
}UFO;	

typedef struct{
	BOOL valid;
	int frame;
	SDL_Rect rect;
}Explosion;

typedef struct{

	SDL_Rect rect;
	int angle;
	int aim; 
	Coord2D vel; 
}Bomb;

typedef struct 
{
	char entry[20];			/* ��Ŀ, �����20����ĸ; �����ʸպ�20����ĸʱ, ����'\0'���� */
	long lib_offset;		/* ���ʽ��͵�ƫ����(��ƫ������ָ�ֵ������ļ�dict.lib�е�fseek����) */
	short int  xlat_len;	/* ���ʽ���ռ�õ��ֽ��� */
	short int  exam_len;	/* ��������ռ�õ��ֽ��� */
} IDX; 

typedef struct 
{ 
	char word[21];		//��������	
	SDL_Rect rect;		//������ײ���  
} WORD;

typedef struct{
	int hp;			//ʵ������ֵ
	int screen_hp;	//��Ļ��ʾֵ
	LTexture gblood;
	LTexture gbloodBg;
}Blood;

typedef struct
{   
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	SDL_Window *gWindow;
	SDL_Renderer *gRenderer; 
	TTF_Font *gFont;	
	Uint32 timeout;		//���ڶ�ʱ���ɵ���
	Blood blood;
	BOOL gameover;
	//��Ч
	Mix_Music *gMusic;
	Mix_Chunk *wavFire;
	Mix_Chunk *wavBomb;
	//����
	LTexture gbomb;
	LTexture gplanet; 
	LTexture gexplosion;
	LTexture gletters[52];	//26����ĸ��������ɫ����52����ͬ������ַ�
	LTexture gGameOver1;	//��Ϸʧ�ܱ���
	LTexture gGameOver2;	//��Ϸʧ����ʾ

	ScolBack background;
	UFO ufo;
	Bomb bombs[10];			//��Ϸ�����������10���ڵ�ͬʱ����
	int screen_bombs;		//��Ļ���ִ��ڵ���
	Explosion expls[10];	//��ը����֡	 
	int nExpSprite;			//��ը������֡��

	WORD word[25];		// ��ʾ����Ļ�ϵĵ���
	int screen_words;	// ��Ļ������ʾ�ĵ��ʸ���
	int hit,hitlen;		//��ǰƴд���ʵ������±꣬ƴд��ȷ����ĸ�� 
	IDX *pdic;			// �ֵ����׸�����ָ�� 
	int index[26][2];	// index[i][0]: ('a'+i)��ĸ��ͷ���׸��������ֵ��е���� index[i][1]: ('a'+i)��ĸ��ͷ�ĵ��ʸ���       
	    
} MineApp;

extern MineApp theApp;

//=========================������Main.c��ʵ��========================// 
int InitApp();
void CleanApp();

//=========================������Util.c��ʵ��========================//  
int explsWidth();
int explsHeight();
int planetWidth();
int planetHeight();
BOOL LoadMedia();
void MakeRect(SDL_Rect *rect,int x,int y,int w,int h); 
BOOL IsConflict(SDL_Rect rect1,SDL_Rect rect2);

//=========================������LTexture.c��ʵ��====================//  
LTexture load_image(char* path); 
LTexture load_TTF_text( char *text,TTF_Font* gFont,SDL_Color color);
BOOL loadLetters();
void freeLTexture(LTexture *ltexture); 
void renderTexture(LTexture ltexture,int x,int y);

//=========================������Event.c��ʵ��=======================// 
void RunApp();
void postUserEvent(int code);
void routeEvent(SDL_Event* event);
 
//=========================������Draw.c��ʵ��========================// 
void DrawBackground();
void renderApp();
 
//=========================������UFO.c��ʵ��=========================// 
int UFOPosX();
int UFOPosY(); 
int UFOWidth();
int UFOHeight();
int UFOHP();
int UFOScreenHP();
int HPWidth();
int HPHeight();
//=========================������Word.c��ʵ��========================// 
int read_dic(IDX **ppdic); 
int wordX(int index);
int wordY(int index);
int wordWidth(int index);
int wordHeight(int index);  
void generate_one_word();
void delete_one_word(int wordIndex);  
void draw_one_word(int wordIndex);
void updateWords();
void clearWords();

//=========================������Bomb.c��ʵ��========================// 
int bombY(int bombIndex);
int bombX(int bombIndex);
int bombW(int bombIndex);
int bombH(int bombIndex);
int bombAim(int bombIndex);
int bombAngle(int bombIndex);
void fire_a_Bomb(int wordIndex);
void fire_a_Explosion(int x,int y);
void updateBombs();
void clearBombs();

#endif