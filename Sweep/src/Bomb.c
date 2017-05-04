/****************************************************************** 
Author: ���¹���֣����
EMAIL��xgliu@cad.zju.edu.cn
*******************************************************************/
#include "miner.h"

/************************************************************************/
/*����ԭ�ͣ�void GenerateRandomBombs(MineField *fld)					*/                                                                   
/*���������������ָ��													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ����׿�������������ɵ��׵�λ��								*/                                                                   
/************************************************************************/
void GenerateRandomBombs(MineField *fld)
{
	int N = fld->fldSize[2];
	int n = fld->bombCount, j, k;
	MineCell *p = fld->pCells;
	 
	if( !p ) return;
	memset(p,0,sizeof(MineCell)*N);
	srand((int)time(NULL));
	for( j = 0; j < n; j++ )
	{
		do { 
			k = rand()%N;
		} while( IsBomb(p[k].data) );
		p[k].data = BOMB;
	}
}

/************************************************************************/
/*����ԭ�ͣ�void CalcNeighbors(MineField *fld)							*/                                                                   
/*���������������ָ��													*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ�����λ��ȷ���󣬼���ÿ��λ����Χ���׵�����					*/                                                                   
/************************************************************************/
void CalcNeighbors(MineField *fld)
{
	int SX = fld->fldSize[0];
	int SY = fld->fldSize[1];
	int x, y, nx, ny, sum;
	MineCell *p = fld->pCells;
	for( x=0; x<SX; x++ ) for( y=0; y<SY; y++ )
	{
		if( IsBomb(p[FlatIndex(x,y,SX)].data) )
			continue;
		sum = 0; 
		for( nx = x-1; nx<x+2; nx++ ) for( ny=y-1; ny<y+2; ny++ )
		{
			if( nx==x && ny==y ) continue;
			if( nx<0 || nx>=SX ) continue;
			if( ny<0 || ny>=SY ) continue;
			sum += IsBomb(p[FlatIndex(nx,ny,SX)].data);
		}
		p[FlatIndex(x,y,SX)].data = (char)sum;
	}
}

/********************************************************************************************/
/*����ԭ�ͣ�BOOL ConstructField(MineField * fld, int fldSizeX, int fldSizeY, int bombCount)	*/                                                                   
/*���������������ָ�룬������ȣ��߶ȣ���һ���׿�Ϊ��λ�������׸���						*/                                                                   
/*�� �� ֵ�������ɹ�����TRUE,���򷵻�FALSE													*/                                                                   
/*�������ܣ������������������������׿������ڴ�												*/                                                                   
/********************************************************************************************/
BOOL ConstructField(MineField * fld, int fldSizeX, int fldSizeY, int bombCount)
{
	if( fldSizeX<0 || fldSizeY<0 || fldSizeX>MAX_FIELD || fldSizeY>MAX_FIELD )
	{
		printf("Mine Field is too big to construct\n");
		return FALSE;
	}
	if( bombCount<0 || bombCount>fldSizeX*fldSizeY/2 )
	{
		printf("Too many bombs to construct\n");
		return FALSE;
	}

	fld->fldSize[0] = fldSizeX;
	fld->fldSize[1] = fldSizeY;
	fld->fldSize[2] = fldSizeX * fldSizeY;
	fld->bombCount = bombCount;
	if( ! (fld->pCells = (MineCell*)calloc(fldSizeX*fldSizeY, sizeof(MineCell))) )
	{
		printf("Failed to allocate mine field\n");
		return FALSE;
	}
	return TRUE;
}

/************************************************************************/
/*����ԭ�ͣ�int CellFinalVisualIndex(MineCell p)						*/                                                                   
/*����������׿�														*/                                                                   
/*�� �� ֵ����ʾ��־													*/                                                                   
/*�������ܣ�������Ϸ����ʱ���׿����ʾ��־�������趨����				*/                                                                   
/************************************************************************/
int CellFinalVisualIndex(MineCell p)
{
	if( IsBomb(p.data) )
	{
		if( p.state==csRevealed || p.state==csAutomated ) return cvRedBomb;
		if( p.state==csBombFlag)  return cvFlag;
		return cvBomb;
	}
	if( p.state==csBombFlag) return cvWrongBomb;
	if( p.state==csQuestioned ) return cvQsMark;
	if( p.state==csRevealed || p.state==csAutomated )
		return 15-p.data;
	return cvCovered;
}

/************************************************************************/
/*����ԭ�ͣ�int CellVisualIndex(MineCell p)								*/                                                                   
/*����������׿�														*/                                                                   
/*�� �� ֵ����ʾ��־													*/                                                                   
/*�������ܣ������׿鵱ǰ״̬������ʾ��־�������趨����				*/                                                                   
/************************************************************************/
int CellVisualIndex(MineCell p)
{
	switch( p.state )
	{
	case csCovered:    return 0;
	case csBombFlag:   return 1;
	case csQuestioned: return 2;
	case csPressed:    return 15;
	case csPressedQ:   return 6;
	case csRevealed:
	case csAutomated:   
		if( IsBomb(p.data) ) return 5;
		return (15-p.data);
	}
	return 0;
}

/************************************************************************/
/*����ԭ�ͣ�void DestroyField(MineField *fld)							*/                                                                   
/*���������ָ��������ָ��												*/                                                                   
/*�� �� ֵ����															*/                                                                   
/*�������ܣ��ͷ��������ڴ�												*/                                                                   
/************************************************************************/
void DestroyField(MineField *fld)
{
	if( fld->pCells ) 
		free(fld->pCells);
	memset(fld,0,sizeof(MineField));
}

/************************************************************************/
/*����ԭ�ͣ�BOOL GameOver()												*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����Ϸʧ�ܷ���TRUE,���򷵻�FALSE								*/                                                                   
/*�������ܣ�����ڵ��״��ͷ�����Ϸʧ��									*/                                                                   
/************************************************************************/
BOOL GameOver()
{
	MineField *fld = & theApp.mineField;
	return ( fld->state==sGameOver );
}

/************************************************************************/
/*����ԭ�ͣ�MineCell* GetCellAt(int x, int y)							*/                                                                   
/*���������X����,Y����													*/                                                                   
/*�� �� ֵ��ָ�����������׿��ָ��										*/                                                                   
/*�������ܣ����������������׿�											*/                                                                   
/************************************************************************/
MineCell* GetCellAt(int x, int y)
{
	MineField *fld = & theApp.mineField;
	int cx = (x - fld->rect.x)/CellsWidth();
	int cy = (y - fld->rect.y)/CellsHeight();

	if( InRange(cx,0,fld->fldSize[0]) && InRange(cy,0,fld->fldSize[1]) )
		return (theApp.mineField.pCells+FlatIndex(cx,cy,fld->fldSize[0]));
	return NULL;
}

/************************************************************************/
/*����ԭ�ͣ�MineCell* GetFocusCell()									*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ��ָ��ǰ��Ծ�׿��ָ��  									*/                                                                   
/*�������ܣ���ȡָ��ǰ��������׿��ָ��							*/                                                                   
/************************************************************************/ 
MineCell* GetFocusCell()
{
	return theApp.mineField.pFocus;
}

/************************************************************************/
/*����ԭ�ͣ�MineCell* SetFocusCell(MineCell *pCell)						*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ���׿��ָ��  												*/                                                                   
/*�������ܣ��趨pFocuseָ��ΪpCell										*/                                                                   
/************************************************************************/ 
MineCell* SetFocusCell(MineCell *pCell)
{
	return (theApp.mineField.pFocus=pCell);
}
 
/************************************************************************/
/*����ԭ�ͣ�void OpenCellBlock(MineCell *pCenCell)						*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ����			  												*/                                                                   
/*�������ܣ�ָ���׿���Χ�˸�λ������Ҫ�Զ��򿪵��������				*/                                                                   
/************************************************************************/ 
void OpenCellBlock(MineCell *pCenCell)
{
	MineField *fld = & theApp.mineField;
	Coord2D cd = CellCoord(pCenCell);
	int x, y, bombSum = 0;
	MineCell *p;

	if( !pCenCell ) return;
	if( pCenCell->state!=csRevealed && pCenCell->state!=csAutomated )
		return;
	// checking the condition
	for( x = cd.x-1; x < cd.x+2; x++ )
		for( y = cd.y-1; y < cd.y+2; y++ )
		{
			if( !InRange(x,0,fld->fldSize[0]) || !InRange(y,0,fld->fldSize[1]) )
				continue;
			p = fld->pCells + FlatIndex(x,y,fld->fldSize[0]);
			if( p->state==csBombFlag )
				bombSum++;
		}
		// do NOT match the condition
		if( bombSum != pCenCell->data )
			return; // can not open the 3x3 block

		// set the state to avoid repeating on this cell
		if( pCenCell->state!=csAutomated )	
			pCenCell->state = csAutomated;
		// open the block
		for( x = cd.x-1; x < cd.x+2; x++ )
			for( y = cd.y-1; y < cd.y+2; y++ )
			{
				if( !InRange(x,0,fld->fldSize[0]) || !InRange(y,0,fld->fldSize[1]) )
					continue;
				OpenCell( fld->pCells + FlatIndex(x,y,fld->fldSize[0]) );
			}
}
 
/************************************************************************/
/*����ԭ�ͣ�void PressCell(MineCell *pCell)								*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ��׿�δ�򿪣�����ʱ�޸���״̬ΪcsPressed					*/                                                                   
/************************************************************************/
void PressCell(MineCell *pCell)
{
	if( !pCell ) return;
	if( pCell->state==csPressed )
		return;
	if( pCell->state==csCovered )
		pCell->state = csPressed;
	else if( pCell->state==csQuestioned )
		pCell->state = csPressedQ; 
}

/************************************************************************/
/*����ԭ�ͣ�void MarkCell(MineCell *pCell)								*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ��Ҽ�����׿�ʱ�޸�������									*/                                                                   
/************************************************************************/
void MarkCell(MineCell *pCell)
{
	if( !pCell ) return;

	switch( pCell->state )
	{
	case csCovered:
		pCell->state = csBombFlag;
		postUserEvent(evtMarkMore);
		break;
	case csBombFlag:
		pCell->state = csQuestioned;
		postUserEvent(evtMarkLess);
		break;
	case csQuestioned:
		pCell->state = csCovered;
		break;
	default:
		return;
	} 
}

/************************************************************************/
/*����ԭ�ͣ�void OpenCell(MineCell *pCell)								*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ�������ʾ�׿���ʵ��̬ʱ�Ĵ�����							*/                                                                   
/************************************************************************/
void OpenCell(MineCell *pCell)
{
	if( ! pCell ) return;
	if( pCell->state==csBombFlag  )
		return;
	if( IsBomb(pCell->data) )
	{
		pCell->state = csRevealed;
		Mix_PlayChannel( -1, theApp.audio_bomb, 0 ); 
		postUserEvent(evtStopTimer);
		postUserEvent(evtGameFail);
		return;
	}
	if( pCell->state!=csRevealed && pCell->state!=csAutomated)   
		pCell->state = csRevealed; // the cell is not opened

	if( pCell->data==0 && pCell->state!=csAutomated ) 
	{   // there is no bomb around
		Mix_PlayChannel( -1, theApp.audio_reveal, 0 ); 
		pCell->state = csAutomated;
		// automatically open the neighbor 3x3 block
		OpenCellBlock(pCell); 
	}
}
 
/************************************************************************/
/*����ԭ�ͣ�void ReleaseCell(MineCell *pCell)							*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ����׿鴦�ͷ�ʱ�޸���״̬									*/                                                                   
/************************************************************************/
void ReleaseCell(MineCell *pCell)
{
	if( !pCell ) return;
	if( pCell->state == csPressed ) 
		pCell->state = csCovered;  
	else if( pCell->state == csPressedQ ) 
		pCell->state = csQuestioned;  
}

/************************************************************************/
/*����ԭ�ͣ�void ReleaseCellBlock(MineCell *pCell)						*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ��ͷ�ָ���׿鼰��Χ�˸�λ�õ��׿�							*/                                                                   
/************************************************************************/
void ReleaseCellBlock(MineCell *pCell)
{
	MineField *fld = & theApp.mineField;
	Coord2D cen = CellCoord(pCell);
	int x, y;

	if( !pCell ) return;
	for( x = cen.x-1; x<cen.x+2; x++ )
		for( y = cen.y-1; y<cen.y+2; y++ )
		{
			if( !InRange(x,0,fld->fldSize[0]) || !InRange(y,0,fld->fldSize[1]) )
				continue;
			pCell = fld->pCells+( FlatIndex(x,y,fld->fldSize[0]) );
			ReleaseCell(pCell);
		}
}

/************************************************************************/
/*����ԭ�ͣ�void PressCellBlock(MineCell *pCell)						*/                                                                   
/*����������׿��ָ��													*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ����Խ�ָ���׿鼰��Χ�˸�λ��ȫ���޸�Ϊ����״̬				*/                                                                   
/************************************************************************/
void PressCellBlock(MineCell *pCell)
{
	MineField *fld = & theApp.mineField;
	Coord2D cen = CellCoord(pCell);
	int x, y;

	if( !pCell ) return;
	for( x = cen.x-1; x<cen.x+2; x++ )
		for( y = cen.y-1; y<cen.y+2; y++ )
		{
			if( !InRange(x,0,fld->fldSize[0]) || !InRange(y,0,fld->fldSize[1]) )
				continue;
			pCell = fld->pCells+( FlatIndex(x,y,fld->fldSize[0]) );
			PressCell(pCell);
		}
}

/************************************************************************/
/*����ԭ�ͣ�void LeftPressField(int x, int y, unsigned char flags)		*/                                                                   
/*���������X���꣬Y���꣬���ò���flags									*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ����������������������¼�									*/                                                                   
/************************************************************************/
void LeftPressField(int x, int y, unsigned char flags)
{
	MineField *fld = & theApp.mineField;
	MineCell *pOld = GetFocusCell();
	MineCell *pNow = GetCellAt(x,y);

	switch ( fld->state )
	{
	case sNewGame:
		// start timing
		postUserEvent(evtStartTimer);
	case sWait:	// waiting for user input
		// chane to the state where the left button is down
		fld->state = sLeftDown;
		SetFocusCell(pNow);
		PressCell(pNow);
		break;
	case sRightDown:
		fld->state = sLRDown;
		SetFocusCell(pNow);
		PressCellBlock(pNow);
		break;
	case sGameOver:
		break;
	}
}
 
/************************************************************************/
/*����ԭ�ͣ�void LeftReleaseField(int x, int y, unsigned char flags)	*/                                                                   
/*���������X���꣬Y���꣬���ò���flags									*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ������������������ͷ��¼�									*/                                                                   
/************************************************************************/
void LeftReleaseField(int x, int y, unsigned char flags)
{
	MineField *fld = & theApp.mineField;
	MineCell *pOld = GetFocusCell();
	MineCell *pNow = GetCellAt(x,y);

	switch ( fld->state )
	{
	case sLeftDown:	// waiting for user input
		// chane to the state where the left button is down
		fld->state = sWait;
		OpenCell(pNow);
		break;
	case sLRDown:
		fld->state = sWait;
		ReleaseCellBlock(pOld);
		OpenCellBlock(pNow);
		break;
	case sGameOver:
		break;
	}
}

/************************************************************************/
/*����ԭ�ͣ�void RightPressField(int x, int y, unsigned char flags)		*/                                                                   
/*���������X���꣬Y���꣬���ò���flags									*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ���������������Ҽ������¼�									*/                                                                   
/************************************************************************/
void RightPressField(int x, int y, unsigned char flags)
{
	MineField *fld = & theApp.mineField;
	MineCell *pOld = GetFocusCell();
	MineCell *pNow = GetCellAt(x,y);

	switch ( fld->state )
	{
	case sNewGame:
		// start timing
		postUserEvent(evtStartTimer);
	case sWait:	// waiting for user input
		// chane to the state where the left button is down
		fld->state = sRightDown;
		SetFocusCell(pNow);
		MarkCell(pNow);
		break;
	case sLeftDown:
		fld->state = sLRDown;
		SetFocusCell(pNow);
		PressCellBlock(pNow);
		break;
	}
}

/************************************************************************/
/*����ԭ�ͣ�void RightReleaseField(int x, int y, unsigned char flags)	*/                                                                   
/*���������X���꣬Y���꣬���ò���flags									*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ���������������Ҽ��ͷ��¼�									*/                                                                   
/************************************************************************/
void RightReleaseField(int x, int y, unsigned char flags)
{
	MineField *fld = & theApp.mineField;
	MineCell *pOld = GetFocusCell();
	MineCell *pNow = GetCellAt(x,y);

	switch ( fld->state )
	{
	case sRightDown:
		fld->state = sWait;
		break;
	case sLRDown:
		fld->state = sWait;
		ReleaseCellBlock(pOld);
		OpenCellBlock(pNow);
		break;
	case sLeftDown:
		fld->state = sLRDown;
		PressCellBlock(pNow);
		break;
	}
}

/************************************************************************/
/*����ԭ�ͣ�void MoveOnField(int x, int y, unsigned char flags)			*/                                                                   
/*���������X���꣬Y���꣬���ò���flags									*/                                                                   
/*�� �� ֵ����  														*/                                                                   
/*�������ܣ���������������ƶ��¼�										*/                                                                   
/************************************************************************/
void MoveOnField(int x, int y, unsigned char flags)
{
	MineField *fld = & theApp.mineField;
	MineCell *pOld = GetFocusCell();
	MineCell *pNow = GetCellAt(x,y);
	if( pNow==pOld ) return;

	switch ( fld->state )
	{
	case sLeftDown:
		ReleaseCell(pOld);
		SetFocusCell(pNow);
		PressCell(pNow);
		break;
	case sLRDown:
		ReleaseCellBlock(pOld);
		SetFocusCell(pNow);
		PressCellBlock(pNow);
		break;
	case sRightDown:
		SetFocusCell(pNow);
		break;
	case sGameOver:
		break;
	}
}

/************************************************************************/
/*����ԭ�ͣ�BOOL MissionCompleted()										*/                                                                   
/*�����������															*/                                                                   
/*�� �� ֵ����Ϸ������ɷ���TRUE,���򷵻�FALSE							*/                                                                   
/*�������ܣ��ж���Ϸ�����Ƿ��Ѿ����									*/                                                                   
/************************************************************************/
BOOL MissionCompleted()
{
	MineField *fld = & theApp.mineField;
	MineCell *p = fld->pCells;
	int N = fld->fldSize[2];
	int sum = 0;

	if( theApp.taskButton.data>0 )
		return 0;

	while( N-->0 )
	{
		if( p->state==csRevealed || p->state==csAutomated )
			sum ++;
		p++;
	}
	return ( sum + fld->bombCount == fld->fldSize[2] );
}
