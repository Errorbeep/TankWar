#ifndef __POINT_H__
#define __POINT_H__

class Point
{
public:
	Point(int x = 0, int y = 0, bool Flag = false) : m_x(x), m_y(y), flag(Flag) {};
	~Point() {};

	Point& operator=(const Point &p)
	{
		m_x = p.m_x;
		m_y = p.m_y;
		flag = false;
		return *this;
	}

	void Set(int x, int y);

	void SetX(int x);
	void SetY(int y);

	int GetX();
	int GetY();
	bool GetFlag()
	{
		return flag;
	}
	void SetFlag(bool Flag)
	{
		flag = Flag;
	}


private:
	int m_x;
	int m_y;
	bool flag;
};

#endif