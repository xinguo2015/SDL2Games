/****************************************************************** 
File name: LTexture.c
Date:	2015/8/9
Description:	���أ��ͷţ�����LTexture 
*******************************************************************/
#include "maze.h"

/************************************************************************/
/*����ԭ�ͣ�void renderTexture(LTexture ltexture,int x,int y)	 		*/                                                                   
/*���������LTexture ltexture,����x,����y								*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ָ��λ�û�������						 					*/                                                                   
/************************************************************************/ 
void renderTexture(LTexture ltexture,int x,int y){

	SDL_Rect srcRect={0,0,ltexture.mWidth,ltexture.mHeight};
	SDL_Rect destRect={x,y,ltexture.mWidth,ltexture.mHeight};

	SDL_RenderCopy(theApp.gRenderer,ltexture.mTexture,&srcRect,&destRect);
}

/********************************************************************************/
/*����ԭ�ͣ�void renderPart(LTexture ltexture,int id,int nsprite,int x,int y)	*/                                                                   
/*���������LTexture ltexture,ͼ��id,��ͬ�������nsprite,����x,����y			*/                                                                   
/*�� �� ֵ����																	*/                                                                   
/*�������ܣ���ָ��λ�û��������е�ָ��������						 			*/                                                                   
/********************************************************************************/ 
void renderPart(LTexture ltexture,int id,int nsprite,int x,int y){

	SDL_Rect srcRect={0,ltexture.mHeight*id/nsprite,ltexture.mWidth,ltexture.mHeight/nsprite};

	SDL_Rect destRect={x,y,ltexture.mWidth,ltexture.mHeight/nsprite};

	SDL_RenderCopy(theApp.gRenderer,ltexture.mTexture,&srcRect,&destRect);
}
  
/************************************************************************/
/*����ԭ�ͣ�LTexture load_image(char* path)								*/                                                                   
/*���������ͼƬ��Դ��Ӳ���ϵ����·��									*/                                                                   
/*�� �� ֵ��LTexture													*/                                                                   
/*�������ܣ�������Ӳ���ϵ�ͼƬ��Դ����������			 				*/                                                                   
/************************************************************************/
LTexture load_image(char* path){

	LTexture ltexture;

	SDL_Surface* loadedSurface=IMG_Load(path);

	if(loadedSurface==NULL)
	{
		printf("Unable to load image %s!SDL Error: %s\n",path,SDL_GetError());
	} 
	else
	{   
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

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
/*����ԭ�ͣ�LTexture load_TTF_text( char *text,TTF_Font* gFont)			*/                                                                   
/*�������������ʾ���ַ�ch,�ı�����gFont								*/                                                                   
/*�� �� ֵ��LTexture													*/                                                                   
/*�������ܣ������ַ�������						 						*/                                                                   
/************************************************************************/  
LTexture load_TTF_text( char *text,TTF_Font* gFont){

	SDL_Surface* textSurface; 
	LTexture textTexture;   
	SDL_Color color={240,0,0,255};

	textSurface = TTF_RenderText_Solid(gFont, text, color );  

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
	return load_TTF_text(numText,theApp.gFont);
} 

/************************************************************************/
/*����ԭ�ͣ�void freeLTexture(LTexture *ltexture)		 				*/                                                                   
/*������������ͷŵ�LTexture											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��ͷ�LTexture��Դ						 					*/                                                                   
/************************************************************************/  
void freeLTexture(LTexture *ltexture){

	if( ltexture->mTexture != NULL ){ 

		SDL_DestroyTexture(ltexture->mTexture);
		ltexture->mWidth=0;
		ltexture->mHeight=0;
		ltexture->mTexture=NULL;
	} 
}













