
#include "stdafx.h"

#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "Enemy.h"




CEnemy::CEnemy()
{
	m_nLife = 103;
	m_nWidth = 600;
	m_nHeight = 500;
	IsAlive = true;
	
}


CEnemy::~CEnemy()
{
}


void CEnemy::Ouchhurt()
{
	m_nLife = m_nLife - 1;
	if (m_nLife == 0)
	{
		IsAlive = false;
	}
	AttackTimer();
}



void CEnemy::ImageInit()
{
	IsAlive = true;
	m_imgDefault.Load(_T("res\\히오스명언.PNG"));
	m_pPos = CPoint(500, 500);
	
	
	
}




void CEnemy::Imageprint()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();

	CDC* pDC = pView->GetDC();

	m_imgDefault.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
}


void CEnemy::AttackTimer()
{
	printf("yes");
	
	newtwo.EnemyThread();
	
	
}
