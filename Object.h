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
	// ��ͼ
	virtual void Display() = 0;

	// �ƶ�
	virtual void Move(Map mp) = 0;

	// �ж��Ƿ���ʧ
	virtual bool IsDisappear() = 0;

	//virtual void Boom(list<Object*>& lstBombs) = 0;

protected:
	// ����������Χ
	//virtual void CalculateSphere() = 0;

	// λ��
	int m_x, m_y;
	// ������Χ
	//Rect m_rectSphere;
	// ��ɫ
	COLORREF m_color;
	// ����
	Dir m_dir;
	// ����״̬
	bool m_bDisappear;
	// ����ǰ������
	int m_step;
};

#endif