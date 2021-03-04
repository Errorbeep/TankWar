#include "EnemyTank.h"
#include"Bullet.h"
//#include<iostream>
#include<time.h>
//using namespace std;

EnemyTank::EnemyTank(int x, int y)
{
	int i;
	m_x = x;
	m_y = y;
	m_bDisappear = false;
	m_step = 0;
	m_bNeedShoot = false;
	path.clear();
	//path.resize(maxPath);
	path.push_back(Point(x, y, true));
	m_dir = (Dir)(Dir::bUP + (rand() % 4));
	m_step = 1;
	//cout << "(" << m_x << ", " << m_y << ")\n ";
	//q(10, vector<Point>(19));
	q.resize(maxPath);
	for (i = 0; i < q.size(); i++)
	{
		//q[i].resize(4);
		q[i].clear(); //!!!!!!!!
	}
	
}
void EnemyTank::Display()
{
//	cout << m_dir << " " << m_x << ", " << m_y << endl;
	switch (m_dir)
	{
	case bUP:
		DrawTankBody();
		break;
	case bDOWN:
		DrawTankBody();
		break;
	case bLEFT:
		DrawTankBody();
		break;
	case bRIGHT:
		DrawTankBody();
		break;
	default:
		break;
	}


}

void EnemyTank::Shoot(list<Object*>& lstBullets)
{

	if (m_dir == bUP)
	{
		Bullet* pBullet = new Bullet((m_x + 1) * 25, m_y * 25 - 2, m_dir, WHITE, 1);
		lstBullets.push_back(pBullet);
	}
	else if (m_dir == bRIGHT)
	{
		Bullet* pBullet = new Bullet((m_x + 2) * 25 + 2, (m_y + 1) * 25, m_dir, WHITE, 1);
		lstBullets.push_back(pBullet);
	}
	else if (m_dir == bDOWN)
	{
		Bullet* pBullet = new Bullet((m_x + 1) * 25, (m_y + 2) * 25 + 2, m_dir, WHITE, 1);
		lstBullets.push_back(pBullet);
	}
	else
	{
		Bullet* pBullet = new Bullet(m_x * 25 - 2, (m_y + 1) * 25, m_dir, WHITE, 1);
		lstBullets.push_back(pBullet);
	}
	//lstBullets.push_back(pBullet);

	m_bNeedShoot = false;
}

bool EnemyTank::NeedShoot()
{
	return m_bNeedShoot;

}

void EnemyTank::Move(Map mp)
{

	double dur;
	clock_t start, end;
	int W = mp.getWidth();
	int H = mp.getHight();
	bool tell = false;
//	Point tP;
	start = clock();
	setfillcolor(BLACK);
//	Dir dir;
	//cout << "Move: (" << m_x << ", " << m_y << ")\n";
	int tempX, tempY, old_x = m_x, old_y = m_y, i, pindex;
	while(path.size() > maxPath - 1)
	{
		path.erase(path.begin());
	}
	detect(mp);
	int index = path.size() - 1;
	if (index < 0)
	{
		path.push_back(Point(m_x, m_y, true));
		index++;
	}

	if (index >= 0 && !q[index].empty())
	{

		for (i = 0; i < q[index].size(); i++)
		{
			modifyMap(mp, 0);
			tempX = q[index][i].GetX();
			tempY = q[index][i].GetY();
			if (q[index][i].GetFlag() == false 
				&& mp.getN(tempY, tempX) == 0 && mp.getN(tempY + 1, tempX) == 0 && mp.getN(tempY, tempX + 1) == 0 && mp.getN(tempY + 1, tempX + 1) == 0)
			{
				pindex = i;
				break;
			}
			modifyMap(mp, 6);
		}
		if (i != q[index].size())
		{
			//cout <<"Index:"<< index << endl;
			m_x = q[index][pindex].GetX();
			m_y = q[index][pindex].GetY();
			//cout<<"JUST NOW：              (" << m_x << ", " << m_y << ")" << endl;
			if (m_x > old_x)
			{
				m_dir = bRIGHT;
			}
			else if (m_x < old_x)
			{
				m_dir = bLEFT;
			}
			else if (m_y > old_y)
			{
				m_dir = bDOWN;
			}
			else
			{
				m_dir = bUP;
			}
			q[index][pindex].SetFlag(true);
			path.push_back(Point(m_x, m_y, true));
			//cout << "MoveFromTo: (" << old_x << ", " << old_y << ") ---> (" << m_x << ", " << m_y << ")" << endl;
			/*while(path.size() > 18)
			{
				path.erase(path.begin());
			}*/
			tell = true;

		}
	}
	if(!tell )
	{
		/*if (q[index].empty())
			cout << "q["<<index<<"] Empty\n";
		else
		{
			cout << "q[" << index << "] :\n";
			for (int i = 0; i < q[index].size(); i++)
			{
				cout << q[index][i].GetX() << ", " << q[index][i].GetY() << " " << q[index][i].GetFlag() << endl;
			}
		}*/

		if (index - 1 >= 0)
		{

			modifyMap(mp, 0);
			tempX = path[index - 1].GetX();
			tempY = path[index - 1].GetY();
			if (mp.getN(tempY, tempX) == 0 && mp.getN(tempY + 1, tempX) == 0 && mp.getN(tempY, tempX + 1) == 0 && mp.getN(tempY + 1, tempX + 1) == 0)
			{

				index--;
				//if (index >= 0)
				//{
					//cout << "Index:" << index << endl;

					m_x = path[index].GetX();
					m_y = path[index].GetY();
					//cout << "Back: (" << old_x << ", " << old_y << ") ---> (" << m_x << ", " << m_y << ")" << endl;
					for (i = 0; i < q[index].size(); i++)
					{
						if (q[index][i].GetX() == old_x && q[index][i].GetY() == old_y)
						{
						//	cout << "Back: " << old_x << ", " << old_y << " Flag = true\n";
							q[index][i].SetFlag(true);
							//break;
						}

					}

					path.pop_back();
					if (m_x > old_x && m_y == old_y)
					{
						m_dir = bRIGHT;
					}
					else if (m_x < old_x && m_y == old_y)
					{
						m_dir = bLEFT;
					}
					else if (m_y > old_y && m_x == old_x)
					{
						m_dir = bDOWN;
					}
					else if (m_y < old_y && m_x == old_x)
					{
						m_dir = bUP;
					}

				modifyMap(mp, 6);
			}

		}
		else
		{
			index = 0;
			path.clear();
			path.push_back(Point(m_x, m_y));
			Dir dir;
			while ((dir = (Dir)(Dir::bUP + (rand() % 4))) == m_dir)//自动转向
			{
				// Do nothing
			}
			for (i = 0; i < q.size(); i++)
			{
				q[i].resize(4);
				q[i].clear(); //!!!!!!!!
			}
			//cout << "Reborn!-------------------------------" << "(" << m_x << ", " << m_y << ")" << endl;
		}
	}
	if (old_x != m_x || old_y != m_y)
	{
		
		modifyMap(mp, old_x, old_y, 0);
		modifyMap(mp, 6);
		//cout << "oldx: " << old_x << " oldy: " << old_y << " m_x: " << m_x << " m_y: " << m_y << endl;

		end = clock();
		dur = (double)(end - start) / CLOCKS_PER_SEC;
		while(dur <= 0.05)
		{
			end = clock();
			dur = (double)(end - start) / CLOCKS_PER_SEC;
		}
		solidrectangle(old_x * 25, old_y * 25, old_x * 25 + 50, old_y * 25 + 50);  //覆盖坦克原来位置
		//cout << "ERASE###################################"<<old_x<<", "<<old_y<<endl;
	}
	Display();
	m_step++;
	if (m_step % MAX_STEP_SHOOT == 0)
	{
		m_bNeedShoot = true;
	}
//	setfillcolor(YELLOW);
	//for (i = 0; i < 1000000; i++) {}
	//cout << "DISPLAY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<m_x<<", "<<m_y<<endl;
	
}

void EnemyTank::modifyMap(Map mp, int n)
{
	mp.setMap(m_y, m_x, n);
	mp.setMap(m_y + 1, m_x, n);
	mp.setMap(m_y, m_x + 1, n);
	mp.setMap(m_y + 1, m_x + 1, n);

}
void EnemyTank::modifyMap(Map mp, int x, int y, int n)
{
	mp.setMap(y, x, n);
	mp.setMap(y + 1, x, n);
	mp.setMap(y, x + 1, n);
	mp.setMap(y + 1, x + 1, n);
}

void EnemyTank::DrawTankBody()
{
	//TANK enemyTank[ENENMY_TANK_NUMBER];
	//BULLET enemyBUllet[ENENMY_TANK_NUMBER];
	IMAGE enemyTank_img[8];
	loadimage(&enemyTank_img[bUP], _T("enemy_tank_up.gif"), 50, 50);
	loadimage(&enemyTank_img[bDOWN], _T("enemy_tank_down.gif"), 50, 50);
	loadimage(&enemyTank_img[bLEFT], _T("enemy_tank_left.gif"), 50, 50);
	loadimage(&enemyTank_img[bRIGHT], _T("enemy_tank_right.gif"), 50, 50);
	putimage(m_x * 25, m_y * 25, &enemyTank_img[m_dir]);
	//cout << m_dir << " DRAW:_______" << m_x << ", " << m_y << endl;
	/*IMAGE myTank_img[4];
	loadimage(&myTank_img[UP], _T("tank_up.jpg"), 50, 50);
	loadimage(&myTank_img[DOWN], _T("tank_down.jpg"), 50, 50);
	loadimage(&myTank_img[LEFT], _T("tank_left.jpg"), 50, 50);
	loadimage(&myTank_img[RIGHT], _T("tank_right.jpg"), 50, 50);
	putimage(m_x * 25, m_y * 25, &myTank_img[m_dir]);  */


}
void EnemyTank::setDir(Dir dir)
{
	m_dir = dir;
}
void EnemyTank::setDir(int tank_x, int tank_y)
{
	int r = rand() % 100;
	if (m_y < tank_y)
	{
		if (m_x < tank_x)
		{
			if (r < 50)
				m_dir = bUP;
			else
				m_dir = bLEFT;
		}
		else if (m_x > tank_x)
		{
			if (r < 50)
				m_dir = bUP;
			else
				m_dir = bRIGHT;
		}
		else if (m_x == tank_x)
		{
	//		if (map[tank_y - 1][tank_x] == 2)
	//		{
				if (r < 50)
					m_dir = bLEFT;
				else
					m_dir = bRIGHT;
	//		}
				m_dir = bUP;
		}
	}
	else if (m_y > tank_y)
	{
		if (m_x < tank_x)
		{
			if (r < 50)
				m_dir = bDOWN;
			else
				m_dir = bLEFT;
		}
		else if (m_x > tank_x)
		{
			if (r < 50)
				m_dir = bDOWN;
			else
				m_dir = bRIGHT;
		}
		else if (m_x == tank_x)
		{
	//		if (map[tank_y + 2][tank_x] == 2)
	//		{
				if (r < 50)
					m_dir = bLEFT;
				else
					m_dir = bRIGHT;
	//		}
				m_dir = bDOWN;
		}
	}
	else if (m_y == tank_y)
	{
		if (m_x < tank_x)
			m_dir = bLEFT;
		else
			m_dir = bRIGHT;
	}

}

void EnemyTank::detect(Map mp)
{
	int delX[4] = { 0, 1, 0, -1 };
	int delY[4] = {-1, 0, 1, 0 };

	int i, j, tempX, tempY, index = path.size() - 1, cnt, temp;
	
	if (index < 0)
	{
		path.push_back(Point(m_x, m_y, true));
		index++;
	}
	//cout << "Detect:" << index << endl;
	modifyMap(mp, 0);

	//i = rand() % 4;
	for (i = 0; i < 4; i++)
	{
		bool f1 = false, f2 = false;
		tempX = m_x + delX[i];
		tempY = m_y + delY[i];
		//cout << "Path size:"<<path.size() << endl;
		for (j = 0; j < path.size(); j++)
		{
			//cout << path[j].GetX() <<", "<< path[j].GetY() << endl;
			if (path[j].GetX() == tempX && path[j].GetY() == tempY)
			{
				//cout << "f1 = true: " << tempX << " " << tempY << endl;
				f1 = true;
				break;
			}
			
		}
		
		for (j = 0; j < q[index].size(); j++)
		{
			if (q[index][j].GetX() == tempX && q[index][j].GetY() == tempY && q[index][j].GetFlag() == true)
			{
			//	cout << "f2 = true: " << tempX << " " << tempY << endl;
				f2 = true;
				break;
			}
			

		}
		
		
		if (tempX > 1 && tempX < mp.getWidth() - 2 && tempY > 1 && tempY < mp.getHight() - 2 && f1 == false &&  f2 == false && 
			mp.getN(tempY, tempX) == 0 && mp.getN(tempY + 1, tempX) == 0 && mp.getN(tempY, tempX + 1) == 0 && mp.getN(tempY + 1, tempX + 1) == 0)
		{

			q[index].push_back(Point(tempX, tempY));
		//	cout << "From q: " << tempX << ", " << tempY << endl;

		}
		
	}

	//if (q[index].empty())
	//	cout << "q[" << index << "]Nothing Detected!\n";
	modifyMap(mp, 6);
}