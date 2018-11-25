#pragma once

#include "atlImage.h"

class CPlayer {
private:
	int m_nLife;
	int m_nWidth;
	int m_nHeight;
	CImage m_Img;
	CPoint m_Ppos;

public:


public:
	CPlayer();
	~CPlayer();
	int getWidth();
	void setWidth(int width);
	int getHeight();
	void setHeight(int height);
	int getLife();
	void setLife(int life);
	void drawMove(CDC *pDC);
	void drawAttack(CDC *pDC);
	void drawError(CDC *pDC);
	CPoint getPos();
	void setPos(int x, int y);
};

