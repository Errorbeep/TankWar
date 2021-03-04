#ifndef __OBJECT_H__
#define __OBJECT_H__
#include <list>
#include "Graphic.h"
#include "Map.h"
using namespace std;

enum Dir { UP, DOWN, LEFT, RIGHT, bUP, bDOWN, bLEFT, bRIGHT};

class Object
{
public:
	// 绘图
	virtual void Display() = 0;

	// 移动
	virtual void Move(Map mp) = 0;

	// 判断是否消失
	virtual bool IsDisappear() = 0;

	//virtual void Boom(list<Object*>& lstBombs) = 0;

protected:
	// 计算势力范围
	//virtual void CalculateSphere() = 0;

	// 位置
	int m_x, m_y;
	// 势力范围
	//Rect m_rectSphere;
	// 颜色
	COLORREF m_color;
	// 方向
	Dir m_dir;
	// 存在状态
	bool m_bDisappear;
	// 单次前进步长
	int m_step;
};

#endif