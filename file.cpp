#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "CMap.h"
#include "file.h"
#include "data.h"  
#include "ui.h"

using std::cout;
using std::cin;

void SaveIni()
{
	FILE *pFile = nullptr;

	//1.��
	if (fopen_s(&pFile, "IniInfo", "wb+"))
		printf("ʧ��\n");
	//д��
	fwrite(g_defauleMapName, 50, 1, pFile);
	fwrite(g_SaveName1, 50, 1, pFile);
	//fwrite(g_SaveName2, 50, 1, pFile);
	
	//3.�ر�
	fclose(pFile);
}
void ReadIni()
{
	FILE *pFile = nullptr;
	//1.��
	if (fopen_s(&pFile, "IniInfo", "ab+"))
		printf("ʧ��\n");
	//д��
	fread(g_defauleMapName, 50, 1, pFile);
	fread(g_SaveName1, 50, 1, pFile);
	//fread(g_SaveName2, 50, 1, pFile);
	
	//3.�ر�
	fclose(pFile);
	if (fopen_s(&pFile, "map4", "ab+"))
		printf("ʧ��\n");
	fread(g_aMap, 4 * HEIGHT*WEIGHT, 1, pFile);
	fclose(pFile);
}
void SaveMap(int(*m_map)[HEIGHT],char *m_mapName)
{
	FILE *pFile = nullptr;

	//1.��
	if (fopen_s(&pFile, m_mapName, "wb+"))
		printf("ʧ��\n");
	//д��
	
	fwrite(m_map, 4 * HEIGHT*WEIGHT, 1, pFile);
	//3.�ر�
	fclose(pFile);
}


void ReadMap(int(*m_map)[HEIGHT], const char *m_mapName)
{
	FILE *pFile = nullptr;
	//1.��
	if (fopen_s(&pFile, m_mapName, "rb+"))
		printf("ʧ��\n");
	//д��
	fread(m_map, 4 * HEIGHT*WEIGHT, 1, pFile);
	//3.�ر�
	fclose(pFile);
}
void SaveGame(pGAMESAVE g_sav,char * name, char * oldname)
{
	//��ȫ�ֱ����ֱ𶼴浽�ṹ��ĳ�Ա����
	g_sav->gIsNewFood=gIsNewFood;
	g_sav->gIsNewBlood = gIsNewBlood;
	g_sav->gIsPause = gIsPause;
	memcpy(g_sav->g_aMap, g_aMap, 4 * HEIGHT*WEIGHT);
	g_sav->g_nSpeed = g_nSpeed;
	g_sav->g_nScore = g_nScore;
	g_sav->g_nBlood = g_nBlood;
	g_sav->g_nNormalSpeed = g_nNormalSpeed;
	g_sav->g_nFastSpeed = g_nFastSpeed;
	g_sav->g_len= g_len;
	FILE *pFile = nullptr;
	//1.��
	if (fopen_s(&pFile, name, "wb+"))
		printf("ʧ��\n");
	//��ԭ���Ĵ浵ɾ��
	remove(oldname);
	//д��浵����
	fwrite(g_sav, sizeof(GAMESAVE), 1, pFile);
	//д����������vector
	for (int i=0;i<g_snake.size();i++)
	{
		fwrite(&g_snake[i], sizeof(COORD), 1, pFile);
	}
	//3.�ر�
	fclose(pFile);
	SaveIni();
}
void OpenGame(char * saveName)
{
	int i = 0;
	
	FILE *pFile = nullptr;
	//1.��
	if (fopen_s(&pFile, saveName, "rb+"))
		printf("ʧ��\n");
	//��ȡ
	fread(g_save, sizeof(GAMESAVE), 1, pFile);
	//��ȡvector
	/*while(!feof(pFile))
	{
		fread(&g_tmp[i], sizeof(COORD), 1, pFile);
		i++;
	}*/
	int n=g_save->g_len;
	for (int i=0;i<n;i++)
	{
		fread(&g_tmp[i], sizeof(COORD), 1, pFile);
	}

	//3.�ر�
	fclose(pFile);

	gIsNewFood=g_save->gIsNewFood ;
	gIsNewBlood=g_save->gIsNewBlood;
	gIsPause=g_save->gIsPause;
	g_nNormalSpeed = g_save->g_nNormalSpeed;
	g_nFastSpeed = g_save->g_nFastSpeed;
	g_nSpeed=g_save->g_nSpeed;
	g_nScore=g_save->g_nScore;
	g_nBlood=g_save->g_nBlood;
	g_len = n;
	//������ʼ��Ϸ
	Start(1);
	
}