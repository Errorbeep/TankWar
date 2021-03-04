#include "Bullet.h"
//#include<iostream>
//using namespace std;


Bullet::Bullet()
{
}

Bullet::Bullet(int x, int y, Dir dir, COLORREF color, int User)
{
	m_x = x;
	m_y = y;
	m_dir = dir;
	m_color = color;

	m_step = 12;

	m_bDisappear = false;
	user = User;
	//CalculateSphere();
}

Bullet::~Bullet()
{

}

// 绘图
void Bullet::Display()
{
	COLORREF fill_color_save = getfillcolor();
	COLORREF color_save = getcolor();

	setfillcolor(m_color);
	setcolor(m_color);

	fillcircle(m_x, m_y, 2);

	setcolor(color_save);
	setfillcolor(fill_color_save);
}
void Bullet::putTankBoom(int x, int y)
{
	IMAGE img[8];
	/* char name[32];
	   for (int i = 0; i < 8; i++)
	   {
		   sprintf_s(name, 32, "blast%d.gif", i + i);
		   loadimage(&img[i], name, 50, 50);
	   }     */
	loadimage(&img[0], _T("blast1.gif"), 50, 50);
	loadimage(&img[1], _T("blast2.gif"), 50, 50);
	loadimage(&img[2], _T("blast3.gif"), 50, 50);
	loadimage(&img[3], _T("blast4.gif"), 50, 50);
	loadimage(&img[4], _T("blast5.gif"), 50, 50);
	loadimage(&img[5], _T("blast6.gif"), 50, 50);
	loadimage(&img[6], _T("blast7.gif"), 50, 50);
	loadimage(&img[7], _T("blast8.gif"), 50, 50);
	for (int i = 0; i < 8; i++)
	{
		putimage(x * 25, y * 25, &img[i]);
		Sleep(10);
	}
	solidrectangle(x * 25, y * 25, x * 25 + 50, y * 25 + 50);
}

// 移动
void Bullet::Move(Map mp)
{
	int x1, y1, x2, y2;
	x1 = m_x / 25;
	y1 = m_y / 25;
	IMAGE Wall2;
	loadimage(&Wall2, _T("wall3.jpg"), 25, 25);
	setfillcolor(BLACK);
	solidcircle(m_x, m_y, 3);
	switch (m_dir)
	{
		
	case bUP:

		x2 = x1 - 1;
		y2 = y1;
		m_y -= m_step;
		//CalculateSphere();
		/*if (m_y <= 2 || mp.getN(m_y, m_x) != 0)
		{
			//m_y += m_step;
			m_bDisappear = true;
		}*/
		break;
	case bDOWN:
		x2 = x1 - 1;
		y2 = y1;
		m_y += m_step;
		//CalculateSphere();
		/*if (m_y > mp.getHight() - 2 || mp.getN(m_y, m_x) != 0)
		{
			//m_y += m_step;
			m_bDisappear = true;
		}*/
		break;
	case bLEFT:
		x2 = x1;
		y2 = y1 - 1;
		m_x -= m_step;
		//CalculateSphere();
		/*if (m_x < 0 || mp.getN(m_y, m_x) != 0)
		{
			//m_x = 0;
			m_bDisappear = true;
		}*/
		break;
	case bRIGHT:
		x2 = x1;
		y2 = y1 - 1;
		m_x += m_step;
		//CalculateSphere();
		/*if (m_x > mp.getWidth() - 2 || mp.getN(m_y, m_x) != 0)
		{
			//m_x = mp.getWidth() - 2;
			m_bDisappear = true;
		}*/
		break;
	default:
		break;
	}

	if (m_x < 1 || m_x>750 || m_y < 1 || m_y>750)
	{
		putimage(x1 * 25, y1 * 25, &Wall2);
		putimage(x2 * 25, y2 * 25, &Wall2);
		m_bDisappear = true;
		return;
	}
	if (mp.getN(y1, x1) == 3 || mp.getN(y1, x1) == 4)
	{
		mp.setMap(y1, x1, 7);
	}
	if (mp.getN(y1, x1) == 1 && mp.getN(y2, x2) == 1)
	{
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25, x1 * 25 + 25, y1 * 25 + 25);
		solidrectangle(x2 * 25, y2 * 25, x2 * 25 + 25, y2 * 25 + 25);
		mp.setMap(y1, x1, 0);
		mp.setMap(y2, x2, 0); 
		m_bDisappear = true;
		//bullet->state = 0;
		return;
	}
	else if (mp.getN(y1, x1) == 1 && mp.getN(y2, x2) == 0)
	{
		setfillcolor(BLACK);
		solidrectangle(x1 * 25, y1 * 25, x1 * 25 + 25, y1 * 25 + 25);
		mp.setMap(y1, x1, 0);
		m_bDisappear = true;
		//bullet->state = 0;
		return;
	}
	else if (mp.getN(y1, x1) == 0 && mp.getN(y2, x2) == 1)
	{
		setfillcolor(BLACK);
		solidrectangle(x2 * 25, y2 * 25, x2 * 25 + 25, y2 * 25 + 25);
		mp.setMap(y2, x2, 0);
		m_bDisappear = true;
		//bullet->state = 0;
		return;
	}
	else if (mp.getN(y1, x1) == 2 && mp.getN(y2, x2) == 2)   //子弹碰到不可消除墙，重新绘制白墙图片，否则墙上会有弹坑
	{
		putimage(x1 * 25, y1 * 25, &Wall2);
		putimage(x2 * 25, y2 * 25, &Wall2);
		m_bDisappear = true;
		//bullet->state = 0;
		return;
	}
	else if (mp.getN(y1, x1) == 2 && mp.getN(y2, x2) != 2)
	{
		putimage(x1 * 25, y1 * 25, &Wall2);
		m_bDisappear = true;
		//bullet->state = 0;
		return;
	}
	else if (mp.getN(y1, x1) != 2 && mp.getN(y2, x2) == 2)
	{
		putimage(x2 * 25, y2 * 25, &Wall2);
		m_bDisappear = true;
		//bullet->state = 0;
		return;
	}
	else if ((mp.getN(y1, x1) == 5 && mp.getN(y2, x2) == 5) || (mp.getN(y1, x1) == 6 && mp.getN(y2, x2) == 6))
	{
		//mp.setMap(y1, x1, 7);
		//mp.setMap(y2, x2, 7); 
		//mp.setMap(y2 - 1, x2, 7);
		//mp.setMap(y1 - 1, x1, 7);
		m_bDisappear = true;
		if ((user == 0 && mp.getN(y1, x1) == 6) || (user == 1 && mp.getN(y1, x1) == 5))
		{
			if (m_dir == bUP)
			{
				if (mp.getN(y1 - 1, x1) >= 5)
				{
				mp.setMap(y2 - 1, x2, 7);
				//cout << x2 << ",*****************UP*********************************************************** " << (y2 - 1) << endl;
				putTankBoom(x2, y2 - 1);

				}

			}
			if (m_dir == bRIGHT)
			{
				if (mp.getN(y2, x2 + 1) >= 5)
				{
				//cout << x2 << ",*****************bRIGHT******************************************************** " << y2 << endl;
				mp.setMap(y2, x2, 7);
				putTankBoom(x2, y2);

				}
			}
			if (m_dir == bLEFT)
			{
				if (mp.getN(y2, x2 - 1) >= 5)
				{
				//cout << x2 - 1 << ",*****************bLEFT********************************************** " << y2 << endl;
				mp.setMap(y2, x2 - 1, 7);
				putTankBoom(x2 - 1, y2);

				}

			}
			if (m_dir == bDOWN)
			{
				if (mp.getN(y2 + 1, x2) >= 5)
				{
				//cout << y2 << ",*****************bDOWN********************************************* " << x2 << endl;
				mp.setMap(y2, x2, 7);
				putTankBoom(x2, y2);

				}
			}
		}
		//bullet->state = 0;
		return;
	}
	else if ((mp.getN(y1, x1) == 5 && mp.getN(y2, x2) == 0) || (mp.getN(y1, x1) == 6 && mp.getN(y2, x2) == 0))
	{
		m_bDisappear = true;
		if ((user == 0 && mp.getN(y1, x1) == 6) || (user == 1 && mp.getN(y1, x1) == 5))
		{

			if (m_dir == bUP)
			{
				if (mp.getN(y1 - 1, x1 + 1) >= 5)
				{
				mp.setMap(y1 - 1, x1, 7);
				putTankBoom(x1, y1 - 1);

				}

			}
			if (m_dir == bRIGHT)
			{
				if (mp.getN(y1 + 1, x1 - 1) >= 5)
				{
				mp.setMap(y1, x1 - 1, 7);
				putTankBoom(x1 - 1, y1);

				}
			}
			if (m_dir == bLEFT)
			{
				if (mp.getN(y1 + 1, x1 - 1) >= 5)
				{
				mp.setMap(y1, x1 - 1, 7);
				putTankBoom(x1 - 1, y1);

				}

			}
			if (m_dir == bDOWN)
			{
				if (mp.getN(y1 + 1, x1 + 1) >= 5)
				{
				mp.setMap(y1, x1, 7);
				putTankBoom(x1, y1);

				}
			}
		}
		//bullet->state = 0;
		return;
	}
	else if ((mp.getN(y1, x1) == 0 && mp.getN(y2, x2) == 5) || (mp.getN(y1, x1) == 0 && mp.getN(y2, x2) == 6))
	{

		m_bDisappear = true;
		if ((user == 0 && mp.getN(y2, x2) == 6) || (user == 1 && mp.getN(y2, x2) == 5))
		{
			if (m_dir == bUP)
			{
				if (mp.getN(y2 - 1, x2 - 1) >= 5)
				{
				mp.setMap(y2 - 1, x2 - 1, 7);
				putTankBoom(x2 - 1, y2 - 1);

				}

			}
			if (m_dir == bRIGHT)
			{
				if (mp.getN(y2 - 1, x2 + 1) >= 5)
				{
				mp.setMap(y2 - 1, x2, 7);
				putTankBoom(x2, y2 - 1);

				}
			}
			if (m_dir == bLEFT)
			{
				if (mp.getN(y2 - 1, x2 - 1) >= 5)
				{
				mp.setMap(y2 - 1, x2 - 1, 7);
				putTankBoom(x2 - 1, y2 - 1);

				}

			}
			if (m_dir == bDOWN)
			{
				if (mp.getN(y2 + 1, x2 - 1) >= 5)
				{
				mp.setMap(y2, x2 - 1, 7);
				putTankBoom(x2 - 1, y2);

				}
			}
		}
		
		//bullet->state = 0;
		return;
	}

	Display();
}

