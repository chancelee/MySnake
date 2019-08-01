#include<iostream>
#include<stdlib.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <memory.h>
#include<string.h>
#include <vector>
#include"CMap.h"
#include "CBloodF.h"
#include "CSnake.h"
#include "CFood.h"
#include "data.h"
#include "file.h"
using std::swap;
using std::vector;
using std::cout;
using std::cin;


void gotoxy(short nX, short nY)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cd = { nX * 2 ,nY };
	SetConsoleCursorPosition(hOutput, cd);
}
void setcolor(int foreColor = 0, int backcolor = 0)
{
	HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOutput, foreColor + backcolor * 0x10);
	/*SetConsoleTextAttribute(hOutput, foreColor + backcolor * 0x10 | BACKGROUND_RED |g_nBlood
		BACKGROUND_GREEN |
		BACKGROUND_BLUE |
		BACKGROUND_INTENSITY);*/
}
void set()
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hInput, &mode); //initialize
	mode |= ENABLE_MOUSE_INPUT;
	SetConsoleMode(hInput, mode);
}

void GameInfo()
{
	gotoxy(4, 40);
	setcolor(12,15);
	cout <<char(3)<<" Blood: "<< g_nBlood<<" ";

	gotoxy(22, 40);
	setcolor(13,15); cout << "��";
	setcolor(0,15);
	cout << " " << "Score: " << g_nScore;

	gotoxy(5, 43);
	setcolor(0,15);
	cout << "SPACE����ͣ/����";
	cout << "\t\t\tShift: �浵";
	cout << "\t\t\tBack: �˳���Ϸ";
	
}
//��Ϸ������ʼ
void Start(int i)
{
	gIsNewBlood=true;
	if (g_nFastSpeed == 20)
	{
		PlaySound("hard.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	}
	else
	PlaySound("normal.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	system("cls");
	CMap map;
	memcpy(g_aMap, g_save->g_aMap, 4 * HEIGHT*WEIGHT);
	map.DrawMap();
	for (int i = 0; i < g_len; i++)
	{
		map.m_sna.m_snake.insert(map.m_sna.m_snake.begin() + i, g_tmp[i]);
	}
	while (1)
	{
		GameInfo();
		map.m_fd.RandF();
		map.m_blood.RandB();
		map.m_sna.Collision();
		map.m_sna.MoveS();
		
		//�浵
		if (GetAsyncKeyState(VK_SHIFT))
		{
			gIsPause = 1;
			//����vector��������swap
			g_snake.assign(map.m_sna.m_snake.begin(), map.m_sna.m_snake.end());
			time_t t = time(NULL);
			//��¼�߽��ĸ���
			g_len = g_snake.size();
			//�ɵ��ļ���������ɾ���ɵĴ浵�ļ�
			char oldgame[50] = { 0 };
			strcpy_s(oldgame, 50, g_SaveName1);
			memset(g_save, 0, sizeof(GAMESAVE));
			strftime(g_SaveName1, sizeof(g_SaveName1) - 1, "%Y-%m-%d %H-%M-%S", localtime(&t));
			SaveGame(g_save, g_SaveName1, oldgame);
			gotoxy(30, 44); setcolor(1);
			cout << "�ɹ��浵Ϊ" << g_SaveName1;
			//if (strcmp(g_SaveName1, g_SaveName2) < 0)
			//{
			//	strcpy_s(oldgame, 50, g_SaveName1);
			//	memset(g_save, 0, sizeof(GAMESAVE));
			//	strftime(g_SaveName1, sizeof(g_SaveName1) - 1, "%Y-%m-%d %H-%M-%S", localtime(&t));
			//	SaveGame(g_save, g_SaveName1, oldgame);
			//	gotoxy(30, 44); setcolor(1);
			//	cout << "�ɹ��浵Ϊ" << g_SaveName1;
			//}
			//else
			//{
			//	memset(g_save2, 0, sizeof(GAMESAVE));
			//	strcpy_s(oldgame, 50, g_SaveName2);
			//	//��ȡ��ǰϵͳʱ��
			//	strftime(g_SaveName2, sizeof(g_SaveName2) - 1, "%Y-%m-%d %H-%M-%S", localtime(&t));
			//	SaveGame(g_save2, g_SaveName2, oldgame);
			//	gotoxy(30, 44); setcolor(1);
			//	cout << "�ɹ��浵Ϊ" << g_SaveName2;
			//}
		}
		if (GetAsyncKeyState(VK_BACK))
		{
			break;
		}
		Sleep(g_nSpeed); 
	}
	
}

void Start(int(*m_map)[HEIGHT],const char * music)
{
	gIsNewFood = 0;
	g_nNormalSpeed =300;
	g_nSpeed =300;
	g_nFastSpeed = 100;
	PlaySound(music, NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);
	system("cls");
	CMap map;
	memcpy(g_aMap, m_map, 4 * HEIGHT*WEIGHT);
	map.DrawMap();
	map.m_sna.IniS();
	map.m_sna.DrawS();
	while (1)
	{
		GameInfo();
		map.m_fd.RandF();
		map.m_blood.RandB();
		map.m_sna.Collision();
		map.m_sna.MoveS();
		
		//�浵
		if (GetAsyncKeyState(VK_SHIFT))
		{
			gIsPause = 1;
			//����vector��������swap
			g_snake.assign(map.m_sna.m_snake.begin(), map.m_sna.m_snake.end());
			time_t t = time(NULL);
			
			g_len = g_snake.size();
			//�ɴ浵���ļ���
			char oldgame[50] = { 0 };

			strcpy_s(oldgame, 50, g_SaveName1);
			memset(g_save, 0, sizeof(GAMESAVE));
			strftime(g_SaveName1, sizeof(g_SaveName1) - 1, "%Y-%m-%d %H-%M-%S", localtime(&t));
			SaveGame(g_save, g_SaveName1, oldgame);
			gotoxy(28, 44); setcolor(1, 15);
			cout << "�ɹ��浵Ϊ" << g_SaveName1;
			//if (strcmp(g_SaveName1, g_SaveName2) < 0)
			//{
			//	strcpy_s(oldgame,50 ,g_SaveName1 );
			//	memset(g_save, 0, sizeof(GAMESAVE));
			//	strftime(g_SaveName1, sizeof(g_SaveName1) - 1, "%Y-%m-%d %H-%M-%S", localtime(&t));
			//	SaveGame(g_save, g_SaveName1, oldgame);
			//	gotoxy(28, 44); setcolor(1,15);
			//	cout << "�ɹ��浵Ϊ" << g_SaveName1;
			//}
			//else
			//{
			//	memset(g_save2, 0, sizeof(GAMESAVE));
			//	strcpy_s(oldgame, 50, g_SaveName2);
			//	//��ȡ��ǰϵͳʱ��
			//	strftime(g_SaveName2, sizeof(g_SaveName2) - 1, "%Y-%m-%d %H-%M-%S", localtime(&t));
			//	SaveGame(g_save2, g_SaveName2, oldgame);
			//	gotoxy(28, 44); setcolor(1,15);
			//	cout << "�ɹ��浵Ϊ" << g_SaveName2;
			//}
		}
		//�˳�
		if (GetAsyncKeyState(VK_BACK))
		{
			break;
		}
		Sleep(g_nSpeed);
		if (map.m_sna.m_isAlive == false)
		{
			gIsPause = 1;
			PlaySound("down.wav", NULL, SND_FILENAME | SND_ASYNC);
			Sleep(3000);
			break;
		}
		
	}

}
//�༭�����ͼ
void Paint(int (*m_map)[HEIGHT],char *m_mapName)
{
	PlaySound("paint.wav", NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
	system("cls");
	set();
	CMap pMap;
	memcpy(g_aMap, m_map, 4 * WEIGHT*HEIGHT);
	pMap.DrawMap();
	gotoxy(5, 43);
	setcolor(10,15); cout << "Press 'W': Wall �~";
	setcolor(9,15); cout << "\t\t\tPress 'I': Ice ��";
	setcolor(0,15); cout << "\t\t\tPress 'B': Border ��";
	gotoxy(5, 44);
	setcolor(0,15); cout << "Mouse Right: Black";
	setcolor(0,15); cout << "\t\t\tPress 'BackSpace': Save&Exit";
	setcolor(0,15); cout << "\t\tPress 'Space': Apply";
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD ir = {};
	DWORD dw = 0;
	while (1)
	{
		ReadConsoleInput(hInput, &ir, 1, &dw);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				gotoxy(pos.X/2, pos.Y);
				if (GetAsyncKeyState('B'))
				{
					setcolor(0,15); cout << "��"; 
					m_map[pos.X/2][pos.Y] = BORDER;
				}
				if (GetAsyncKeyState('W'))
				{
					if (pos.Y % 2 == 0)setcolor(10);
					else if (pos.Y % 3 == 0)setcolor(14); 
					else setcolor(2,15);cout << "�~";
					m_map[pos.X/2][pos.Y] = WALL;
				}
				if (GetAsyncKeyState('I'))
				{
					setcolor(9,15); cout << "��"; 
					m_map[pos.X/2][pos.Y] = ICE;
				}
			}
			if (ir.Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
			{
				COORD pos = ir.Event.MouseEvent.dwMousePosition;
				gotoxy(pos.X/2, pos.Y);
				cout << "  ";
				m_map[pos.X / 2][pos.Y] = BLANK;
			}
		}
		//Back���沢�˳�
		if (GetAsyncKeyState(VK_BACK))
		{
			gotoxy(30, 45); 
			//����ǰ�ĵ�ͼ��Ϣ���浽�ļ�����
			SaveMap(m_map, m_mapName);
			SaveIni();
			setcolor(0, 15); cout << "����ɹ���";
			break;
		}
		//EnterӦ�õ�ǰ��ͼ
		if (GetAsyncKeyState(VK_SPACE))
		{
			//�������
			SaveMap(m_map, m_mapName);
			//memcpy(g_aMap, m_map, 4 * WEIGHT*HEIGHT);
			//����Ĭ�ϵ�ͼ�ļ���
			strcpy_s(g_defauleMapName, 50,m_mapName);
			//����Ĭ�ϵ�ͼ�����ֵ�iniInfo
			SaveIni();
			cout << "Ӧ�óɹ���";
			break;
		}
	}
}
void LoadingMenu()
{
	
	system("cls");
	CMap welcom;
	ReadIni();
	PlaySound("menu.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	g_aMap[32][10] = FOOD;
	g_aMap[36][24] = FOOD;
	g_aMap[57][25] = BLOODF;
	welcom.DrawMap(1);
	mciSendString("play maochulai.wav", NULL, 0, NULL);
	Sleep(60);
	welcom.m_sna.m_snake.push_back({ 20,25 });
	welcom.m_sna.DrawS();
	Sleep(100);
	welcom.m_sna.m_snake.push_back({ 19,25 });
	welcom.m_sna.DrawS();
	Sleep(30);
	welcom.m_sna.m_snake.push_back({ 18,25 });
	welcom.m_sna.DrawS();

	/*if (1)
	{
		welcom.m_sna.HoriMovS();
		welcom.m_sna.Collision();
		Sleep(500);
	}*/
}

void SelectMap()
{
	char nOp = 0;
	int nOver = 1;
	while (1)
	{
		LoadingMenu();
		gotoxy(43, 31); setcolor(2,15);
		cout << "Ĭ�ϵ�ͼ�� " << g_defauleMapName;
		gotoxy(43, 32);
		cout << "1. " << g_sNamwMap1;
		gotoxy(43, 33);
		cout << "2. " << g_sNamwMap2;
		gotoxy(43, 34);
		cout << "3. " << g_sNamwMap3;
		gotoxy(43, 35);
		cout << "4. " << "����";
		gotoxy(43, 36);
		cout << "��ѡ��";
		cin >>nOp;
		getchar();
		switch (nOp)
		{
		case '1':
			//��g_sNamwMap1�ļ��ж�ȡ��ͼ��g_aNewMap1
			ReadMap(g_aNewMap1, g_sNamwMap1);
			Paint(g_aNewMap1, g_sNamwMap1); break;
		case '2':
			ReadMap(g_aNewMap2, g_sNamwMap2);
			Paint(g_aNewMap2, g_sNamwMap2); break;
		case '3':
			ReadMap(g_aNewMap3, g_sNamwMap3);
			Paint(g_aNewMap3, g_sNamwMap3); break;
		case '4':nOver = 0; break;
		default:cout << "����������������룡";
			break;
		}
		if (nOver==0)
		{
			break;
		}
		setcolor(15, 15);
	}
}
void SelectGame()
{
	char nOp = 0;
	int nOver = 1;
	while (1)
	{
		LoadingMenu();
		gotoxy(41, 31); setcolor(2,15);
		cout << "1. " << g_SaveName1 ;
		gotoxy(41, 32);
		//cout << "2. " << g_SaveName2 ;
		//gotoxy(41, 33);
		cout << "2. " << "����";
		gotoxy(41, 34);
		cout << "��ѡ��";
		cin >> nOp;
		
		switch (nOp)
		{
		case '1':
			OpenGame(g_SaveName1);
			 break;
		case '2':
			//OpenGame(g_SaveName2);
			break;
		case '3':nOver = 0; break;
		default:
			break;
		}
		if (nOver == 0)
		{
			break;
		}
	
	}
}
void Selectdiff()
{
	
	int nOver = 1;
	while (nOver)
	{
		LoadingMenu();
		
		gotoxy(43, 31); setcolor(2,13);
		cout << "1. " << "Normal";
		gotoxy(43, 32); setcolor(2, 15);
		cout << "2. " << "Difficult";
		gotoxy(43, 33); setcolor(2, 15);
		cout << "3. " << "����";
		char nOp;
		int k = 1;
		bool flag = false;
		while (nOp = getch())
		{

			switch (nOp)
			{
			case 72:
			{
				if (k > 1)
				{
					switch (k)
					{
					case 2:
						gotoxy(43, 31); setcolor(2, 13);
						cout << "1. " << "Normal";
						gotoxy(43, 32); setcolor(2, 15);
						cout << "2. " << "Difficult";
						k--;
						break;
					case 3:
						gotoxy(43, 32); setcolor(2, 13);
						cout << "2. " << "Difficult";
						gotoxy(43, 33); setcolor(2, 15);
						cout << "3. " << "����";
						k--;
						break;
					}

				}

			}
			break;
			case 80:
			{
				if (k < 5)
				{
					switch (k)
					{
					case 1:
						gotoxy(43, 31); setcolor(2, 15);
						cout << "1. " << "Normal";
						gotoxy(43, 32); setcolor(2, 13);
						cout << "2. " << "Difficult";
						k++;
						break;
					case 2:
						gotoxy(43, 32); setcolor(2, 15);
						cout << "2. " << "Difficult";
						gotoxy(43, 33); setcolor(2, 13);
						cout << "3. " << "����";
						k++;
						break;
					}
				}
			}
			break;
			case 13:flag = true; break;
			default:break;
			}
			if (flag)
			{
				break;
			}
			setcolor(15, 15);
		}
		switch (k)
		{
		case 1:  {
				system("cls");
				//��ʼ����ͼ����g_sNamwMap2�ļ�������д��g_aNewMap2
				ReadMap(g_aNewMap1, g_sNamwMap1);
				g_nNormalSpeed = 400;
				g_nSpeed = 400;
				g_nFastSpeed = 150;
				Start(g_aNewMap1,"normal.wav");
			}break;
		case 2:{
			system("cls");
				CMap map;
				//��ʼ����ͼ����g_sNamwMap1�ļ�������д��g_aNewMap1
				ReadMap(g_aNewMap2, g_sNamwMap2);
				g_nNormalSpeed = 80;
				g_nSpeed = 80;
				g_nFastSpeed = 20;
				Start(g_aNewMap2,"hard.wav");
			}
		case 3:nOver = 0; break;
		default:
			break;
		}
	}

}
void Menu()
{
	while (1)
	{
		ReadIni();
		LoadingMenu();
		gotoxy(43, 31); setcolor(2, 13);
		cout << "1. ��ʼ��Ϸ\n";
		gotoxy(43, 32); setcolor(2, 15);
		cout << "2. ѡ���Ѷ�\n";
		gotoxy(43, 33);
		cout << "3. ѡ���ͼ\n";
		gotoxy(43, 34);
		cout << "4. ��ȡ�浵\n";
		gotoxy(43, 35);
		cout << "5. �˳���Ϸ\n";
	
		char nOp;
		int k = 1;
		bool flag = false;
		while (nOp = getch())
		{

			switch (nOp)
			{
			case 72:
			{
				if (k > 1)
				{
					switch (k)
					{
					case 2:
						gotoxy(43, 31); setcolor(2, 13);
						cout << "1. ��ʼ��Ϸ\n";
						gotoxy(43, 32); setcolor(2, 15);
						cout << "2. ѡ���Ѷ�\n";
						k--;
						break;
					case 3:

						gotoxy(43, 32); setcolor(2, 13);
						cout << "2. ѡ���Ѷ�\n";
						gotoxy(43, 33); setcolor(2, 15);
						cout << "3. ѡ���ͼ\n";
						k--;
						break;
					case 4:
						gotoxy(43, 33); setcolor(2, 13);
						cout << "3. ѡ���ͼ\n";
						gotoxy(43, 34); setcolor(2, 15);
						cout << "4. ��ȡ�浵\n";
						k--;
						break;
					case 5:
						gotoxy(43, 34); setcolor(2, 13);
						cout << "4. ��ȡ�浵\n";
						gotoxy(43, 35); setcolor(2, 15);
						cout << "5. �˳���Ϸ\n";
						k--;
						break;

					}

				}

			}
			break;
			case 80:
			{
				if (k < 5)
				{
					switch (k)
					{
					case 1:
						gotoxy(43, 31); setcolor(2, 15);
						cout << "1. ��ʼ��Ϸ\n";
						gotoxy(43, 32); setcolor(2, 13);
						
						cout << "2. ѡ���Ѷ�\n";
						setcolor(0, 15);
						k++;
						break;
					case 2:
						gotoxy(43, 32); setcolor(2, 15);
						cout << "2. ѡ���Ѷ�\n";

						gotoxy(43, 33); setcolor(2, 13);
						
						cout << "3. ѡ���ͼ\n";
						k++;
						break;
					case 3:
						gotoxy(43, 33); setcolor(2, 15);
						cout << "3. ѡ���ͼ\n";
						gotoxy(43, 34); setcolor(2, 13);
						
						cout << "4. ��ȡ�浵\n";
						k++;
						break;
					case 4:
						gotoxy(43, 34); setcolor(2, 15);
						cout << "4. ��ȡ�浵\n";
						gotoxy(43, 35); setcolor(2, 13);
						
						cout << "5. �˳���Ϸ\n";
						k++;
						break;
					}
				}
			}
			break;
			case 13:flag = true; break;
			default:break;
			}
			if (flag)
			{
				break;
			}
			setcolor(15, 15);
		}
		switch (k)
		{
		case 1:ReadMap(g_aNewMap1, g_defauleMapName);
			Start(g_aNewMap1, "normal.wav"); setcolor(15, 15); break;
		case 2:Selectdiff(); break;
		case 3:SelectMap();  setcolor(15, 15); break;
		case 4:SelectGame(); setcolor(15, 15); break;
		case 5:exit(0); break;
		default:
			break;
		}
		SaveIni();
	}
	
}
