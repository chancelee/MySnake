#pragma once
#include<iostream>
#include "CFood.h"
#include "CSnake.h"
#include "CBloodF.h"
#include "data.h"

class CMap
{
public:
	CMap();
	void DrawMap();//����ͼ
	void DrawMap(int i);//���˵�����ʱ����
	
public:
	int m_aMap[HEIGHT][WEIGHT];
	CFood m_fd;//�ӷ�ʳ��
	CBloodF m_blood;//��Ѫʳ��
	CSnake m_sna;//��
};
