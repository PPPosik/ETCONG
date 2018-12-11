#pragma once


#include "atltypes.h"
#include "atlimage.h"
#include "BulletCalculate.h"

class CEnemy
{
public:
	CEnemy();
	~CEnemy();
	int m_nLife;
	int m_nWidth;
	int m_nHeight;
	int m_nLoopLife;
	void Ouchhurt();
	CPoint m_pPos;
	bool IsAlive;
	void ImageInit();
	CImage m_imgDefault;
	void Imageprint();
	void AttackTimer();
	CBulletCalculate newtwo;
};
