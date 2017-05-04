#include "Russia.h" 	
 
char gMediaPath[256] = "";
extern char * MakePath(char path[], char dir[], char filename[]);
extern char *FullPath(char filename[]);

MineApp theApp;

Block arrayBLOCK[19]={ 
	/* x1,y1,x2,y2,x3,y3,x4,y4,boxtype,next*/
	{0,-2,0,-1,0,0,1,0,BOX_BLUE,1},		/**��һ����״**/
	{-1,0,0,0,1,-1,1,0,BOX_BLUE,2},
	{0,-2,1,-2,1,-1,1,0,BOX_BLUE,3},
	{-1,-1,-1,0,0,-1,1,-1,BOX_BLUE,0},

	{0,-2,0,-1,0,0,1,-2,BOX_PINK,5},	/**�ڶ�����״**/
	{-1,-1,-1,0,0,0,1,0,BOX_PINK,6},
	{0,0,1,-2,1,-1,1,0,BOX_PINK,7},
	{-1,-1,0,-1,1,-1,1,0,BOX_PINK,4},

	{-1,0,0,-1,0,0,1,0,BOX_YELLOW,9},	/**��������״**/
	{-1,-1,0,-2,0,-1,0,0,BOX_YELLOW,10},
	{-1,-1,0,-1,0,0,1,-1,BOX_YELLOW,11},
	{0,-2,0,-1,0,0,1,-1,BOX_YELLOW,8},

	{-1,0,0,-1,0,0,1,-1,BOX_GREEN,13},	/**��������״**/
	{0,-2,0,-1,1,-1,1,0,BOX_GREEN,12},

	{-1,-1,0,-1,0,0,1,0,BOX_RED,15},	/**��������״**/
	{0,-1,0,0,1,-2,1,-1,BOX_RED,14},

	{0,-3,0,-2,0,-1,0,0,BOX_ORANGE,17},	/**��������״**/
	{-1,0,0,0,1,0,2,0,BOX_ORANGE,16},

	{0,-1,0,0,1,-1,1,0,BOX_CYAN,18}		/**��������״**/

};


/************************************************************************/
/*����ԭ�ͣ�void CalcLayout()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��趨��Ϸ�а�ť���ȼ��ͼƷֵ�rect			 				*/                                                                   
/************************************************************************/
void CalcLayout(){
	
	MakeRect(&theApp.StartBtn.rect,400,290,ButtonWidth(),ButtonHeight());
	MakeRect(&theApp.StopBtn.rect,400,345,ButtonWidth(),ButtonHeight());
	MakeRect(&theApp.QuitBtn.rect,400,400,ButtonWidth(),ButtonHeight()); 
}

/************************************************************************/
/*����ԭ�ͣ�void InitApp(int argc,char* args[])							*/                                                                   
/*��������������ṩ������Ĳ���										*/                                                                   
/*�� �� ֵ����ʼ���Ƿ�ɹ�												*/
/* �������ܣ���ʼ����Ϸ���ݣ�������������Ⱦ�����趨��ť���Ʒֵ�λ��		*/                                                                   
/************************************************************************/
BOOL InitApp(int argc,char* args[]){
	  
	 //��ʼ��SDL 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO )<0)
	{
		printf("SDL could not initialize! SDL error:%s\n",SDL_GetError());
		return FALSE;
	} 
	//������Ϸ����
	theApp.gWindow=SDL_CreateWindow("Tetris",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
	if (theApp.gWindow==NULL)
	{
		printf("Fail to create SDL window! SDL error:%s\n",SDL_GetError());
		return FALSE;			
	} 
	//������Ϸ���ڵ���Ⱦ��
	theApp.gRenderer=SDL_CreateRenderer(theApp.gWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(theApp.gRenderer==NULL)
	{
		printf("Failed to create renderer!SDL Error:%s\n",SDL_GetError());
		return FALSE;
	}
	//����PNG��JPGͼƬ����ģʽ 
	if (!(IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) & (IMG_INIT_PNG|IMG_INIT_JPG)))
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return FALSE;
	}
	//��ʼ��SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		return FALSE;
	}

	//��ʼ��SDL_mixer 
	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 512 ) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}
	  
	//����ý����Դ
	if (!LoadMedia())
	{
		printf("Failed in loading media!\n");
		return FALSE;
	}
	 
	//�趨��ť���Ʒֺ��Ѷȵȼ���rect
	CalcLayout();
	theApp.gamestate=NotStart;
	return TRUE; 
	
}

/************************************************************************/
/*����ԭ�ͣ�void StartGame()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/
/* �������ܣ�ÿ����Ϸ��ʼǰ��ʼ����Ϸ״̬���ȼ�������������				*/                                                                   
/************************************************************************/
void StartGame(){

	int i,j; 
	/*��ʼ��������Ϸ��������*/
	for (j=0;j<=BOARD_HEIGHT;j++)
		for (i=0;i<BOARD_WIDTH+2;i++)
		{
			if (i==0 || i==BOARD_WIDTH+1)
				theApp.Gameboard[i][j]=BOX_BLUE;
			else
				theApp.Gameboard[i][j]=BOX_BLANK;
		}
	for (i=0;i<BOARD_WIDTH+2;i++)
		theApp.Gameboard[i][BOARD_HEIGHT+1]=BOX_BLUE;
	  
	/*��ʼ���÷�,�ȼ���������״������*/ 
	resetLevel();
	resetScore(); 
	resetShape();
}

/************************************************************************/
/*����ԭ�ͣ�void CleanApp()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��ͷų�����Դ					 							*/                                                                   
/************************************************************************/
void CleanApp(){
	 
	Mix_FreeChunk( theApp.audio_attach );
	theApp.audio_attach = NULL;
	Mix_FreeChunk( theApp.audio_score );
	theApp.audio_score = NULL;
	Mix_FreeChunk( theApp.audio_levelUp );
	theApp.audio_levelUp = NULL; 
	Mix_FreeChunk( theApp.audio_btnDown );
	theApp.audio_btnDown = NULL; 
	Mix_FreeChunk( theApp.audio_fail );
	theApp.audio_fail = NULL;

	freeLTexture(&theApp.StartBtn.ltexture);
	freeLTexture(&theApp.StopBtn.ltexture);
	freeLTexture(&theApp.QuitBtn.ltexture);
	freeLTexture(&theApp.imgBackground);
	freeLTexture(&theApp.imgBox);
	freeLTexture(&theApp.Score.ltexture);
	freeLTexture(&theApp.Level.ltexture);

	TTF_CloseFont( theApp.gFont ); 
	SDL_DestroyWindow(theApp.gWindow);
	SDL_DestroyRenderer(theApp.gRenderer);
	theApp.gFont = NULL;
	theApp.gWindow=NULL;
	theApp.gRenderer=NULL;
	
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

/************************************************************************/
/*����ԭ�ͣ�int main(int argc,char* args[]) 							*/                                                                   
/*����������������������Ĳ���										*/                                                                   
/*�� �� ֵ���Ƿ������˳�												*/                                                                   
/*�������ܣ���ں���,��������˹��������������			 				*/                                                                   
/************************************************************************/
int main(int argc,char* args[])
{   
	if( argc>1 ) 
		strcpy(gMediaPath, args[1]);
	else {
		strcpy(gMediaPath, SDL_GetBasePath());
		strcat(gMediaPath, "../");
	}
	printf("base path = %s\n", SDL_GetBasePath());
	printf("media path = %s\n", gMediaPath);
	   
	if (!InitApp(argc,args))
	{  
		printf("Fail to InitApp!\n");
		return FALSE;
	}   
	RunApp();  
	CleanApp();  
	return 0; 
}

