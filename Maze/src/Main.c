/****************************************************************** 
File name: Main.c
Date: 2015/8/7
Description:	���ļ� 
				�Թ������㷨�ο�//http://dourok.info/2011/07/14/maze-generation-algorithm/
*******************************************************************/
#include "maze.h"

char gMediaPath[256] = "../Games/HanoiTower";
extern char * MakePath(char path[], char dir[], char filename[]);
extern char *FullPath(char filename[]);
MineApp theApp; 

  
/************************************************************************/
/*����ԭ�ͣ�void CalcLayout()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ��ʱ��,��ť��Rect						 			*/                                                                   
/************************************************************************/
void CalcLayout()
{  
	int x,y;
	
	//��ʱ��λ��X���������
	x=SCREEN_WIDTH/2-btnW()/2;
	y=partH()/2-btnH()/2;
	MakeRect(&theApp.timeBtn.rect, x, y, btnW(), btnH());
	
	//�Զ���ʾ��ťλ��������ť���м�
	x=SCREEN_WIDTH*3/4-btnW()*3/4-3;
	MakeRect(&theApp.autoBtn.rect, x, y, btnW(), btnH()); 

	
	//���ٲ��Ű�ť���Զ���ʾ��ť���
	x=SCREEN_WIDTH*3/4-btnW()*3/4-13;
	MakeRect(&theApp.upBtn.rect, x, y, btnW()/2, btnH()); 

	//���ٲ��Ű�ť���Զ���ʾ��ť�Ҳ�
	x=SCREEN_WIDTH*3/4+7;
	MakeRect(&theApp.downBtn.rect, x, y, btnW()/2, btnH()); 
	

	//�ֶ�������ťλ����Ļ�Ҷ�
	x=SCREEN_WIDTH-btnW()-6;
	MakeRect(&theApp.manualBtn.rect, x, y, btnW(), btnH());
}

/************************************************************************/
/*����ԭ�ͣ�BOOL goMaze(int r,int c)									*/                                                                   
/*����������Ϲ�����λ�ö�ӦGameBoard������кţ��к�					*/                                                                   
/*�� �� ֵ����ǰλ����ͨ�����ڵ�·���Ϸ���TRUE,���򷵻�FALSE			*/
/*�������ܣ��Թ��ݹ�Ѱ·����											*/                                                                   
/************************************************************************/
BOOL goMaze(int r,int c)
{    
	theApp.GameBoard[r][c]=STEP;
	//�����Թ�����
	if (IsSucceed()) 
	{ 
		theApp.OnTheWay=TRUE; 
	}
		 
	//�ж������Ƿ���·
	if (!theApp.OnTheWay && theApp.GameBoard[r-1][c]==BLANK)
	{ 
		//�����ƶ�һ��λ��
		moveUp(r*partH());//��Ϊ��Ļ��һ��Ϊ������������Gameboard����ĵ�r-1�д�����Ļ��r��
		if (!goMaze(r-1,c))
		{ //����Ϸ�λ�ò�����ȷ·���У����»���һ��λ��
			moveDown((r+1)*partH());//ͬ��Gameboard����ĵ�r�д�����Ļ��r+1��
		} 
	}  
	//�ж������Ƿ���·
	if (!theApp.OnTheWay && theApp.GameBoard[r+1][c]==BLANK)
	{ 
		moveDown((r+2)*partH());//ͬ��Gameboard����ĵ�r+1�д�����Ļ��r+2��
		if (!goMaze(r+1,c))
		{
			//����·�λ�ò�����ȷ·���У����ϻ���һ��λ��
			moveUp((r+1)*partH());
		} 
	} 
	//�ж������Ƿ���·
	if (!theApp.OnTheWay && theApp.GameBoard[r][c+1]==BLANK)
	{ 
		moveRight((c+1)*partW());
		if (!goMaze(r,c+1))
		{ //����ҷ�λ�ò�����ȷ·���У��������һ��λ��
			moveLeft(c*partW());
		} 
	}  
	//�ж������Ƿ���·
	if (!theApp.OnTheWay && theApp.GameBoard[r][c-1]==BLANK)
	{ 
		moveLeft((c-1)*partW());
		if (!goMaze(r,c-1))
		{ //�����λ�ò�����ȷ·���У����һ���һ��λ��
			moveRight(c*partW());
		} 
	}  
	
	//��λ�ò���ͨ�����ڵ�·����
	if(!theApp.OnTheWay)
		theApp.GameBoard[r][c]=BLANK;

	return theApp.OnTheWay;
}
 
/************************************************************************/
/*����ԭ�ͣ�int threadFunction( void* data )							*/                                                                   
/*���������SDL�̱߳�׼���												*/                                                                   
/*�� �� ֵ��0															*/
/*�������ܣ������߳�ִ���Թ��ݹ�Ѱ·									*/                                                                   
/************************************************************************/
int threadFunction( void* data )
{	
	int row,col; 
	row=pumpkinY()/partH()-1;  
	col=pumpkinX()/partW();		 
	goMaze(row,col); 
	return 0;
}
 
/************************************************************************/
/*����ԭ�ͣ�void InitApp(int argc,char* args[])							*/                                                                   
/*��������������ṩ������Ĳ���										*/                                                                   
/*�� �� ֵ����ʼ���Ƿ�ɹ�												*/
/*�������ܣ���ʼ���������ݣ�����ý����Դ								*/                                                                   
/************************************************************************/
BOOL InitApp(int argc,char* args[]) {
	
	memset(&theApp, 0, sizeof(theApp));
	//��ʼ��SDL 
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO )<0)
	{
		printf("SDL could not initialize! SDL error:%s\n",SDL_GetError());
		return FALSE;
	} 
	//������Ϸ����
	theApp.gWindow=SDL_CreateWindow("Maze",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
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
	 
	LoadMedia(); //����ý����Դ
	CalcLayout();//�趨��ʱ���밴ť��λ�úʹ�С
	postUserEvent(evtStartGame);
	return TRUE; 
}
  
/************************************************************************/
/*����ԭ�ͣ�void CleanApp()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����								 							*/                                                                   
/*�������ܣ��ͷų�����Դ					 							*/                                                                   
/************************************************************************/
void CleanApp()
{     
	int i=0;
	//�ͷų����м��ص�����
	freeLTexture(&theApp.btnLT); 
	freeLTexture(&theApp.partLT); 
	freeLTexture(&theApp.successLT[0]);
	freeLTexture(&theApp.successLT[1]);
	freeLTexture(&theApp.failLT[0]);
	freeLTexture(&theApp.failLT[1]);
	freeLTexture(&theApp.levelLT);
	for (i=0;i<10;i++)
	{
		freeLTexture(theApp.numbersLT+i);
	}
	//�ͷ�SDL_Window��SDL_Renderer
	SDL_DestroyWindow(theApp.gWindow);
	SDL_DestroyRenderer(theApp.gRenderer);
	theApp.gWindow=NULL;
	theApp.gRenderer=NULL;

	TTF_Quit(); 
	IMG_Quit();
	SDL_Quit();
}

/************************************************************************/
/*����ԭ�ͣ�int main(int argc,char* args[]) 							*/                                                                   
/*����������������������Ĳ���										*/                                                                   
/*�� �� ֵ���Ƿ������˳�												*/                                                                   
/*�������ܣ���ں���,������ŵ����������									*/                                                                   
/************************************************************************/
int main( int argc, char* args[] )
{
	if( argc>1 ) 
		strcpy(gMediaPath, args[1]);
	else {
		strcpy(gMediaPath, SDL_GetBasePath());
		strcat(gMediaPath, "../");
	}
	printf("base path = %s\n", SDL_GetBasePath());
	printf("media path = %s\n", gMediaPath);

	if( ! InitApp(argc, args) )
		return 0; 
	
	RunApp();
	CleanApp();
	return 0;
}
