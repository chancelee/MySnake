#pragma once
#include "data.h"

void SaveIni();//�����ʼ����Ϣ����Ϸ�浵��Ĭ�ϵ�ͼ���ļ���
void ReadIni();//��ȡ��ʼ����Ϣ
void SaveMap(int(*m_map)[HEIGHT], char *m_mapName);//�����ͼ
void ReadMap(int(*m_map)[HEIGHT], const char *m_mapName);//��ȡѡ�еĵ�ͼ
void SaveGame(pGAMESAVE g_sav, char * name,char * oldname);//������Ϸ
void OpenGame(char * saveName);//��ȡ��Ϸ�浵����ʼ��Ϸ
