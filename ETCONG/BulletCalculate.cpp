#include "stdafx.h"
#include "BulletCalculate.h"

#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "MainFrm.h"
#include "Enemy.h"


struct Plyear {
	CETCONGView *pView;
	CBulletCalculate *self;
	UINT nchar;
	int pPx;
	int pPy;

}; Plyear* pPlyear = new Plyear;

struct Enyme {
	CETCONGView *pView;
	CBulletCalculate *self;
	int aEx;
	int aEy;
	int pPx;
	int pPy;
		
};
Enyme* pEnyme = new Enyme;


CBulletCalculate::CBulletCalculate()
{
	
	
}


CBulletCalculate::~CBulletCalculate()
{
}




int CBulletCalculate::theBulletWay(int launch_ax)
{
	
	Sleep(10);

	return launch_ax + 50;
	
}

UINT CBulletCalculate::PistolThread(LPVOID _mothod)
{
	Plyear* pStruct = (Plyear*)_mothod;
	CETCONGView *pView = (CETCONGView*)pStruct->pView;
	
	//printf("yes7 %d %d %d \n", pStruct->nchar, pStruct->pPx, pStruct->pPy);
	shootBullet(pView, pStruct->nchar, pStruct->pPx, pStruct->pPy);
	//printf("yes6");
	return 0;
}


UINT CBulletCalculate::PistolThreadst(LPVOID _mothod)
{
	Plyear* pStruct = (Plyear*)_mothod;

	//printf("yes2");
	return pStruct->self->PistolThread(pStruct);
}



void CBulletCalculate::PlayerBulletThread(UINT nChar)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();
	pPlyear->pView = pView;
	pPlyear->self = this;
	pPlyear->nchar = nChar;
	pPlyear->pPx = pView->m_player.getPos().x;//- (pView->m_pBackgroundPos.x);
	pPlyear->pPy = pView->m_player.getPos().y; //- (pView->m_pBackgroundPos.y);

	pPlayerAttack = NULL;
	//printf("yes3");
	pPlayerAttack = AfxBeginThread(PistolThreadst, pPlyear);
	//printf("yes4");
	if (pPlayerAttack == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pPlayerAttack->m_hThread);
	pPlayerAttack->m_hThread = NULL;
}


void CBulletCalculate::shootBullet(LPVOID View, UINT nChar, int player_x, int player_y)
{
	
	CETCONGView *pView = (CETCONGView*)View;

	//CDC* pDC = pView->GetDC();
	//CRect rect;
	//pView->GetClientRect(rect);
	//CDC memDC;
	//CBitmap* pOldBitmap;
	//CBitmap bmp;

	//memDC.CreateCompatibleDC(pDC);
	//bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	KeyInput = nChar;
	launch_X = player_x;
	launch_Y = player_y;
	enemy_x = pView->m_aEnemy.m_pPos.x;
	enemy_y = pView->m_aEnemy.m_pPos.y;
	enemy_w = pView->m_aEnemy.m_nWidth;
	enemy_h = pView->m_aEnemy.m_nHeight;

	bool flag = true;
	

	//m_imgBulletPlayer.BitBlt(pDC->m_hDC, m_pBackgroundPos.x, m_pBackgroundPos.y);
	//CBulletCalculate m_aBullet;
	//m_imgBulletPlayer.Load(_T("res\\bullet.png"));
	//AfxMessageBox(_T("shooted"));
	//printf("yes6");
	for (int i = 0; i < 15 && flag; i++) {

		//pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);
		switch (KeyInput) {
		case VK_UP:
			launch_Y -= 50;
			//m_imgBulletPlayer.TransparentBlt(memDC.m_hDC, launch_X, launch_Y, 100, 100, RGB(255, 255, 255));
			//pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
			//pView->m_aEnemy.Imageprint();

			break;
		case VK_DOWN:
			launch_Y += 50;
			//m_imgBulletPlayer.TransparentBlt(memDC.m_hDC, launch_X, launch_Y, 100, 100, RGB(255, 255, 255));
			//pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
			//pView->m_aEnemy.Imageprint();
			break;
		case VK_LEFT:
			launch_X -= 50;
			//m_imgBulletPlayer.TransparentBlt(memDC.m_hDC, launch_X, launch_Y, 100, 100, RGB(255, 255, 255));
			//pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
			//pView->m_aEnemy.Imageprint();
			break;
		case VK_RIGHT:
			launch_X += 50;
			//m_imgBulletPlayer.BitBlt(pDC->m_hDC, launch_X, launch_Y);
			//pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
			//pView->m_aEnemy.Imageprint();
			break;
		default:
			flag = false;
			break;
		}

		if (flag) 
		{
			pView->m_display.ActiveBulletAnimation(launch_X, launch_Y);
		}
		//printf("\n++%d++%d", launch_X, launch_Y);
		pView->Invalidate(TRUE);
		
		//pView->m_ImgBackground.BitBlt(memDC.m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
		//pView->m_player.drawAttack(&memDC);
		//m_imgBulletPlayer.TransparentBlt(memDC.m_hDC, launch_X, launch_Y, 100, 100, RGB(255, 255, 255));
		

		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		//memDC.SelectObject(pOldBitmap);

		if(pView->m_aEnemy.IsAlive){
			if (((launch_X + 25 < enemy_x + enemy_w) && (launch_X + 75 > enemy_x)) && ((launch_Y + 25 < enemy_y + enemy_h) && (launch_Y + 75 > enemy_y)))
			{
				pView->m_aEnemy.Ouchhurt(pView);
				pView->m_display.EndBulletAnimation();
				pView->Invalidate(TRUE);
				return;
			}
		}
		

		Sleep(10);
	}
	pView->m_display.EndBulletAnimation();
	pView->Invalidate(TRUE);

	//memDC.DeleteDC();
	//m_aBullet.theBulletWay(KeyInput, player_x, player_y);
	
}

UINT CBulletCalculate::ThreadEnemyBullet(LPVOID _mothod)
{
	Enyme* pStruct = (Enyme*)_mothod;
	CETCONGView *pView = (CETCONGView*)pStruct->pView;
	CDC *pDC = pView->GetDC();

	//printf("yes1");
	//shootWild(pDC, pView, pStruct->aEx, pStruct->aEy, pStruct->pPx, pStruct->pPy);

	

	while (pView->m_aEnemy.IsAlive)
	{
		shootCrossWild(pDC, pView);
		if (!(pView->m_aEnemy.IsAlive)) {
			break;
		}
		Sleep((pView->m_nTime)*4);

		if (!(pView->m_aEnemy.IsAlive)) {
			break;
		}
		shootMine(pDC, pView);
		if (!(pView->m_aEnemy.IsAlive)) {
			break;
		}
		Sleep( (pView->m_nTime)*4);
		
	}

	return 0;
}

UINT CBulletCalculate::ThreadEnemyBulletTimer(LPVOID _mothod)
{
	Enyme* pStruct = (Enyme*)_mothod;

	//printf("yes2");
	return pStruct->self->ThreadEnemyBullet(pStruct);
}


void CBulletCalculate::EnemyThread(LPVOID view)
{
	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)view;
	pEnyme->pView = pView;
	pEnyme->self = this;
	pEnyme->aEx = pView->m_aEnemy.m_pPos.x;
	pEnyme->aEy = pView->m_aEnemy.m_pPos.y;
	pEnyme->pPx = 1280 / 2 - 50;//- (pView->m_pBackgroundPos.x);
	pEnyme->pPy = 720 / 2 - 70; //- (pView->m_pBackgroundPos.y);

	pEnemyAttack = NULL;
	//printf("yes3");
	pEnemyAttack = AfxBeginThread(ThreadEnemyBulletTimer, pEnyme);
	//printf("yes4");
	if (pEnemyAttack == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pEnemyAttack->m_hThread);
	pEnemyAttack->m_hThread = NULL;
}


void CBulletCalculate::shootWild(CDC *pDC, LPVOID view, int enemy_x, int enemy_y, int player_x, int player_y)
{
	//반사시키는 코드였었음. 기능 추가시 수정바람
	/*
	CETCONGView* pView = (CETCONGView*)view;
	CRect rect;
	pView->GetClientRect(rect);
	CDC memDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	CImage m_imgWildBoss;
	m_imgWildBoss.Load(_T("res\\bullet.png"));
	launch_X = enemy_x;
	launch_Y = enemy_y;
	target_x = player_x;
	target_y = player_y;
	int bpx = launch_X;
	int bpy = launch_Y;
	int linearx = (target_x - launch_X) / 10;
	int lineary = (target_y - launch_Y) / 10;
	printf("///from  %d %d    to %d %d\n", launch_X, launch_Y, target_x, target_y);
	//AfxMessageBox(_T("shooted"));
	
	CPoint prev = pView->m_pBackgroundPos;
	for (int at = 0; at < 30; at++)
	{
		CPoint now = pView->m_pBackgroundPos;
		if (prev.x != now.x || prev.y != now.y) {
			int dx = prev.x - now.x;
			int dy = prev.y - now.y;

			bpx -= dx;
			bpy -= dy;

			prev = now;

		}
		//AfxMessageBox(_T("shooted"));
		bpx += linearx;
		bpy += lineary;
		//m_imgWildBoss.BitBlt(pDC->m_hDC, launch_X-50, launch_Y);
		
		pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);

		//pView->m_ImgBackground.BitBlt(memDC.m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
		m_imgWildBoss.TransparentBlt(memDC.m_hDC, bpx, bpy, 100, 100, RGB(255, 255, 255));
		DeleteObject(m_imgWildBoss);
		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		pDC->TransparentBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, rect.Width(), rect.Height(), RGB(0, 0, 0));
		memDC.SelectObject(pOldBitmap);
		

		//m_imgWildBoss.TransparentBlt(pDC->m_hDC, bpx, bpy, 100, 100, RGB(255, 255, 255));
		//m_imgWildBoss.BitBlt(pDC->m_hDC, launch_X+50, launch_Y);
		Sleep(50);
	}
	memDC.DeleteDC();
	*/
}




void CBulletCalculate::shootMine(CDC *pDC, LPVOID view)
{
	CETCONGView* pView = (CETCONGView*)view;
	CPoint prev = pView->m_pBackgroundPos;


	int player_x = 1280 / 2 - 50 - 100;
	int player_y = 720 / 2 - 50 - 100;
	CPoint now;
	int alreadyhurt = 0;
	for (int at = 0; at < 4; at++)
	{
		pView->m_display.ActiveEnemyMine(at, player_x, player_y);
		pView->Invalidate(TRUE);
		for (int n = 0; n < 12; n++) {
			now = pView->m_pBackgroundPos;
			if (prev.x != now.x || prev.y != now.y) {
				int dx = prev.x - now.x;
				int dy = prev.y - now.y;

				player_x -= dx;
				player_y -= dy;

				prev = now;
				pView->m_display.ActiveEnemyMine(at, player_x, player_y);
			}
			if ( ((at == 0) || (at == 1)) && ((player_x <= 1280 / 2 - 50) && (player_x >= 1280 / 2 - 50 - 200)) && ((player_y <= 720 / 2 - 50) && (player_y >= 720 / 2 - 50 - 200))) {
				shootVoid(pView);
			}
			else
			{
				disableVoid(pView);
			}
			if ( (at == 2) && ((player_x <= 1280 / 2 - 50) && (player_x >= 1280 / 2 - 50 - 200)) && ((player_y <= 720 / 2 - 50) && (player_y >= 720 / 2 - 50 - 200))) {
				if (alreadyhurt == 0) {
					pView->m_player.OuchHurt();
					pView->m_display.PlayerHurt();
					alreadyhurt++;
				}
				
			}
			
			Sleep( ((pView->m_nTime)/4) );
			if (at == 3) {
				
				break;
			}

		}	
	}
	disableVoid(pView);
}


void CBulletCalculate::shootVoid(LPVOID view)
{
	CETCONGView* pView = (CETCONGView*)view;
	pView->m_display.ActiveEnemyBlind();


}


void CBulletCalculate::disableVoid(LPVOID view)
{
	CETCONGView* pView = (CETCONGView*)view;
	pView->m_display.RevealedPlayerBling();
}


void CBulletCalculate::stopThread()
{
	DWORD dwResult;
	if (pEnemyAttack->m_hThread != NULL) {
		pEnemyAttack->SuspendThread();
		::GetExitCodeThread(pEnemyAttack->m_hThread, &dwResult);
		delete pEnemyAttack;
	}
}


void CBulletCalculate::shootCrossWild(CDC *pDC, LPVOID view)
{
	CETCONGView* pView = (CETCONGView*)view;
	int LX = pView->m_aEnemy.m_pPos.x;
	int LY = pView->m_aEnemy.m_pPos.y;
	int bex1 = LX+200;
	int bex2 = LX-100;
	int bey1 = LY+200;
	int bey2 = LY-100;
	int player_x = 1280 / 2 - 50;
	int player_y = 720 / 2 - 50;

	int m_nWildVelocity = 25;

	CPoint prev = pView->m_pBackgroundPos;
	for (int at = 0; at < 30; at++)
	{
		CPoint now = pView->m_pBackgroundPos;
		if (prev.x != now.x || prev.y != now.y) {
			int dx = prev.x - now.x;
			int dy = prev.y - now.y;

			bex1 -= dx;
			bex2 -= dx;
			bey1 -= dy;
			bey2 -= dy;
			LX -= dx;
			LY -= dy;

			prev = now;

		}
		//AfxMessageBox(_T("shooted"));
		bex1 += m_nWildVelocity;
		bex2 -= m_nWildVelocity;
		pView->m_display.ActiveWildtoX(LY, bex1, bex2);
		pView->Invalidate(TRUE);

		
			if ( ( (bex1 == player_x) || (bex2 == player_x) ) && (( player_y >= LY ) && (player_y <= LY+200) ))
			{
				pView->m_player.OuchHurt();
				pView->m_display.EndWildtoX();
				pView->m_display.PlayerHurt();
				Sleep((30 - at) * 100);
				break;
			}
		

		Sleep(100);
	}
	pView->m_display.EndWildtoX();
	pView->Invalidate(TRUE);

	for (int at = 0; at < 30; at++)
	{
		CPoint now = pView->m_pBackgroundPos;
		if (prev.x != now.x || prev.y != now.y) {
			int dx = prev.x - now.x;
			int dy = prev.y - now.y;

			bex1 -= dx;
			bex2 -= dx;
			bey1 -= dy;
			bey2 -= dy;
			LX -= dx;
			LY -= dy;

			prev = now;

		}
		//AfxMessageBox(_T("shooted"));
		bey1 += m_nWildVelocity;
		bey2 -= m_nWildVelocity;
		pView->m_display.ActiveWildtoY(LX, bey1, bey2);
		pView->Invalidate();

		
			if (((bey1 == player_y) || (bey2 == player_y)) && ((player_x >= LX) && (player_x <= LX + 200)))
			{
				pView->m_player.OuchHurt();
				pView->m_display.EndWildtoY();
				pView->m_display.PlayerHurt();
				Sleep((30 - at) * 100);
				return;
			}
		

		Sleep(100);
	}
	pView->m_display.EndWildtoY();
	pView->Invalidate();

}




