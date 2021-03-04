#ifndef __BULLET_H__
#define __BULLET_H__

#include "Object.h"

class Bullet : public Object
{
public:
	Bullet();
	Bullet(int x, int y, Dir dir, COLORREF color, int User);
	~Bullet();

	void Display();

	void Move(Map mp);

	bool IsDisappear()
	{
		return m_bDisappear;
	}

protected:
	//void CalculateSphere();
	int user;
	void putTankBoom(int x, int y);
	
};

#endif