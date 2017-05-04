/****************************************************************** 
File name: LTexture.c
Date:	2015/7/28
Description:	ʵ�ּ��ش���ɫ�ı���LTexture,����ͼƬ��LTexture 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "hanoi.h"

/************************************************************************/
/*����ԭ�ͣ�void renderTexture(LTexture ltexture,int x,int y)	 		*/                                                                   
/*���������LTexture ltexture,����x,����y								*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ���ָ��λ�û�������						 					*/                                                                   
/************************************************************************/ 
void renderTexture(LTexture ltexture,int x,int y){

	SDL_Rect srcRect={0,0,ltexture.mWidth,ltexture.mHeight},destRect={x,y,ltexture.mWidth,ltexture.mHeight};

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

/********************************************************************************/
/*����ԭ�ͣ�LTexture load_TTF_text( char *text,TTF_Font* gFont,SDL_Color color)	*/                                                                   
/*�������������ʾ���ַ�ch,�ı���ɫcolor										*/                                                                   
/*�� �� ֵ��LTexture															*/                                                                   
/*�������ܣ������ַ�������						 								*/                                                                   
/********************************************************************************/  
LTexture load_TTF_text( char *text,TTF_Font* gFont,SDL_Color color){

	SDL_Surface* textSurface; 
	LTexture textTexture;   
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
	SDL_Color color={255,255,255,255};
	sprintf(numText,"%d",num);   
	return load_TTF_text(numText,theApp.gFont,color);
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
 












