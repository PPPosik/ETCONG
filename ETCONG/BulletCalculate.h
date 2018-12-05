

#pragma once
class CBulletCalculate
{
public:
	CBulletCalculate();
	~CBulletCalculate();
	int theBulletWay(int);

	void shootBullet(UINT nChar, int player_x, int player_y);

	UINT ThreadEnemyBullet(LPVOID _mothod);

	UINT KeyInput;
	int launch_X;
	int launch_Y;
	int enemy_x;
	int enemy_y;
	int enemy_w;
	int enemy_h;
	int target_x;
	int target_y;
	static UINT ThreadEnemyBulletTimer(LPVOID _mothod);
	void EnemyThread();
	void shootWild(CDC * pDC, LPVOID view, int enemy_x, int enemy_y, int player_x, int player_y);
	
};

