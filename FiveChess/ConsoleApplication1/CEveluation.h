#pragma once
#include <stdio.h>
#include <windows.h>
#define  BLACK  0
#define  WHITE  1
#define  GRID_NUM 15
#define  GRID_COUNT 225
#define  NOSTONE 0xFF    //û������
#define  STWO      1   //�߶�
#define  STHREE    2   //����
#define  SFOUR     3   //����
#define  TWO       4   //���
#define  THREE     5   //����
#define  FOUR      6   //����
#define  FIVE      7   //����
#define  DFOUR     8   //˫��
#define  FOURT     9   //����
#define  DTHREE   10   //����
#define  NOTYPE   11   //δ����
#define  ANALSISED 255  //�ѷ�������
#define  TOBEANALSIS 0  //�ѷ�������
#define TRUE 1
#define FALSE 0
#define GRID_NUM 15

class CEveluation
{
public:
	CEveluation();
	virtual ~CEveluation();

	virtual int Eveluate(BYTE position[][GRID_NUM], BOOL bIsRedTurn);

protected:

	int AnalysisHorizon(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisVertical(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisLeft(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisRight(BYTE position[][GRID_NUM], int i, int j);
	int AnalysisLine(BYTE *position, int GridNum, int StonePos);
	BYTE m_LineRecord[30];
	int TypeRecord[GRID_NUM][GRID_NUM][4];
	int TypeCount[2][20];

};


