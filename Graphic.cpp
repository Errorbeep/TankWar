#include "Graphic.h"
#include"Setting.h"
//#include<iostream>
//using namespace std;


Rect Graphic::m_rectScreen;
Rect Graphic::m_rectBattleGround;
char Graphic::m_pArray[100];
const int SCORE_LEFT = 760;
const int SCORE_TOP = 5;

void Graphic::Create()
{
	m_rectScreen.Set(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	initgraph(SCREEN_WIDTH, SCREEN_WIDTH);
	setbkcolor(DARKGRAY);

	m_rectBattleGround.Set(BATTLE_GROUND_X1, BATTLE_GROUND_Y1, BATTLE_GROUND_X2, BATTLE_GROUND_Y2);
}

void Graphic::Destroy()
{
	closegraph();
}

void Graphic::DrawBattleGround()
{
	rectangle(m_rectBattleGround.GetStartPoint().GetX(), m_rectBattleGround.GetStartPoint().GetY(),
		m_rectBattleGround.GetEndPoint().GetX(), m_rectBattleGround.GetEndPoint().GetY());
}

int Graphic::GetScreenWidth()
{
	return SCREEN_WIDTH;
}

int Graphic::GetScreenHeight()
{
	return SCREEN_HEIGHT;
}

Rect Graphic::GetBattleGround()
{
	return m_rectBattleGround;
}

void Graphic::ShowScore()
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	rectangle(SCORE_LEFT, SCORE_TOP, SCORE_LEFT + 250, SCORE_TOP + 40);


	RECT r = { SCORE_LEFT, SCORE_TOP, SCORE_LEFT + 250, SCORE_TOP + 40 };
	wsprintf((LPWSTR)m_pArray, _T("�� %d ��"), Setting::GetGameLevel());
	drawtext((LPWSTR)m_pArray, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	r.top += 50;
	r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("��   ��  :  %d  "), Setting::GetSumScore());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50;
	r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("��   ��  :  %d  "), Setting::GetTankLevel());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50;
	r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("��   ��  :  %d  "), Setting::GetLife());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);

	r.top += 50;
	r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("������   :  %d  "), Setting::GetTankNum());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);
	//cout << Setting::GetTankNum() << "=========================================================================\n";

	r.top += 50;
	r.bottom += 50;

	line(SCORE_LEFT, r.bottom, SCREEN_WIDTH - 5, r.bottom);

	r.top += 50;
	r.bottom += 50;
	wsprintf((LPWSTR)m_pArray, _T("�����ٵ�����  :  %d"), Setting::GetTankSum());
	drawtext((LPWSTR)m_pArray, &r, DT_VCENTER | DT_SINGLELINE);


	setcolor(color_save);
	setfillcolor(fill_color_save);
}