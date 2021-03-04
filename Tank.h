#ifndef __TANK_H__
#define __TANK_H__

#include "Object.h"
#include <list>
#include "Graphic.h"
//#include "Map.h"
using namespace std;

//enum Dir { UP, DOWN, LEFT, RIGHT, STOP };

class Tank:public Object
{
public:
	Tank()
	{
		m_dir = Dir::UP;
		m_step = 4;
		m_bDisappear = false; 
	}
	~Tank() {}
	virtual void Display() = 0;
	virtual void Move(Map mp) = 0;
	virtual void modifyMap(Map mp, int n) = 0;
	virtual void modifyMap(Map mp, int x, int y, int n) = 0;
	virtual void setDir(int i, int j) = 0;
	virtual void setDir(Dir dir) = 0;
	virtual bool NeedShoot() = 0;
	//void CalculateSphere() {}
	int getX()
	{
		return m_x;
	}
	int getY()
	{
		return m_y;
	}
	void setX(int X)
	{
		m_x = X;
	}
	void setY(int Y)
	{
		m_y = Y;
	}
	void Shoot(list<Object*>& lstBullets)
	{
		// Shoot
	}

	bool IsDisappear()
	{
		return m_bDisappear;
	}

protected:
	int m_x;
	int m_y;
	COLORREF m_color;

	Dir m_dir;
	int m_step;
	bool m_bNeedShoot;
	virtual void DrawTankBody() = 0;
};

#endif