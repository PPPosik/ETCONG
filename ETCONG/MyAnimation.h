#pragma once

#include "atlImage.h"

#define MAX_MOVE_CNT 9

class CMyAnimation
{
public:
	CMyAnimation();
	~CMyAnimation();
	void InitAnimation();
	void PlayAnimation(CDC *pDC, LPVOID view);

	CPoint m_pPos;
	CImage m_ImgMove[MAX_MOVE_CNT];
	CImage m_ImgBackground;
	int m_nWidth;
	int m_nHeight;

	CPoint getPos();
	void setPos(int x, int y);

	UINT ThreadAnimation(LPVOID _mothod);
	static UINT ThreadStaticAnimation(LPVOID _mothod);
	void StartThread();
};

