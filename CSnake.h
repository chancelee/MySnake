#pragma once
#include<iostream>
#include<windows.h>
#include<vector>

using std::vector;

class CSnake
{
public:
	CSnake();
	void IniS();	//�����ʼ���ߵ��������
	void DrawS();	//����
	void Collision();	//��ײ���
	void MoveS();	//�ƶ�
	
public:
	vector<COORD> m_snake;//�ߵ�λ��
	int m_nDir;	//����
	bool m_isAlive;	//�Ƿ���
private:
	
};
