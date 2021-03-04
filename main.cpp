#pragma warning(disable:4996)

#include <iostream>
#include <conio.h>
#include <time.h>
#include <list>

#include "Graphic.h"
#include "MainTank.h"
#include"EnemyTank.h"
#include"Map.h"
#include "Setting.h"
#pragma comment(lib,"winmm.lib")           //µº»Î…˘“Ùø‚

using namespace std;



int main()
{
	Graphic::Create();

	srand((unsigned)time(NULL));
	const int MAX_TANKS = 4;
	int cnt = 0, i, j, times = 0, k, t_x, t_y, kk = 1;
	MainTank mainTank;

	list<Tank*> lstTanks;
	lstTanks.clear();


	list<Object*> lstBullets;
	lstBullets.clear();

	//Tank* pTank[MAX_TANKS];
	int m[30][30] = {
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 2, 2, 2, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,0,1,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,0,1,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 1, 2 },
		{ 2,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0, 0, 1, 1, 2 },
		{ 2,0,1,1,0,0,0,1,0,1,1,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0, 0, 1, 0, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,0,1,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 0, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,0,1,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,0,1,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,0,0,2,0,1,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 1, 2 },
		{ 2,0,0,2,0,0,2,1,0,2,0,0,2,0,0,2,0,0,2,1,0,2,1,1,2,0, 1, 2, 1, 2 },
		{ 2,0,0,2,0,0,2,1,0,2,0,0,2,0,0,2,0,0,2,1,0,2,1,1,2,0, 1, 2, 1, 2 },
		{ 2,0,0,2,0,0,2,0,0,2,1,1,2,0,0,2,0,0,2,0,0,2,0,0,2,0, 0, 2, 0, 2 },
		{ 2,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0, 0, 0, 1, 2 },
		{ 2,1,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,1, 0, 0, 1, 2 },
		{ 2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,2,2,2,1,1,2,1, 1, 2, 2, 2 },
		{ 2,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 2 },
		{ 2,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0, 0, 0, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,0,0,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,0,0,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 0, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,1,1,2,0,0,2,1,0,2,1,1,2,0, 0, 2, 0, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,1,1,2,0,0,2,1,0,2,1,1,2,0, 1, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,0,0,2,1,0,2,0,0,2,1,0,2,1,1,2,0, 1, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,0,0,2,1,0,2,0,0,2,1,0,2,1,1,2,0, 1, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,0,1,1,1,1,2,0,0,2,1,0,2,0,0,2,0, 0, 2, 1, 2 },
		{ 2,0,0,2,0,0,2,0,0,2,0,1,1,3,4,1,0,0,1,0,0,2,0,0,2,0, 0, 2, 1, 2 },
		{ 2,0,0,2,0,0,2,0,0,2,0,1,1,4,4,1,0,0,2,0,0,2,0,0,2,0, 0, 2, 1, 2 },
		{ 2,0,1,2,0,0,2,1,0,2,1,1,2,1,1,2,0,0,2,0,0,2,1,1,2,0, 0, 2, 1, 2 },
		{ 2,0,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0, 0, 0, 1, 2 },
		{ 2,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,1,1,0,0, 0, 0, 1, 2 },
		{ 2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 2, 2, 2, 2 }
	};

	Map mp(m);
	i = mainTank.getX();
	j = mainTank.getY();
	mp.setMap(j, i, 5);
	mp.setMap(j + 1, i, 5);
	mp.setMap(j, i + 1, 5);
	mp.setMap(j + 1, i + 1, 5);
	
	
	//PlaySound(_T("setOut.wav"), NULL, SND_FILENAME | SND_SYNC);
	PlaySound(_T("setOut.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	mp.Display();
	bool loop = true;
	bool skip = false;
	while (loop)
	{
		if (Setting::m_bNewLevel)
		{
			Sleep(1000);

			Setting::m_bNewLevel = false;

			Setting::NewGameLevel();

			int W = mp.getWidth();
			int H = mp.getHight();
			cnt = 0;
			while (cnt < Setting::GetTankNum())
			{
				i = rand() % (W - 2);
				j = rand() % (H - 2);
				if (i != 0 && j != 0 && mp.getN(j, i) == 0 && mp.getN(j + 1, i) == 0 && mp.getN(j, i + 1) == 0 && mp.getN(j + 1, i + 1) == 0)
				{
					lstTanks.push_back(new EnemyTank(i, j));
					mp.setMap(j, i, 6);
					mp.setMap(j + 1, i, 6);
					mp.setMap(j, i + 1, 6);
					mp.setMap(j + 1, i + 1, 6);
					cnt++;
				}
				//rand() % (b - a + 1) + a
				//m_pos.SetX(rand() % Graphic::GetBattleGround().GetWidth());
				//m_pos.SetY(rand() % Graphic::GetBattleGround().GetHeight());
			}
		}
		

		if (kbhit())
		{
			int key = getch();

			switch (key)
			{
				// Up
			case 72:
				mainTank.setDir(Dir::UP);
				break;
				// Down
			case 80:
				mainTank.setDir(Dir::DOWN);
				break;
				// Left
			case 75:
				mainTank.setDir(Dir::LEFT);
				break;
				// Right
			case 77:
				mainTank.setDir(Dir::RIGHT);
				break;
				// Space
			case 32:
				mainTank.Shoot(lstBullets);
				break;
			case 76:
				Setting::SetImmortal();//functionally immortal
				break;
				// Esc
			case 27:
				loop = false;
				break;
				// Enter
			case 13:
				if (skip)
					skip = false;
				else
					skip = true;
				break;
			default:
				break;
			}
		}

		if (!skip)
		{
			if (mp.getN(24, 14) == 7 || mp.getN(24, 15) == 7 || mp.getN(25, 14) == 7 || mp.getN(25, 15) == 7)
			{
				break;
			}
			if (mp.getN(mainTank.getY(), mainTank.getX()) == 7)
			{
				Setting::MainTankDamaged();
				mainTank.modifyMap(mp, 0);
				//mainTank.Display();
			}
			if (Setting::GetLife() <= 0)
			{
				Setting::SetImmortal(0);
				Graphic::ShowScore();
				break;
			}
			mainTank.Move(mp);
			t_x = mainTank.getX();
			t_y = mainTank.getY(); 

			for (list<Tank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); )
			{
				int tempMx = (*it)->getX(), tempMy = (*it)->getY();
				if (mp.getN(tempMy, tempMx) == 7)
				{
					(*it)->modifyMap(mp, 0);
					setfillcolor(BLACK);
					solidrectangle(tempMx * 25, tempMy * 25, tempMx * 25 + 50, tempMy * 25 + 50);
					delete *it;
					it = lstTanks.erase(it);
					Setting::TankDamaged();
					continue;
				}
				k = rand() % 10;
				if(times % (70 + k) == 0)
					(*it)->Move(mp);
				if ((*it)->NeedShoot())
				{
					EnemyTank* p = (EnemyTank*)*it;
					p->Shoot(lstBullets);
				}
				it++;
				//(*it)->Display();
			}

			for (list<Object*>::iterator it = lstBullets.begin(); it != lstBullets.end();)
			{
				(*it)->Move(mp);

				if ((*it)->IsDisappear())
				{
					delete *it;
					it = lstBullets.erase(it);
					continue;
				}

				it++;
			}

			Graphic::ShowScore();
			Graphic::DrawBattleGround();
		}
		Sleep(5);
		//times += 15;
		times++;
	}
	IMAGE gameOver;
	loadimage(&gameOver, _T("gameover.jpg"), 750, 750);
	putimage(0, 0, &gameOver);
	system("pause");
	for (list<Tank*>::iterator it = lstTanks.begin(); it != lstTanks.end(); it++)
	{
		delete *it;
	}
	lstTanks.clear();

	for (list<Object*>::iterator it = lstBullets.begin(); it != lstBullets.end(); it++)
	{
		delete *it;
	}
	lstBullets.clear();

	Graphic::Destroy();
	//getchar();
	getchar();
	return 0;
}
