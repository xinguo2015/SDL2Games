/****************************************************************** 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "Russia.h" 	 

/************************************************************************/
/*����ԭ�ͣ�LTexture load_image(char path[])							*/                                                                   
/*���������ͼƬ��Դ��Ӳ���ϵ����·��									*/                                                                   
/*�� �� ֵ��LTexture													*/                                                                   
/*�������ܣ�������Ӳ���ϵ�ͼƬ��Դ����������			 				*/                                                                   
/************************************************************************/
LTexture load_image(char path[]){

	LTexture ltexture;

	SDL_Surface* loadedSurface=IMG_Load(path);

	if(loadedSurface==NULL)
	{
		printf("Unable to load image %s!SDL Error: %s\n",path,SDL_GetError());
	} 
	else
	{  
		ltexture.mTexture=SDL_CreateTextureFromSurface(theApp.gRenderer,loadedSurface);

		if (ltexture.mTexture==NULL)
		{ 
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
		} 
		else{
			ltexture.mWidth=loadedSurface->w;
			ltexture.mHeight=loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	} 

	return ltexture;	
}

/************************************************************************/
/*����ԭ�ͣ�LTexture load_TTF_Text( char text[])	 					*/                                                                   
/*�������������ʾ���ַ�����											*/                                                                   
/*�� �� ֵ��LTexture													*/                                                                   
/*�������ܣ������ַ���������						 					*/                                                                   
/************************************************************************/  
LTexture load_TTF_text( char *text){

	SDL_Surface* textSurface; 
	LTexture textTexture; 
	SDL_Color textColor = { 240, 240, 0, 255 };  
	textSurface = TTF_RenderText_Solid( theApp.gFont, text, textColor ); 
	if( textSurface != NULL )
	{ 
		textTexture.mTexture = SDL_CreateTextureFromSurface( theApp.gRenderer, textSurface );
		if( textTexture.mTexture == NULL ) 
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() ); 
		else{
			textTexture.mWidth=textSurface->w;
			textTexture.mHeight=textSurface->h;
		}
		SDL_FreeSurface( textSurface );
	}
	else 
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() ); 

	return textTexture;
} 
 
/************************************************************************/
/*����ԭ�ͣ�LTexture load_Number( int num)			 					*/                                                                   
/*�������������ʾ������												*/                                                                   
/*�� �� ֵ��LTexture													*/                                                                   
/*�������ܣ��������ֵ�����							 					*/                                                                   
/************************************************************************/ 
LTexture load_Number( int num){
	 
	char numText[10]; 
	sprintf(numText,"%d",num);   
	return load_TTF_text(numText);
} 
 
/************************************************************************/
/*����ԭ�ͣ�void freeLTexture(LTexture *ltexture)		 				*/
/*������������ͷŵ�LTexture											*/
/*�� �� ֵ����															*/
/*�������ܣ��ͷ�LTexture��Դ						 					*/
/************************************************************************/
void freeLTexture(LTexture *ltexture){

	if (ltexture->mTexture != NULL){

		SDL_DestroyTexture(ltexture->mTexture);
		ltexture->mWidth = 0;
		ltexture->mHeight = 0;
		ltexture->mTexture = NULL;
	}
}

extern char gMediaPath[256];

char * MakePath(char path[], char dir[], char filename[])
{
	strcpy(path,dir);
	return strcat(path, filename);
}

char *FullPath(char filename[])
{
	static char path[256];
	return MakePath(path, gMediaPath, filename);
}


/************************************************************************/
/*����ԭ�ͣ�BOOL LoadMedia()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ��ý����Դ�Ƿ�ȫ�����سɹ�   									*/                                                                   
/*�������ܣ�������Ϸ���õ���ý����Դ					 				*/                                                                   
/************************************************************************/
BOOL LoadMedia(){
	 
	//��������
	theApp.gFont = TTF_OpenFont( FullPath("/media/myFont.ttf"), 28 );
	if( theApp.gFont == NULL ) 
	{
		printf("Failed to load TTF");
		return FALSE;
	} 
	  
	//������Ϸ��������
	theApp.imgBackground=load_image(FullPath("/media/pics/background.jpg") );
	if (!theApp.imgBackground.mTexture)
	{
		printf("Failed to load imgBackground");
		return FALSE;
	}
	
	//����ʧ������
	theApp.imgFail=load_image(FullPath("/media/pics/failbg.jpg") );
	if (!theApp.imgFail.mTexture)
	{
		printf("Failed to load failbg");
		return FALSE;
	}
	
	//���ط�������
	theApp.imgBox=load_image(FullPath("/media/pics/box.jpg") );
	if (!theApp.imgBox.mTexture)
	{
		printf("Failed to load imgBox");
		return FALSE;
	} 
	 
	//���ؿ�ʼ������
	theApp.StartBtn.ltexture=load_image(FullPath("/media/pics/startPic.png") );
	if (!theApp.StartBtn.ltexture.mTexture)
	{
		printf("Failed to load StartBtn");
		return FALSE;
	} 
	 
	//������ͣ������
	theApp.StopBtn.ltexture=load_image(FullPath("/media/pics/stopPic.png") );
	if (!theApp.StopBtn.ltexture.mTexture)
	{
		printf("Failed to load StopBtn");
		return FALSE;
	}  
	 
	//�����˳�������
	theApp.QuitBtn.ltexture=load_image(FullPath("/media/pics/quitPic.png") );
	if (!theApp.QuitBtn.ltexture.mTexture)
	{
		printf("Failed to load QuitBtn");
		return FALSE;
	}
	//����ͼ�����ʱ����Ƶ
	theApp.audio_attach = Mix_LoadWAV( FullPath("/media/audio/attach.wav") );
	if( !theApp.audio_attach)
	{
		printf( "Failed to load attatch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}
	//���������밴ťʱ����Ƶ
	theApp.audio_levelUp = Mix_LoadWAV( FullPath("/media/audio/levelUp.wav") );
	if( !theApp.audio_levelUp)
	{
		printf( "Failed to load levelUp sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}
	//������갴�°�ťʱ����Ƶ
	theApp.audio_btnDown = Mix_LoadWAV( FullPath("/media/audio/btnDown.wav") );
	if( !theApp.audio_btnDown)
	{
		printf( "Failed to load btnDown sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}
	//���ص÷�ʱ����Ƶ
	theApp.audio_score = Mix_LoadWAV( FullPath("/media/audio/score.wav") );
	if( !theApp.audio_score)
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	} 
	//����ʧ��ʱ����Ƶ
	theApp.audio_fail = Mix_LoadWAV( FullPath("/media/audio/fail.wav") );
	if( !theApp.audio_fail)
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		return FALSE;
	}

	theApp.nStartBtnSprite=4;
	theApp.nStopBtnSprite=8;
	theApp.nQuitBtnSprite=3; 
	theApp.nBoxSprite=7;

	return TRUE;
}
 
/************************************************************************/
/*����ԭ�ͣ�int BoxWidth()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ��������					   								*/                                                                   
/*�������ܣ���ȡ��Ϸ�е�������Ŀ��									*/                                                                   
/************************************************************************/
int BoxWidth(){ 

	return theApp.imgBox.mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int BoxHeight()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ������߶�					   								*/                                                                   
/*�������ܣ���ȡ��Ϸ�е�������ĸ߶�									*/                                                                   
/************************************************************************/
int BoxHeight(){ 

	return theApp.imgBox.mHeight/theApp.nBoxSprite;
}

/************************************************************************/
/*����ԭ�ͣ�void MakeRect(SDL_Rect *rect,int x,int y,int w,int h)		*/                                                                   
/*������������޸ĵ�SDL_Rect��������x,������y�����w���߶�h				*/                                                                   
/*�� �� ֵ����						   									*/                                                                   
/*�������ܣ��趨���SDL_Rect����������								*/                                                                   
/************************************************************************/
void MakeRect(SDL_Rect *rect,int x,int y,int w,int h){

	rect->x=x;
	rect->y=y;
	rect->w=w;
	rect->h=h; 
}

/************************************************************************/
/*����ԭ�ͣ�BOOL IsConflict(int BlockIndex,int x,int y)					*/                                                                   
/*�����������״������BlockIndex��������x,������y						*/                                                                   
/*�� �� ֵ���г�ͻ����TRUE,�޳�ͻ����FALSE								*/                                                                   
/*�������ܣ��ж���״�Ƿ��ܴ��������꣨x,y����							*/                                                                   
/************************************************************************/ 
BOOL IsConflict(int BlockIndex,int x,int y){

	int i;   
	for (i=0;i<=7;i +=2)
	{
		//**1.�������ұ߽����ͻ**/
		if (arrayBLOCK[BlockIndex].arrXY[i]+x<1||arrayBLOCK[BlockIndex].arrXY[i]+x>BOARD_WIDTH)
			return TRUE;

		/**2.������黹û������Ϸ��壬�򲻱ؼ��**/
		if (arrayBLOCK[BlockIndex].arrXY[i+1]+y<1)
			continue;

		/**3.�÷��鵱ǰλ���Ѵ�������Ϸ����У��򷵻س�ͻ**/
		if (theApp.Gameboard[arrayBLOCK[BlockIndex].arrXY[i]+x][arrayBLOCK[BlockIndex].arrXY[i+1]+y]>BOX_BLANK)
			return TRUE;
	}
	return FALSE;
}

/************************************************************************/
/*����ԭ�ͣ�void KillLine(int y)										*/                                                                   
/*���������������y														*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ȥ��y��													*/                                                                   
/************************************************************************/  
void KillLine(int y){

	int i,j;
	for (j=y;j>=1;j--) 
		for (i=1;i<=BOARD_WIDTH;i++) 
			theApp.Gameboard[i][j]=theApp.Gameboard[i][j-1];  
}

/************************************************************************/
/*����ԭ�ͣ�BOOL IsLineFull(int y)										*/                                                                   
/*���������������y														*/                                                                   
/*�� �� ֵ����������TURE,���򷵻�FALSE									*/                                                                   
/*�������ܣ��жϵ�y���Ƿ��ѱ����� 										*/                                                                   
/************************************************************************/ 
BOOL IsLineFull(int y){

	int i;
	for(i=1;i<=BOARD_WIDTH;i++)
		if (theApp.Gameboard[i][y]==BOX_BLANK)
			return FALSE;
	return TRUE;	
}

/************************************************************************/
/*����ԭ�ͣ�int KillLines(int y)										*/                                                                   
/*���������������y														*/                                                                   
/*�� �� ֵ����ȥ������													*/                                                                   
/*�������ܣ���ȥ��y���Լ���y��֮�������ı���������						*/                                                                   
/************************************************************************/  
int KillLines(int y){

	int i,LinesKilled=0;

	for(i=0;i<4;i++)
	{
		while (IsLineFull(y))
		{
			KillLine(y);
			LinesKilled++;
			i++; 
		}
		y--;
		if (y<1)
			break; 
	}
	return LinesKilled;
}
 
/************************************************************************/
/*����ԭ�ͣ�BOOL IsGameOver()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����Ϸ��������TRUE,���򷵻�FALSE								*/                                                                   
/*�������ܣ��ж���Ϸ�Ƿ����											*/                                                                   
/************************************************************************/  
BOOL IsGameOver(){
	int i;
	for (i=1;i<=BOARD_WIDTH;i++)
	{
		if(theApp.Gameboard[i][1])
			return TRUE;
	}
	return FALSE;
}			

/************************************************************************/
/*����ԭ�ͣ�int IsTimeUp(int timecount)									*/                                                                   
/*���������ʱ��(��λ����)												*/                                                                   
/*�� �� ֵ��ʱ����ָ��ֵ�򷵻�TRUE.���򷵻�FALSE 						*/                                                                   
/*�������ܣ��жϿ�ʼ��ʱ��ʱ�����Ƿ񳬹�ָ��ֵ						*/                                                                   
/************************************************************************/ 
 BOOL IsTimeUp(int timecount){  

	 if ( (SDL_GetTicks()-theApp.time)>timecount)
	 {
		 theApp.time=SDL_GetTicks();
		 return TRUE;
	 }

	 return	FALSE; 
 }

 /************************************************************************/
 /*����ԭ�ͣ�BOOL HitRectTest(int x,int y,SDL_Rect rect)				 */                                                                   
 /*���������X���꣬Y���꣬��������										 */                                                                   
 /*�� �� ֵ�������ھ��������ڷ���TRUE�����򷵻�FALSE 					 */                                                                   
 /*�������ܣ��ж������Ƿ��ھ���������									 */                                                                   
 /************************************************************************/ 
 BOOL HitRectTest(int x,int y,SDL_Rect rect){

	 return (x>=rect.x && y>=rect.y && x<rect.x+rect.w && y<rect.y+rect.h);
 }

 /************************************************************************/
 /*����ԭ�ͣ�void* getFocus()											 */                                                                   
 /*�����������															 */                                                                   
 /*�� �� ֵ��ָ��ǰ��ԾBUTTON��ָ��  									 */                                                                   
 /*�������ܣ���ȡָ��ǰ�������BUTTON��ָ��						 */                                                                   
 /************************************************************************/ 
 void* getFocus(){

	 return theApp.pFocus;
 }
  
 /************************************************************************/
 /*����ԭ�ͣ�void* setFocus												 */                                                                   
 /*���������ָ��ǰ��ԾBUTTON��ָ�� 									 */                                                                   
 /*�� �� ֵ��ָ��ǰ��ԾBUTTON��ָ��  									 */                                                                   
 /*�������ܣ��趨pFocuseָ��ΪpCtrl										 */                                                                   
 /************************************************************************/ 
 void* setFocus(void* pCtrl){

	 theApp.pFocus=pCtrl;

	 return pCtrl;
 }
