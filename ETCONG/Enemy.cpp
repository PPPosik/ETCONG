
#include "stdafx.h"

#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "Enemy.h"
#include "ETCONG.h"



CEnemy::CEnemy()
{
	m_nLife = 5;
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
		IsAlive = false;
		CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
		pApp->CallDeath(FALSE);
	}
	
	
}



void CEnemy::ImageInit()
{
	IsAlive = true;
	m_imgDefault.Load(_T("res\\���������.PNG"));
	m_pPos = CPoint(1090, 610);
}




void CEnemy::Imageprint()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();

	CDC* pDC = pView->GetDC();

	m_imgDefault.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
}


void CEnemy::AttackTimer(LPVOID view)
{

	
	CETCONGView *pView = (CETCONGView*)view;

	
	newtwo.EnemyThread(pView);
	
	
}
