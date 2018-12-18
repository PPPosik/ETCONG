
#include "stdafx.h"

#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "Enemy.h"
#include "ETCONG.h"



CEnemy::CEnemy()
{
	m_nLife = 20;
	m_nWidth = 300;
	m_nHeight = 300;
	IsAlive = true;
	m_nLoopLife = 0;
}


CEnemy::~CEnemy()
{
}


void CEnemy::Ouchhurt(LPVOID view)
{
	
	m_nLife = m_nLife - 1;
	if (m_nLoopLife == 0)
	{
		AttackTimer(view);
	}
	m_nLoopLife++;
	if (m_nLife == 0)
	{
		printf("clear\n");
		IsAlive = false;
		((CETCONGView*)view)->Invalidate();
		Sleep(3000);
		CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
		pApp->CallDeath(FALSE);
	}
	
	
}



void CEnemy::ImageInit()
{
	IsAlive = true;
	m_pPos = CPoint(1090, 610);
}



void CEnemy::AttackTimer(LPVOID view)
{

	
	CETCONGView *pView = (CETCONGView*)view;

	
	newtwo.EnemyThread(pView);
	
	
}
