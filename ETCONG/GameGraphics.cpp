#include "stdafx.h"
#include "GameGraphics.h"
#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"

#define MOVE 100
#define ATTACK 101
#define AFTER_MOVE 102
#define AFTER_ATTACK 103

struct GAMESTRUCT {
	CETCONGView *pView;
	CGameGraphics *self;
};
GAMESTRUCT* pStruct = new GAMESTRUCT;

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
	pStruct->pView = pView;
	pStruct->self = this;

	CWinThread *pDisplay = NULL;

	pDisplay = AfxBeginThread(DisplayStatic, pStruct);

	if (pDisplay == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pDisplay);
}

UINT CGameGraphics::DisplayStatic(LPVOID _mothod) {
	GAMESTRUCT* pStruct = (GAMESTRUCT*)_mothod;

	return pStruct->self->Display(pStruct->pView);
}

UINT CGameGraphics::Display(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;
	CDC *pDC = pView->GetDC();
	bool testb = true;

	CRect rect;
	pView->GetClientRect(rect);
	CDC memDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	while (1) {
		pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);
		m_ImgBackground.BitBlt(memDC.m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
		

		if (pView->m_aEnemy.IsAlive) {
			m_imgEnemyDefault.BitBlt(memDC.m_hDC, pView->m_aEnemy.m_pPos.x, pView->m_aEnemy.m_pPos.y);
		}

		if (DoesEnemyaMined && m_nEnemyMineLevel < 3 ) {
			
			m_imgMineAttack[m_nEnemyMineLevel].BitBlt(memDC.m_hDC, m_nEnemyMinePos.x, m_nEnemyMinePos.y);
		}

		if (pView->m_bError) {
			//m_ImgError.BitBlt(memDC.m_hDC, pView->m_player.getPos().x , pView->m_player.getPos().y);
		}
		
		if(IsMoveActivated)
		{
			
			if (MotionCount == 9) {
				IsMoveActivated = false;

			}
			else {
				m_ImgMoveAni[MotionCount].TransparentBlt(memDC.m_hDC, pView->m_player.getPos().x, pView->m_player.getPos().y-50, m_ImgMoveAni[0].GetWidth(), m_ImgMoveAni[0].GetHeight(), RGB(255, 255, 255));
				MotionCount++;
				//printf("ihateyou");
				pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
				memDC.SelectObject(pOldBitmap);
				Sleep(20);

				continue;
			}

		}
		if (!IsMoveActivated) {
			if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE) {
				m_ImgMove.BitBlt(memDC.m_hDC, pView->m_player.getPos().x, pView->m_player.getPos().y);
			}
			else if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK) {
				m_ImgAttack.BitBlt(memDC.m_hDC, pView->m_player.getPos().x, pView->m_player.getPos().y);
			}
		}
		if (IsBulletShooted) {
			
			
				m_imgBulletfromUser.TransparentBlt(memDC.m_hDC, m_nPlayerBulletPos.x, m_nPlayerBulletPos.y, 100, 100, RGB(255, 255, 255));
				//MotionCount++;
				printf("ihityou");
				//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
				//memDC.SelectObject(pOldBitmap);
				//Sleep(10);
				
				//continue;
			
		}


		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);

		break;
	}
	memDC.DeleteDC();

	return 0;
}


void CGameGraphics::Init()
{
	IsMoveActivated = false;
	IsBulletShooted = false;
	DoesEnemyaMined = false;
	m_ImgBackground.Load(_T("res\\background.png"));
	m_ImgMove.Load(_T("res\\player.png"));
	m_ImgAttack.Load(_T("res\\attack.png"));
	m_ImgError.Load(_T("res\\error.png"));
	m_imgEnemyDefault.Load(_T("res\\히오스명언.PNG"));
	m_imgBulletfromUser.Load(_T("res\\bullet.png"));
	m_imgMineAttack[0].Load(_T("res\\mine4.jpg"));
	m_imgMineAttack[1].Load(_T("res\\mine5.jpg"));
	m_imgMineAttack[2].Load(_T("res\\mine6.jpg"));

	CString str;
	for (int i = 1; i <= 9; i++) {
		str.Format(_T("res\\%d.png"), i);
		m_ImgMoveAni[i - 1].Load(str);
	}
	MotionCount = 0;
}

void CGameGraphics::ActiveMoveAnimation()
{
	IsMoveActivated = true;
	MotionCount = 0;
}


void CGameGraphics::ActiveBulletAnimation(int x, int y)
{
	IsBulletShooted = true;
	m_nPlayerBulletPos.x = x;
	m_nPlayerBulletPos.y = y;
	DisplayThread();
	
}


void CGameGraphics::EndBulletAnimation()
{
	IsBulletShooted = false;
}


void CGameGraphics::ActiveEnemyMine(int lv, int x, int y)
{
	DoesEnemyaMined = true;
	m_nEnemyMineLevel = lv;
	m_nEnemyMinePos.x = x;
	m_nEnemyMinePos.y = y;
	
}
