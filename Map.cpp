#include <graphics.h>
#include"Tank.h"
#include"Map.h"
#include"MainTank.h"

Map::Map(int m[M][N])
{
	map = new int*[M];
	for (int k = 0; k < M; k++)
		map[k] = new int[N];
	int i, j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			map[i][j] = m[i][j];
		}
	}
}

Map::Map()
{
	map = new int*[M];
	for (int k = 0; k < M; k++)
		map[k] = new int[N];
}
/*
Map::~Map()
{

	for (int i = 0; i < M; i++)
		delete[]map[i];
	delete[]map;

}*/


void Map::setMap(int* m[N])
{
	int i, j;
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++)
		{
			map[i][j] = m[i][j];
		}
	}
}

int Map::getN(int i, int j)
{
	return map[i][j];
}

void Map::setMap(int i, int j, int n)
{
	map[i][j] = n;
}
void Map::Display()
{
	IMAGE brick1;
	IMAGE brick2;
	IMAGE home;
	loadimage(&home, _T("home.jpg"), 50, 50);
	loadimage(&brick1, _T("wall1.jpg"), 25, 25);
	loadimage(&brick2, _T("wall3.jpg"), 25, 25);
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			switch (map[i][j])
			{
			case 1:putimage(j * 25, i * 25, &brick1); break;
			case 2:putimage(j * 25, i * 25, &brick2); break;
			case 3:
				putimage(j * 25, i * 25, &home);
				//mp.setMap(i, j, 4);
				map[i][j] = 4;
				break;
			//case 5:tank->Display();
			case 4: break;
			default:
				setfillcolor(BLACK);
				solidrectangle(j * 25, i * 25, j * 25 + 50, i * 25 + 50);
			}
		}
	}
	return;

}
int Map::getWidth()
{
	return N;
}

int Map::getHight()
{
	return M;
}