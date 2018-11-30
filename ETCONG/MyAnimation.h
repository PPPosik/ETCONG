#pragma once

#include "atlImage.h"


class CMyAnimation
{
public:
	CMyAnimation();
	~CMyAnimation();
	void InitAnimation();
	void PlayAnimation(CDC *pDC);

	CPoint m_pPos;
	CImage m_ImgMove1;
	CImage m_ImgMove2;
	CImage m_ImgMove3;
	CImage m_ImgMove4;
	CImage m_ImgMove5;
	CImage m_ImgMove6;
	CImage m_ImgMove7;
	CImage m_ImgMove8;
	CImage m_ImgMove9;
	int m_nWidth;
	int m_nHeight;

	CPoint getPos();
	void setPos(int x, int y);

	UINT ThreadAnimation(LPVOID _mothod);
	static UINT ThreadStaticAnimation(LPVOID _mothod);
	void StartThread();
};

