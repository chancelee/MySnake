#include<iostream>
#include<windows.h>
#include<time.h>
#include<MMSystem.h>
#pragma comment(lib,"Winmm.lib")
#include"data.h"
#include "ui.h"
#include "CSnake.h"
using std::cout;
using std::vector;
using std::swap;
CSnake::CSnake() : m_nDir(EAST), m_isAlive(true)
{

}
void CSnake::IniS()
{
	short nX = 0, nY = 0;
	srand((unsigned int)time(NULL));
	while (1)
	{
		nX = 5 + rand() % 60;
		nY = 1 + rand() % 36;
		if (g_aMap[nX][nY] == BLANK && g_aMap[nX - 1][nY] == BLANK && g_aMap[nX - 2][nY] == BLANK && g_aMap[nX + 1][nY] == BLANK)
		{
			m_snake.push_back({ nX,nY });
			m_snake.push_back({ nX - 1,nY });
			m_snake.push_back({ nX - 2,nY });

			break;
		}
	}
}
void CSnake::DrawS()
{
	for (int i = 0; i < m_snake.size(); i++)
	{
		g_aMap[m_snake[i].X][m_snake[i].Y] = SNAKE;
		gotoxy(m_snake[i].X, m_snake[i].Y);

		if (i == 0)
		{
			g_aMap[m_snake[i].X][m_snake[i].Y] = SNAKEH;
			setcolor(4); cout << "��";
		}
		else
		{
			g_aMap[m_snake[i].X][m_snake[i].Y] = SNAKE;
			setcolor(12); cout << "��";
		}
	}
}
void CSnake::MoveS()
{
	//SPACE��ͣ
	if (GetAsyncKeyState(VK_SPACE))
	{
		gIsPause = -gIsPause;
	}
	if (gIsPause == -1)
	{
		//���û����ͣ���ⰴ��
		if (GetAsyncKeyState('W'))
		{
			m_nDir == SOUTH ? m_nDir : m_nDir = NORTH;
		}
		if (GetAsyncKeyState('A'))
		{
			m_nDir == EAST ? m_nDir : m_nDir = WEST;
		}
		if (GetAsyncKeyState('S'))
		{
			m_nDir == NORTH ? m_nDir : m_nDir = SOUTH;
		}
		if (GetAsyncKeyState('D'))
		{
			m_nDir == WEST ? m_nDir : m_nDir = EAST;
		}
		//��һ����������
		short newX, newY;
		if (m_nDir == NORTH)
		{
			newX = m_snake[0].X; newY = m_snake[0].Y - 1;
		}
		if (m_nDir == WEST)
		{
			newX = m_snake[0].X - 1; newY = m_snake[0].Y;
		}
		if (m_nDir == SOUTH)
		{
			newX = m_snake[0].X; newY = m_snake[0].Y + 1;
		}
		if (m_nDir == EAST)
		{
			newX = m_snake[0].X + 1; newY = m_snake[0].Y;
		}
		m_snake.insert(m_snake.begin(), { newX,newY });
		g_aMap[m_snake[0].X][m_snake[0].Y] = SNAKEH;

		gotoxy(m_snake[0].X, m_snake[0].Y);
		setcolor(4); cout << "��";
		//ԭ����ͷ�������
		gotoxy(m_snake[1].X, m_snake[1].Y);
		g_aMap[m_snake[1].X][m_snake[1].Y] = SNAKE;
		setcolor(12); cout << "��";
		//ʳ����������
		gotoxy(m_snake[3].X, m_snake[3].Y);
		setcolor(12); cout << "��";

		//ȥ��β��
		g_aMap[m_snake[m_snake.size() - 1].X][m_snake[m_snake.size() - 1].Y] = BLANK;
		gotoxy(m_snake[m_snake.size() - 1].X, m_snake[m_snake.size() - 1].Y);
		cout << " ";
		m_snake.pop_back();

	}

}

void CSnake::Collision()
{
	short nextX, nextY;
	if (m_nDir == WEST)
	{
		nextX = m_snake[0].X - 1;
		nextY = m_snake[0].Y;
	}

	if (m_nDir == EAST)
	{
		nextX = m_snake[0].X + 1;
		nextY = m_snake[0].Y;
	}
	if (m_nDir == NORTH)
	{
		nextX = m_snake[0].X;
		nextY = m_snake[0].Y - 1;
	}
	if (m_nDir == SOUTH)
	{
		nextX = m_snake[0].X;
		nextY = m_snake[0].Y + 1;
	}
	switch (g_aMap[nextX][nextY])
	{
		//ײ��ʳ��
	case FOOD:
	{
		mciSendString("play tun.wav", NULL, 0, NULL);
		m_snake.insert(m_snake.begin(), { nextX ,nextY });
		g_aMap[m_snake[0].X][m_snake[0].Y] = SNAKEH;
		g_aMap[m_snake[1].X][m_snake[1].Y] = SNAKE;
		//ʳ����������
		gotoxy(m_snake[1].X, m_snake[1].Y);
		setcolor(13); cout << "��";

		gIsNewFood--;
		g_nScore += 1;
	}break;
	//ײ��ǽ
	case WALL:
	{
		mciSendString("play tan.wav", NULL, 0, NULL);
		//������ͷ����β
		swap(m_snake[0], m_snake[m_snake.size() - 1]);
		g_aMap[m_snake[0].X][m_snake[0].Y] = SNAKEH;
		g_aMap[m_snake[m_snake.size() - 1].X][m_snake[m_snake.size() - 1].Y] = SNAKE;
		g_nBlood -= 1;
		if (g_nBlood == 0)
		{
			m_isAlive = false;
		}
		//��������
		m_nDir = -m_nDir;
	}break;
	//ײ������
	case BLOODF:
	{
		mciSendString("play blood.wav", NULL, 0, NULL);
		g_nBlood += 1;
		
		//ʳ����������
		gotoxy(m_snake[1].X, m_snake[1].Y);
		setcolor(12); cout << " " << char(3); gIsNewBlood = true;
	} break;
	//ײ����
	case ICE:mciSendString("play sui.wav", NULL, 0, NULL);;
		g_nSpeed = g_nFastSpeed; break;
	case BORDER:	//ײ���߽�
	case SNAKE:		//ײ���Լ�
		m_isAlive = false;
		break;
	default:g_nSpeed = g_nNormalSpeed;
		break;
	}
}
