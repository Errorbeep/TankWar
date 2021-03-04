#ifndef __MAIN_TANK__
#define __MAIN_TANK__

#include "Tank.h"

class MainTank : public Tank
{
public:
	MainTank();

	~MainTank() {}

	// 设置行驶方向
	void setDir(Dir dir);
	void setDir(int i, int j);
	void Display();
	void Move(Map mp);
	void modifyMap(Map mp, int n);
	void modifyMap(Map mp, int x, int y, int n);
	void Shoot(list<Object*>& lstBullets);
	bool NeedShoot()
	{
		return m_bNeedShoot;

	}
	//void CalculateSphere();
protected:
	// 绘制坦克主体
	void DrawTankBody();
};

#endif