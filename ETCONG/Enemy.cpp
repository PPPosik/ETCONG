
#include "stdafx.h"

#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "Enemy.h"



CEnemy::CEnemy()
{
	m_nLife = 3;
	m_nWidth = 100;
	m_nHeight = 100;
	m_pPos = CPoint(300, 100);
	
}


CEnemy::~CEnemy()
{
}


void CEnemy::COuchhurt()
{
	m_nLife = m_nLife - 1;
	if (m_nLife == 0)
	{
		Dead();
	}
}


void CEnemy::Dead()
{
	m_imgDefault.Destroy();

}


void CEnemy::ImageInit()
{
	
	m_imgDefault.Load(_T("res\\히오스명언.PNG"));
	
}




void CEnemy::Imageprint()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();

	CDC* pDC = pView->GetDC();
	m_imgDefault.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
}
