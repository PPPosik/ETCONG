#pragma once

#include "atlImage.h"

class CPlayer {
private:
	int m_nLife;
	bool IsAlive;
	CPoint m_pPos;

public:


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

