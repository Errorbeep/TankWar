#ifndef _MAP_H_

#define _MAP_H_


const int N = 30;
const int M = 30;

class Map
{
private:
	int** map;
public:
	Map();
	Map(int m[M][N]);
	~Map() {}

	void setMap(int* m[N]);
	void setMap(int i, int j,int n);
	int getN(int i, int j);
	int getWidth();
	int getHight();
	void Display();
};

#endif