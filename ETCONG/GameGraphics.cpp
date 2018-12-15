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
	pDisplay = NULL;
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
	pDisplay = NULL;
	pDisplay = AfxBeginThread(DisplayStatic, pStruct);
	

	if (pDisplay == NULL) {
		AfxMessageBox(L"Error");
		
	}
	if (pDisplay != NULL) {
		//pDisplay->SuspendThread();
		//DWORD dwResult;
		//::GetExitCodeThread(pDisplay->m_hThread, &dwResult);
	}
	CloseHandle(pDisplay->m_hThread);
	pDisplay->m_hThread = NULL;
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
	//printf("you son");
	
		pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);
		m_ImgBackground.BitBlt(memDC.m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);

		if (DoesEnemyaMined && m_nEnemyMineLevel < 3 ) {
			
			m_imgMineAttack[m_nEnemyMineLevel].TransparentBlt(memDC.m_hDC, m_nEnemyMinePos.x, m_nEnemyMinePos.y, 300, 300, RGB(255, 255, 255));
		}

		if (pView->m_aEnemy.IsAlive) {
			m_imgEnemyDefault.TransparentBlt(memDC.m_hDC, pView->m_aEnemy.m_pPos.x, pView->m_aEnemy.m_pPos.y, 300, 300, RGB(255, 0, 0));
		}

		if (pView->m_bError) {
			//m_ImgError.BitBlt(memDC.m_hDC, pView->m_player.getPos().x , pView->m_player.getPos().y);
		}

		if (DoesEnemyBlined)
		{
			m_imgBlind.TransparentBlt(memDC.m_hDC, 0, 0, 1280, 720, RGB(255, 255, 255));
		}
		if (IsWildvxCrossed)
		{
			m_imgWIld[0].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos1.x, m_nEnemyWildPos1.y, 100, 100, RGB(255, 255, 251));
			m_imgWIld[1].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos1.x, m_nEnemyWildPos1.y + 100, 100, 100, RGB(255, 255, 251));
			m_imgWIld[2].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos1.x, m_nEnemyWildPos1.y + 200, 100, 100, RGB(255, 255, 251));
			m_imgWIld[3].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos2.x, m_nEnemyWildPos2.y, 100, 100, RGB(255, 255, 251));
			m_imgWIld[4].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos2.x, m_nEnemyWildPos2.y + 100, 100, 100, RGB(255, 251, 255));
			m_imgWIld[5].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos2.x, m_nEnemyWildPos2.y + 200, 100, 100, RGB(255, 251, 255));
			
		}
		if (IsWildvyCrossed)
		{
			m_imgWIld[0].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos1.x, m_nEnemyWildPos1.y, 100, 100, RGB(255, 255, 215));
			m_imgWIld[1].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos1.x + 100, m_nEnemyWildPos1.y, 100, 100, RGB(255, 215, 255));
			m_imgWIld[2].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos1.x + 200, m_nEnemyWildPos1.y, 100, 100, RGB(255, 215, 255));
			m_imgWIld[3].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos2.x, m_nEnemyWildPos2.y, 100, 100, RGB(255, 255, 251));
			m_imgWIld[4].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos2.x + 100, m_nEnemyWildPos2.y, 100, 100, RGB(255, 215, 255));
			m_imgWIld[5].TransparentBlt(memDC.m_hDC, m_nEnemyWildPos2.x + 200, m_nEnemyWildPos2.y, 100, 100, RGB(255, 215, 255));
			
		}

		
		for (int hpp = 0; hpp < m_nPlayerLifeLeft; hpp++) {
			m_imgPlayerHP[hpp].TransparentBlt(memDC.m_hDC, 110 * hpp + 10, 570, 100, 100, RGB(255, 255, 255));
		}
		for (int hppp = 2; hppp >= m_nPlayerLifeLeft; hppp--) {
			m_imgHurt[hppp].TransparentBlt(memDC.m_hDC, 110 * hppp + 10, 570, 100, 100, RGB(255, 255, 255));
		}
		
		if(IsMoveActivated)
		{
			/*
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
			*/
			m_ImgMoveAni[MotionCount].TransparentBlt(memDC.m_hDC, pView->m_player.getPos().x, pView->m_player.getPos().y - 50, m_ImgMoveAni[0].GetWidth(), m_ImgMoveAni[0].GetHeight(), RGB(255, 0, 0));

		}
		if (!IsMoveActivated) {
			if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE) {
				m_ImgMove.TransparentBlt(memDC.m_hDC, pView->m_player.getPos().x, pView->m_player.getPos().y, 100, 100, RGB(255, 0, 0));
			}
			else if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK) {
				m_ImgAttack.TransparentBlt(memDC.m_hDC, pView->m_player.getPos().x, pView->m_player.getPos().y, 100, 100, RGB(255, 0, 0));
			}
		}
		//printf("\n==%d==%d", m_nPlayerBulletPos.x, m_nPlayerBulletPos.y);
		if (IsBulletShooted) {
			
			
				m_imgBulletfromUser.TransparentBlt(memDC.m_hDC, m_nPlayerBulletPos.x, m_nPlayerBulletPos.y, 100, 100, RGB(255, 255, 255));
				//printf("\n==%d==%d", m_nPlayerBulletPos.x, m_nPlayerBulletPos.y);
				//MotionCount++;
				//printf("ÃÑ½÷ º´ÙÀÌ¸»ÀÌ¾ß\n");
				//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
				//memDC.SelectObject(pOldBitmap);
				//Sleep(10);
				
				//continue;
			
		}

		


		



		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.SelectObject(pOldBitmap);

		
	
	memDC.DeleteDC();

	return 0;
}


void CGameGraphics::Init()
{
	IsMoveActivated = false;
	IsBulletShooted = false;
	DoesEnemyaMined = false;
	DoesEnemyBlined = false;
	IsWildvxCrossed = false;
	IsWildvyCrossed = false;
	m_ImgBackground.Load(_T("res\\map4.png"));
	m_ImgMove.Load(_T("res\\playerright.png"));
	m_ImgAttack.Load(_T("res\\playerrightatt.png"));
	m_ImgError.Load(_T("res\\mine3.png"));
	m_imgEnemyDefault.Load(_T("res\\boss.png"));
	m_imgBulletfromUser.Load(_T("res\\bullet.png"));
	m_imgMineAttack[0].Load(_T("res\\saturdat.png"));
	m_imgMineAttack[1].Load(_T("res\\sundat.png"));
	m_imgMineAttack[2].Load(_T("res\\deleteday.png"));
	m_imgBlind.Load(_T("res\\Blind2.png"));
	m_imgWIld[0].Load(_T("res\\bullet.png"));
	m_imgWIld[1].Load(_T("res\\bullet.png"));
	m_imgWIld[2].Load(_T("res\\bullet.png"));
	m_imgWIld[3].Load(_T("res\\bullet.png"));
	m_imgWIld[4].Load(_T("res\\bullet.png"));
	m_imgWIld[5].Load(_T("res\\bullet.png"));
	



	CString str;
	for (int i = 1; i <= 9; i++) {
		str.Format(_T("res\\r%d.png"), i);
		m_ImgMoveAni[i - 1].Load(str);
	}
	for (int i = 0; i <= 2; i++) {
		str.Format(_T("res\\hearrt.png"));
		m_imgPlayerHP[i].Load(str);
		m_imgHurt[i].Load(_T("res\\heardt.png"));
	}
	MotionCount = 0;
	m_nPlayerLifeLeft = 3;
}

void CGameGraphics::ActiveMoveAnimation(int count)
{
	IsMoveActivated = true;
	MotionCount = count;
}


void CGameGraphics::ActiveBulletAnimation(int x, int y)
{
	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	//CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();
	IsBulletShooted = true;
	m_nPlayerBulletPos.x = x;
	m_nPlayerBulletPos.y = y;
	//printf("\n--%d--%d", m_nPlayerBulletPos.x, m_nPlayerBulletPos.y);
	//DisplayThread();
	//pBulletView->Invalidate();
	//Display(pView);
	
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


void CGameGraphics::ActiveEnemyBlind()
{
	DoesEnemyBlined = true;
}


void CGameGraphics::RevealedPlayerBling()
{
	DoesEnemyBlined = false;
}


void CGameGraphics::ActiveWildtoX(int y, int x1, int x2)
{
	IsWildvxCrossed = true;
	m_nEnemyWildPos1.x = x1;
	m_nEnemyWildPos2.x = x2;
	m_nEnemyWildPos1.y = y;
	m_nEnemyWildPos2.y = y;
	//DisplayThread();
	//pBulletView->Invalidate();
}


void CGameGraphics::ActiveWildtoY(int x, int y1, int y2)
{
	IsWildvyCrossed = true;
	m_nEnemyWildPos1.x = x;
	m_nEnemyWildPos2.x = x;
	m_nEnemyWildPos1.y = y1;
	m_nEnemyWildPos2.y = y2;
	//DisplayThread();
	//pBulletView->Invalidate();
}


void CGameGraphics::EndWildtoX()
{
	IsWildvxCrossed = false;
}


void CGameGraphics::EndWildtoY()
{
	IsWildvyCrossed = false;
}


void CGameGraphics::PlayerHurt()
{
	m_nPlayerLifeLeft--;
	
	//m_imgPlayerHP[m_nPlayerLifeLeft].Destroy();

	//m_imgPlayerHP[m_nPlayerLifeLeft] = m_imgHurt;
	//m_imgPlayerHP[m_nPlayerLifeLeft].Load(_T("res\\player.png"));
	
}


void CGameGraphics::EndMoveAnimation()
{
	IsMoveActivated = false;
}

// Â¯Áø
void CGameGraphics::LeftPlayer() {
	m_ImgMove.Destroy();
	m_ImgMove.Load(_T("res\\playerleft.png"));

	for (int i = 1; i <= 9; i++) {
		m_ImgMoveAni[i - 1].Destroy();
	}
	CString str;
	for (int i = 1; i <= 9; i++) {
		str.Format(_T("res\\l%d.png"), i);
		m_ImgMoveAni[i - 1].Load(str);
	}

	m_ImgAttack.Destroy();
	m_ImgAttack.Load(_T("res\\playerleftatt.png"));
}


void CGameGraphics::RightPlayer() {
	m_ImgMove.Destroy();
	m_ImgMove.Load(_T("res\\playerright.png"));

	for (int i = 1; i <= 9; i++) {
		m_ImgMoveAni[i - 1].Destroy();
	}
	CString str;
	for (int i = 1; i <= 9; i++) {
		str.Format(_T("res\\r%d.png"), i);
		m_ImgMoveAni[i - 1].Load(str);
	}

	m_ImgAttack.Destroy();
	m_ImgAttack.Load(_T("res\\playerrightatt.png"));
}
