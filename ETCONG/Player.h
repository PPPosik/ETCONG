#pragma once

#include "atlImage.h"

class CPlayer {
private:
	int m_nLife;
	CPoint m_pPos;

public:
	bool IsAlive;

public:
	CPlayer();
	~CPlayer();

	int getLife();
	void setLife(int life);
	CPoint getPos();
	void setPos(int x, int y);
	void ImageInit();
	void OuchHurt();
};

