#include "stdafx.h"
#include "GameGraphics.h"
#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"

#define MOVE 100
#define ATTACK 101
#define AFTER_MOVE 102
#define AFTER_ATTACK 103


CGameGraphics::CGameGraphics()
{
}


CGameGraphics::~CGameGraphics()
{
}



void CGameGraphics::DisplayThread()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();

	CWinThread *pDisplay = NULL;

	pDisplay = AfxBeginThread(Display, pView);

	if (pDisplay == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pDisplay);
}


UINT CGameGraphics::Display(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;
	CDC *pDC = pView->GetDC();
	bool testb = true;

	CImage m_ImgBackground;
	CImage m_ImgMove;
	CImage m_ImgAttack;
	CImage m_ImgError;
	CImage m_imgEnemyDefault;
	
	m_ImgBackground.Load(_T("res\\background.png"));
	m_ImgMove.Load(_T("res\\player.png"));
	m_ImgAttack.Load(_T("res\\attack.png"));
	m_ImgError.Load(_T("res\\error.png"));
	m_imgEnemyDefault.Load(_T("res\\히오스명언.PNG"));

	CRect rect;
	pView->GetClientRect(rect);
	CDC memDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	
	while (testb)
	{
		pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);
		m_ImgBackground.BitBlt(memDC.m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
		//printf("ihateyou");
		
		if (pView->m_aEnemy.IsAlive) {
			m_imgEnemyDefault.BitBlt(memDC.m_hDC, pView->m_aEnemy.m_pPos.x, pView->m_aEnemy.m_pPos.y);
		}

		if (pView->m_bError) {
			//m_ImgError.BitBlt(memDC.m_hDC, pView->m_player.getPos().x , pView->m_player.getPos().y);
		}
		if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE) {
			m_ImgMove.BitBlt(memDC.m_hDC, pView->m_player.getPos().x, pView->m_player.getPos().y);
		}
		else if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK) {
			m_ImgAttack.BitBlt(memDC.m_hDC, pView->m_player.getPos().x , pView->m_player.getPos().y);
		}

		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);

		
	}
	
	
	memDC.DeleteDC();

	return 0;
}
