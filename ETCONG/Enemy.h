#pragma once


#include "atltypes.h"
#include "atlimage.h"
class CEnemy
{
public:
	CEnemy();
	~CEnemy();
	int m_nLife;
	int m_nWidth;
	int m_nHeight;
	void COuchhurt();
	CPoint m_pPos;
	void Dead();
	void ImageInit();
	CImage m_imgDefault;
	void Imageprint();
};
