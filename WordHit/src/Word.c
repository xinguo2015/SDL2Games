/******************************************************************
File name: Word.c
Date:	2015/7/19
Description:	ʵ�ּ����ֵ�,������ɵ����Լ��������ʹ����ຯ��
*******************************************************************/
#include "hitword.h"

extern char *FullPath(char filename[]);

/************************************************************************/
/*����ԭ�ͣ�int read_dic(IDX **ppdic)									*/
/*���������ָ���ֵ�ָ���ָ��											*/
/*�� �� ֵ���ֵ��еĵ��ʸ���						   					*/
/*�������ܣ����ֵ��ļ��ж�ȡ���ݵ��ڴ�									*/
/************************************************************************/
int read_dic(IDX **ppdic)
{
	FILE *fp;
	IDX *pdic;
	int len, entries;
	int i, begin;
	fp = fopen(FullPath("/media/dict.idx"), "rb");
	if (fp == NULL)
		return 0;
	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	entries = len / sizeof(IDX);
	pdic = (IDX*)malloc(entries * sizeof(IDX));
	if (pdic == NULL)
		return 0;
	fread(pdic, sizeof(IDX), entries, fp);
	fclose(fp);
	*ppdic = pdic;
	begin = 0;
	for (i = 0; i < 26; i++)
	{
		while (begin < entries)
		{
			if ((pdic[begin].entry[0] | 0x20) == 'a' + i)
				break;
			begin++;
		}
		theApp.index[i][0] = begin;
		if (i > 0)
			theApp.index[i - 1][1] = begin - theApp.index[i - 1][0];
	}
	theApp.index[i - 1][1] = entries - begin;
	return entries;
}

/************************************************************************/
/*����ԭ�ͣ�BOOL all_alpha(char *p)										*/
/*����������ַ���														*/
/*�� �� ֵ���ַ�����ȫ��Сд��ĸ���ɷ���TRUE,���򷵻�FALSE				*/
/*�������ܣ��ж��ַ����Ƿ���Сд��ĸ����								*/
/************************************************************************/
BOOL all_alpha(char *p)
{
	int i, n = strlen(p);
	for (i = 0; i < n; i++)
	{
		if (!islower(p[i]))
			break;
	}
	return i == n;
}

/************************************************************************/
/*����ԭ�ͣ�int letterW(char ch)										*/
/*�����������															*/
/*�� �� ֵ������СдӢ����ĸ������			   						*/
/*�������ܣ���ȡ����СдӢ����ĸ������								*/
/************************************************************************/
int letterW(char ch) {
	int i = ch - 'a';
	return theApp.gletters[i].mWidth;
}

/************************************************************************/
/*����ԭ�ͣ�int letterH()												*/
/*�����������															*/
/*�� �� ֵ������СдӢ����ĸ����߶�			   						*/
/*�������ܣ���ȡ����СдӢ����ĸ����߶�								*/
/************************************************************************/
int letterH() {

	return theApp.gletters[1].mHeight;
}

/************************************************************************/
/*����ԭ�ͣ�int wordX(int index)										*/
/*���������WORD�����±�												*/
/*�� �� ֵ��word[i]��Χ��x����					   						*/
/*�������ܣ���ȡword[i]��Χ��x����										*/
/************************************************************************/
int wordX(int index) {

	return theApp.word[index].rect.x;
}

/************************************************************************/
/*����ԭ�ͣ�int wordX(int index,int x)									*/
/*���������WORD�����±꣬x����											*/
/*�� �� ֵ����					   										*/
/*�������ܣ��趨word[index]��Χ��x����									*/
/************************************************************************/
void setWordX(int index, int x) {

	theApp.word[index].rect.x = x;
}

/************************************************************************/
/*����ԭ�ͣ�int wordX(int index,int y)									*/
/*���������WORD�����±꣬y����											*/
/*�� �� ֵ����					   										*/
/*�������ܣ��趨word[index]��Χ��y����									*/
/************************************************************************/
void setWordY(int index, int y) {

	theApp.word[index].rect.y = y;
}

/************************************************************************/
/*����ԭ�ͣ�int wordY(int index)										*/
/*���������WORD�����±�												*/
/*�� �� ֵ��word[i]��Χ��y����					   						*/
/*�������ܣ���ȡword[i]��Χ��y����										*/
/************************************************************************/
int wordY(int index) {

	return theApp.word[index].rect.y;
}

/************************************************************************/
/*����ԭ�ͣ�int wordWidth(int index)									*/
/*���������WORD�����±�												*/
/*�� �� ֵ��word[i]��Χ�п��					   						*/
/*�������ܣ���ȡword[i]��Χ�п��										*/
/************************************************************************/
int wordWidth(int index) {

	return theApp.word[index].rect.w;
}

/************************************************************************/
/*����ԭ�ͣ�int wordHeight(int index)									*/
/*���������WORD�����±�												*/
/*�� �� ֵ��word[i]��Χ�и߶�					   						*/
/*�������ܣ���ȡword[i]��Χ�и߶�										*/
/************************************************************************/
int wordHeight(int index) {

	return theApp.word[index].rect.h;
}

/************************************************************************/
/*����ԭ�ͣ�void generate_one_word()									*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ��������һ������											*/
/***************************** *******************************************/
void generate_one_word()
{
	int i, j, d, k;
	char ch;
	int mark[26] = { 0 };
	srand((int)time(NULL));
	for (j = 0; j < theApp.screen_words; j++)
	{
		mark[(theApp.word[j].word[0] | 0x20) - 'a'] = 1;
	}
	d = (rand() % 100) & 1;
	if (d == 0)
	{
		for (j = 0; j < 26; j++)
			if (mark[j] == 0)
				break;
	}
	else
	{
		for (j = 25; j >= 0; j--)
			if (mark[j] == 0)
				break;
	}
	do
	{
		i = rand() % (theApp.index[j][1]) + theApp.index[j][0];
	} while (!all_alpha(theApp.pdic[i].entry));

	memset(theApp.word[theApp.screen_words].word, 0, sizeof(WORD));
	for (k = 0; k < 20; k++)
	{
		ch = theApp.pdic[i].entry[k];
		theApp.word[theApp.screen_words].word[k] = ch;
		if (ch == '\0')
			break;
		theApp.word[theApp.screen_words].rect.w += letterW(ch);
	}
	theApp.word[theApp.screen_words].rect.h = letterH();
	setWordX(theApp.screen_words, rand() % (theApp.SCREEN_WIDTH - wordWidth(theApp.screen_words)));
	setWordY(theApp.screen_words, -planetHeight());

	theApp.screen_words++;
}

/************************************************************************/
/*����ԭ�ͣ�void delete_one_word(int index)								*/
/*���������WORD�����±�												*/
/*�� �� ֵ����															*/
/*�������ܣ���������ɾ��ָ���±�ĵ���									*/
/************************************************************************/
void delete_one_word(int wordIndex)
{
	int i;
	if (wordIndex >= theApp.screen_words)
		return;

	//��������ɾ��ָ������
	memcpy(&theApp.word[wordIndex], &theApp.word[wordIndex + 1], sizeof(WORD)*(theApp.screen_words - 1 - wordIndex));
	theApp.screen_words--;

	//�޸�ÿ���ڵ�Ŀ�굥���±�
	for (i = 0; i < theApp.screen_bombs; i++)
	{
		if (bombAim(i) > wordIndex)
			theApp.bombs[i].aim--;
		else if (bombAim(i) == wordIndex)
			theApp.bombs[i].aim = -1;
	}

	//�޸�����ƴд���ʵı��
	if (theApp.hit == wordIndex)
	{
		//���ɾ����������ƴд�еĵ���
		theApp.hitlen = 0;
		theApp.hit = -1;
	}
	if (theApp.hit > wordIndex)
	{
		theApp.hit--;
	}
}

/************************************************************************/
/*����ԭ�ͣ�void draw_one_word(int index)								*/
/*���������WORD�����±�												*/
/*�� �� ֵ����															*/
/*�������ܣ�����ָ���±�ĵ���											*/
/************************************************************************/
void draw_one_word(int wordIndex) {
	int i, j, x, y;
	char* word;
	if (wordIndex >= theApp.screen_words || wordIndex < 0)
		return;
	//���Ƶ��ʱ�����С����
	x = wordX(wordIndex) + wordWidth(wordIndex) / 2 - planetWidth() / 2;
	y = wordY(wordIndex) + wordHeight(wordIndex) / 2 - planetHeight() / 2;
	renderTexture(theApp.gplanet, x, y);
	//��дÿ������
	x = wordX(wordIndex);
	y = wordY(wordIndex);
	word = theApp.word[wordIndex].word;
	for (i = 0; i < strlen(word); i++)
	{
		j = word[i] - 'a';
		//δƴ������ĸ��ʹ�ñ���ɫ
		if (theApp.hit != wordIndex || i >= theApp.hitlen)
			renderTexture(theApp.gletters[j], x, y);
		else//��ƴ������ĸ��ʹ��ǰ��ɫ
			renderTexture(theApp.gletters[j + 26], x, y);
		x += letterW(word[i]);
	}
}

/************************************************************************/
/*����ԭ�ͣ�void updateWords()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ��������е��ʵ���Ϣ											*/
/************************************************************************/
void updateWords() {

	int i;
	//�����ѵ�����Ļ���У�ɾ���õ���
	if (wordY(0) + wordHeight(0) / 2 - planetHeight() / 2 >= theApp.SCREEN_HEIGHT)
		delete_one_word(0);

	for (i = 0; i < theApp.screen_words; i++)
	{
		theApp.word[i].rect.y++;
		//����ײ��UFO
		if (IsConflict(theApp.ufo.rect, theApp.word[i].rect))
		{
			//������ը
			fire_a_Explosion(wordX(i) + wordWidth(i) / 2, wordY(i) + wordHeight(i));
			//ɾ������
			delete_one_word(i);
			//������ֵ
			theApp.blood.hp -= 10;
			if (!UFOHP())
			{
				theApp.gameover = TRUE;
			}
		}
	}


}

/************************************************************************/
/*����ԭ�ͣ�void clearWords()											*/
/*�����������															*/
/*�� �� ֵ����															*/
/*�������ܣ���յ�������												*/
/************************************************************************/
void clearWords() {

	memset(theApp.word, 0, sizeof(WORD) * 25);
}
