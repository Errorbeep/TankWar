#include"MainTank.h"
#include"Bullet.h"
#pragma comment(lib,"winmm.lib")           //导入声音库

MainTank::MainTank()
{
	m_x = 8;
	m_y = 24;
	m_color = WHITE;
	m_dir = Dir::UP;
	m_step = 1;
	m_bDisappear = false;
}

void MainTank::setDir(Dir dir)
{
	m_dir = dir;
}
void MainTank::setDir(int i, int j)
{

}
void MainTank::DrawTankBody()
{
	IMAGE myTank_img[4];
	loadimage(&myTank_img[UP], _T("tank_up.jpg"), 50, 50);
	loadimage(&myTank_img[DOWN], _T("tank_down.jpg"), 50, 50);
	loadimage(&myTank_img[LEFT], _T("tank_left.jpg"), 50, 50);
	loadimage(&myTank_img[RIGHT], _T("tank_right.jpg"), 50, 50);
	putimage(m_x * 25, m_y * 25, &myTank_img[m_dir]);                           //初始化己方坦克方向//!!!!
	

}

void MainTank::Display()
{
	//COLORREF color_save = getfillcolor();


	switch (m_dir)
	{
	case UP:
		DrawTankBody();
		break;
	case DOWN:
		DrawTankBody();
		break;
	case LEFT:
		DrawTankBody();
		break;
	case RIGHT:
		DrawTankBody();
		break;
	default:
		break;
	}

	//setfillcolor(color_save);
}

void MainTank::Shoot(list<Object*>& lstBullets)
{
	//PlaySound(_T("boom.wav"), NULL, SND_FILENAME | SND_ASYNC);
	//PlaySound(_T("setOut.wav"), NULL, SND_FILENAME | SND_ASYNC);
	if (m_dir == bUP)
	{
		Bullet* pBullet = new Bullet((m_x + 1) * 25, m_y * 25 - 2, m_dir, m_color, 0);
		lstBullets.push_back(pBullet);
	}
	else if (m_dir == bRIGHT)
	{
		Bullet* pBullet = new Bullet((m_x + 2) * 25 + 2, (m_y + 1) * 25, m_dir, m_color, 0);
		lstBullets.push_back(pBullet);
	}
	else if (m_dir == bDOWN)
	{
		Bullet* pBullet = new Bullet((m_x + 1) * 25, (m_y + 2) * 25 + 2, m_dir, m_color, 0);
		lstBullets.push_back(pBullet);
	}
	else
	{
		Bullet* pBullet = new Bullet(m_x * 25 - 2, (m_y + 1) * 25, m_dir, m_color, 0);
		lstBullets.push_back(pBullet);
	}
	/*
		case UP:
			bullet->bullet_x = tank->tank_x * 25 + 25;
			bullet->bullet_y = tank->tank_y * 25 - 3;
			break;
		case DOWN:
			bullet->bullet_x = tank->tank_x * 25 + 25;
			bullet->bullet_y = tank->tank_y * 25 + 53;
			break;
		case LEFT:
			bullet->bullet_x = tank->tank_x * 25 - 3;
			bullet->bullet_y = tank->tank_y * 25 + 25;
			break;
		case RIGHT:
			bullet->bullet_x = tank->tank_x * 25 + 53;
			bullet->bullet_y = tank->tank_y * 25 + 25;
			break;*/
	//lstBullets.push_back(pBullet);

	//Bullet* pBullet = new Bullet(m_x + 3, m_y + 1, m_dir, m_color);

	//lstBullets.push_back(pBullet);
}

void MainTank::Move(Map mp)
{
	/*if (m_pos.GetY() < Graphic::GetBattleGround().GetStartPoint().GetY())
            m_pos.SetY(Graphic::GetBattleGround().GetEndPoint().GetY() - 1);
        break;*/
	int W = mp.getWidth();
	int H = mp.getHight();
	int temp;
	setfillcolor(BLACK);
	switch (m_dir)
	{

	case UP:
		solidrectangle(m_x * 25, m_y * 25, m_x * 25 + 50, m_y * 25 + 50);  //覆盖坦克原来位置
		modifyMap(mp,  0);
		//m_y -= m_step;
		temp = m_y - m_step;
		if (temp < 0)
			//m_y = Graphic::GetScreenHeight() - 1;
			m_y = 0;
		else if (mp.getN(temp, m_x) == 0 && mp.getN(temp + 1, m_x) == 0 && mp.getN(temp, m_x + 1) == 0 && mp.getN(temp + 1, m_x + 1) == 0)
			m_y -= m_step;
		modifyMap(mp,  5);
		Display();
		m_dir = bUP;
		break;
	case DOWN:
		solidrectangle(m_x * 25, m_y * 25, m_x * 25 + 50, m_y * 25 + 50);  //覆盖坦克原来位置
		modifyMap(mp,  0);
		//m_y += m_step;
		//if (m_y > Graphic::GetScreenHeight())
			//m_y = 25;
		temp = m_y + m_step;
		if (temp > H - 2)
			m_y = H - 2;
		else if (mp.getN(temp, m_x) == 0 && mp.getN(temp + 1, m_x) == 0 && mp.getN(temp, m_x + 1) == 0 && mp.getN(temp + 1, m_x + 1) == 0)
			m_y += m_step;
		modifyMap(mp,  5);
		Display();
		m_dir = bDOWN;
		break;
	case LEFT:
		solidrectangle(m_x * 25, m_y * 25, m_x * 25 + 50, m_y * 25 + 50);  //覆盖坦克原来位置
		modifyMap(mp,  0);
		//m_x -= m_step;
		temp = m_x - m_step;
		if (temp < 0)
			m_x = 0;
		else if (mp.getN(m_y, temp) == 0 && mp.getN(m_y + 1, temp) == 0 && mp.getN(m_y, temp + 1) == 0 && mp.getN(m_y + 1, temp + 1) == 0)
			m_x -= m_step;
		modifyMap(mp,  5);
		Display();
		m_dir = bLEFT;
		break;
	case RIGHT:
		solidrectangle(m_x * 25, m_y * 25, m_x * 25 + 50, m_y * 25 + 50);  //覆盖坦克原来位置
		modifyMap(mp,  0);
		//m_x += m_step;
		temp = m_x + m_step;
		//if (m_x > Graphic::GetScreenWidth())
			//m_x = 25;
		if (temp > W - 2)
			m_x = W - 2;
		else if (mp.getN(m_y,temp) == 0 && mp.getN(m_y + 1, temp) == 0 && mp.getN(m_y, temp + 1) == 0 && mp.getN(m_y + 1, temp + 1) == 0)
			m_x += m_step;
		modifyMap(mp,  5);
		Display();
		m_dir = bRIGHT;
		break;
	default:
		break;
	}
}

void MainTank::modifyMap(Map mp, int n)
{
	mp.setMap(m_y, m_x, n);
	mp.setMap(m_y + 1, m_x, n);
	mp.setMap(m_y, m_x + 1, n);
	mp.setMap(m_y + 1, m_x + 1, n);

	/*
	map[tank->tank_y][tank->tank_x] = n;
	map[tank->tank_y + 1][tank->tank_x] = n;
	map[tank->tank_y][tank->tank_x + 1] = n;
	map[tank->tank_y + 1][tank->tank_x + 1] = n;*/
}
void MainTank::modifyMap(Map mp, int x, int y, int n)
{
	mp.setMap(y, x, n);
	mp.setMap(y + 1, x, n);
	mp.setMap(y, x + 1, n);
	mp.setMap(y + 1, x + 1, n);
}

