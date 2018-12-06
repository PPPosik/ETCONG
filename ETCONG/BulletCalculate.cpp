#include "stdafx.h"
#include "BulletCalculate.h"

#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "MainFrm.h"
#include "Enemy.h"

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
	//new CImage.Load(_T("res\\bullet.png"));
	
}


CBulletCalculate::~CBulletCalculate()
{
}




int CBulletCalculate::theBulletWay(int launch_ax)
{
	
	Sleep(10);

	return launch_ax + 50;
	
}




void CBulletCalculate::shootBullet(UINT nChar, int player_x, int player_y)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();

	CDC* pDC = pView->GetDC();
	CRect rect;
	pView->GetClientRect(rect);
	CDC memDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	KeyInput = nChar;
	launch_X = player_x;
	launch_Y = player_y;
	enemy_x = pView->m_aEnemy.m_pPos.x;
	enemy_y = pView->m_aEnemy.m_pPos.y;
	enemy_w = pView->m_aEnemy.m_nWidth;
	enemy_h = pView->m_aEnemy.m_nHeight;
	CImage m_imgBulletPlayer;
	m_imgBulletPlayer.Load(_T("res\\bullet.png"));

	//m_imgBulletPlayer.BitBlt(pDC->m_hDC, m_pBackgroundPos.x, m_pBackgroundPos.y);
	//CBulletCalculate m_aBullet;
	//m_imgBulletPlayer.Load(_T("res\\bullet.png"));
	//AfxMessageBox(_T("shooted"));
	for (int i = 0; i < 15; i++) {

		pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);
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
		
		}
		pView->m_ImgBackground.BitBlt(memDC.m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
		m_imgBulletPlayer.TransparentBlt(memDC.m_hDC, launch_X, launch_Y, 100, 100, RGB(255, 255, 255));
		

		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		memDC.SelectObject(pOldBitmap);

		if(pView->m_aEnemy.IsAlive){
			if (((launch_X + 25 < enemy_x + enemy_w) && (launch_X + 75 > enemy_x)) && ((launch_Y + 25 < enemy_y + enemy_h) && (launch_Y + 75 > enemy_y)))
			{
				pView->m_aEnemy.Ouchhurt();
				return;
			}
		}
		

		Sleep(10);
	}

	memDC.DeleteDC();
	//m_aBullet.theBulletWay(KeyInput, player_x, player_y);
	
}

UINT CBulletCalculate::ThreadEnemyBullet(LPVOID _mothod)
{
	Enyme* pStruct = (Enyme*)_mothod;
	CETCONGView *pView = (CETCONGView*)pStruct->pView;
	CDC *pDC = pView->GetDC();

	//printf("yes1");
	shootWild(pDC, pView, pStruct->aEx, pStruct->aEy, pStruct->pPx, pStruct->pPy);

	return 0;
}

UINT CBulletCalculate::ThreadEnemyBulletTimer(LPVOID _mothod)
{
	Enyme* pStruct = (Enyme*)_mothod;

	//printf("yes2");
	return pStruct->self->ThreadEnemyBullet(pStruct);
}


void CBulletCalculate::EnemyThread()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();
	pEnyme->pView = pView;
	pEnyme->self = this;
	pEnyme->aEx = pView->m_aEnemy.m_pPos.x;
	pEnyme->aEy = pView->m_aEnemy.m_pPos.y;
	pEnyme->pPx = 1280 / 2 - 50;//- (pView->m_pBackgroundPos.x);
	pEnyme->pPy = 720 / 2 - 70; //- (pView->m_pBackgroundPos.y);

	CWinThread *pEnemyAttack = NULL;
	//printf("yes3");
	pEnemyAttack = AfxBeginThread(ThreadEnemyBulletTimer, pEnyme);
	//printf("yes4");
	if (pEnemyAttack == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pEnemyAttack);
}


void CBulletCalculate::shootWild(CDC *pDC, LPVOID view, int enemy_x, int enemy_y, int player_x, int player_y)
{
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
		//pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		pDC->TransparentBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, rect.Width(), rect.Height(), RGB(0, 0, 0));
		memDC.SelectObject(pOldBitmap);
		
		//m_imgWildBoss.TransparentBlt(pDC->m_hDC, bpx, bpy, 100, 100, RGB(255, 255, 255));
		//m_imgWildBoss.BitBlt(pDC->m_hDC, launch_X+50, launch_Y);
		Sleep(50);
	}
	memDC.DeleteDC();
}
