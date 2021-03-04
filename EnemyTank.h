#ifndef __ENEMY_TANK__
#define __ENEMY_TANK__

#include "Tank.h"
#include"Point.h"
//#include<stack>
//#include<queue>
#include<vector>
using namespace std;


const int maxPath = 140;
const int MAX_STEP_SHOOT = 3;

class EnemyTank : public Tank
{
public:
	EnemyTank(int x = 10, int y = 10);

	~EnemyTank() {}
	 
	void Display();
	void Move(Map mp);
	void modifyMap(Map mp, int n);
	void modifyMap(Map mp, int x, int y, int n);
	void setDir(int tank_x, int tank_y);
	void setDir(Dir dir);
	void detect(Map mp);
	void Shoot(list<Object*>& lstBullets);
	bool NeedShoot();
	/*


	// 设置行驶方向
	void SetDir(Dir dir);

	void Display();
	void Move(Map mp);
	void modifyMap(Map mp, int n);
//	void modifyMap(Map mp, int x, int y, int n);*/

protected:
	int m_stepCnt;
	//bool m_bNeedShoot;
	vector<Point> path;
	vector<vector<Point> > q;
	//void CalculateSphere();
	//void RandomTank();
	void DrawTankBody();

};

#endif