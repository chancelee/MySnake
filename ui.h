#pragma once  
#include "data.h"
void gotoxy(short nX, short nY);//��궨λ
void setcolor(int foreColor = 0, int backcolor = 15);//������ɫ
void Menu();//��ӡ���˵�
void GameInfo();//��ӡ��Ϸ�����ϵ���ʾ��Ϣ
void Start(int(*m_map)[HEIGHT], const char * music);//��ʼ����Ϸ����ͬ�ĵ�ͼ��ͬ�ı�������
void Paint(int(*m_map)[HEIGHT],char *m_mapName);//�༭��Ӧ�õ�ͼ
void SelectMap();//ѡ���ͼ����
void Start(int i);//������ʼ��Ϸʱ����
void SelectGame();//ѡ��浵����
void Selectdiff();//ѡ���Ѷ�
void LoadingMenu();//���ز˵��Ķ���