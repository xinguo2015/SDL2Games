/****************************************************************** 
Description�����ļ����������ຯ��������ע���е��׿��ʾ��Ϸ�����ÿ������������ʾ��Щ������ɵ�����
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/


#include "miner.h"

/************************************************************************/
/*����ԭ�ͣ�void draw_cell(int x, int y, int visualIndex)				*/                                                                   
/*�������������X����,Y���꣨�׿��СΪ��λ������ʾ��־visualIndex		*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������ָ���������ָ�����͵��׿�����						*/                                                                   
/************************************************************************/
void draw_cell(int x, int y, int visualIndex)
{ 
	MineField * fld = & theApp.mineField; 
	SDL_Rect srcRect, offset = {0,0,0,0};
	int w = CellsWidth();
	int h = CellsHeight();

	MyDebug(
		if(!InRange(visualIndex,0,theApp.nBombSprite)) 
		{
			printf("Wrong visual index (%d)\n", visualIndex);
			return;
		})

	MakeRect(&srcRect, 0, h*visualIndex, w, h);
	MakeRect(&offset, fld->rect.x + x * w, fld->rect.y + y * h, w, h);
	SDL_RenderCopy(theApp.gRenderer,theApp.imgBombs.mTexture,&srcRect,&offset);  
}

/************************************************************************/
/*����ԭ�ͣ�void DrawField(MineField *fld)								*/                                                                   
/*���������������ָ��													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������������												*/                                                                   
/************************************************************************/
void DrawField(MineField *fld)
{
	MineCell * p = fld->pCells;
	int NX = fld->fldSize[0];
	int NY = fld->fldSize[1];
	int s = fld->state;
	int x, y, vid = 0;

	for( x=0; x<NX; x++ ) for( y=0; y<NY; y++ )
	{
		if( s==sNewGame )
			vid = 0;
		else if( s==sGameOver )
			vid = CellFinalVisualIndex(p[x+y*NX]);
		else 
			vid = CellVisualIndex(p[x+y*NX]);
		draw_cell(x,y,vid);
	}
}

/************************************************************************/
/*����ԭ�ͣ�void DrawFaceButton(ImageButton *b)							*/                                                                   
/*�����������ͨ����ť��ָ��											*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����ƿ�ͨ����ť												*/                                                                   
/************************************************************************/
void DrawFaceButton(ImageButton *b)
{

	SDL_Rect srcRect;
	int h =  FacesHeight(); 

	MakeRect( &srcRect, 0, h*b->data, FacesWidth(), h);
	SDL_RenderCopy(theApp.gRenderer,theApp.imgFaces.mTexture,&srcRect,&b->rect); 
}

/************************************************************************/
/*����ԭ�ͣ�void DrawDigitButton(ImageButton *b)						*/                                                                   
/*������������ֲ�����ָ��												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����ָ��������ֲ��������ʱ����							*/                                                                   
/************************************************************************/
void DrawDigitButton(ImageButton *b)
{
	int g[3] = { MAX(b->data%1000/100,0), MAX(b->data%100/10,0), MAX(b->data%10,0) }, k;
	SDL_Rect srcRect, offset;

	MakeRect(&srcRect, 0, 0, DigitsWidth(), DigitsHeight());
	MakeRect(&offset, 0, 0, DigitsWidth(), DigitsHeight());
	for( k=0; k<3; k++ )
	{ 
		srcRect.y = (theApp.nDigitSprite-1-g[k])*srcRect.h;
		offset.x = b->rect.x + k*srcRect.w;
		offset.y = b->rect.y;
		SDL_RenderCopy(theApp.gRenderer,theApp.imgDigits.mTexture,&srcRect,&offset); 
	}
}

/************************************************************************************************************************/
/*����ԭ�ͣ�void void DrawBumpRect(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 thick, Uint8 dark, Uint8 bright)	*/                                                                   
/*������������Ͻǵ����꣬���½����꣬���ο���thick��������ɫdark��������ɫbright										*/                                                                   
/*�� �� ֵ����																											*/                                                                   
/*�������ܣ����ƾ��ο�										 															*/                                                                   
/************************************************************************************************************************/
void DrawBumpRect(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Sint16 thick, Uint8 dark, Uint8 bright)
{
	Sint16 k;
	for( k=0; k<thick; k++ )
	{ 
		SDL_SetRenderDrawColor( theApp.gRenderer, dark, dark, dark, 0xFF );        
		SDL_RenderDrawLine( theApp.gRenderer, x1+k, y1+k, x2-k, y1+k);
		SDL_RenderDrawLine( theApp.gRenderer, x1+k, y1+k, x1+k, y2-k);
		 
		SDL_SetRenderDrawColor( theApp.gRenderer, bright, bright, bright, 0xFF );        
		SDL_RenderDrawLine( theApp.gRenderer, x1+k, y2-k, x2-k, y2-k);
		SDL_RenderDrawLine( theApp.gRenderer, x2-k, y1+k, x2-k, y2-k);  
	}
}

/************************************************************************/
/*����ԭ�ͣ�void DrawFrames()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ����Ŀ��								 			*/                                                                   
/************************************************************************/
void DrawFrames()
{
	Sint16 x1, y1, x2, y2;
	Sint16 ext=3, thick=3;
	Uint8 g1 = 130;
	Uint8 g2 = 250;

	x1 = theApp.mineField.rect.x - ext;
	x2 = theApp.mineField.rect.x + theApp.mineField.rect.w + ext;
	// bottom rect 
	y1 = theApp.mineField.rect.y - ext;
	y2 = theApp.mineField.rect.y + theApp.mineField.rect.h + ext;
	DrawBumpRect(x1,y1,x2,y2, thick, g1, g2);
	// top rect
	y1 = theApp.taskButton.rect.y - ext-5;
	y2 = theApp.taskButton.rect.y + theApp.taskButton.rect.h + ext+5;
	DrawBumpRect(x1,y1,x2,y2, thick, g1, g2);
	// small rect around task and time button
	ext = 2;
	thick = 2;
	y1 = theApp.taskButton.rect.y - ext;
	y2 = theApp.taskButton.rect.y + theApp.taskButton.rect.h + ext;
	// rect around task
	x1 = theApp.taskButton.rect.x - ext;
	x2 = theApp.taskButton.rect.x + theApp.taskButton.rect.w + ext;
	DrawBumpRect(x1,y1,x2,y2, thick, g1, g2);
	// rect around time
	x1 = theApp.timeButton.rect.x - ext;
	x2 = theApp.timeButton.rect.x + theApp.timeButton.rect.w + ext;
	DrawBumpRect(x1,y1,x2,y2, thick, g1, g2);
}

/************************************************************************/
/*����ԭ�ͣ�void renderApp()											*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�������Ϸ�����е�ȫ������									*/                                                                   
/************************************************************************/
void renderApp(){

	SDL_SetRenderDrawColor(theApp.gRenderer,0xC0,0xC0,0xC0,0xFF);
	SDL_RenderClear(theApp.gRenderer);
	  
	DrawFrames(); 

	DrawField(&theApp.mineField); 
	DrawFaceButton(&theApp.faceButton);
	DrawDigitButton(&theApp.timeButton);
	DrawDigitButton(&theApp.taskButton);

	SDL_RenderPresent(theApp.gRenderer);

}
