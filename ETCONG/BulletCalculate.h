

#pragma once
class CBulletCalculate
{
public:
	CBulletCalculate();
	~CBulletCalculate();
	int theBulletWay(int);

	void shootBullet(UINT nChar, int player_x, int player_y);

	UINT KeyInput;
	int launch_X;
	int launch_Y;
};

