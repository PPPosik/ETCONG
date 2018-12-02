#include "stdafx.h"
#include "BulletCalculate.h"

#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "MainFrm.h"


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
	KeyInput = nChar;
	launch_X = player_x;
	launch_Y = player_y;
	CImage m_imgBulletPlayer;
	m_imgBulletPlayer.Load(_T("res\\bullet.png"));

	//m_imgBulletPlayer.BitBlt(pDC->m_hDC, m_pBackgroundPos.x, m_pBackgroundPos.y);
	//CBulletCalculate m_aBullet;
	//m_imgBulletPlayer.Load(_T("res\\bullet.png"));
	//AfxMessageBox(_T("shooted"));
	for (int i = 0; i < 15; i++) {


		switch (KeyInput) {
		case VK_UP:
			launch_Y -= 50;
			m_imgBulletPlayer.BitBlt(pDC->m_hDC, launch_X, launch_Y);
			pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);

			break;
		case VK_DOWN:
			launch_Y += 50;
			m_imgBulletPlayer.BitBlt(pDC->m_hDC, launch_X, launch_Y);
			pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
			break;
		case VK_LEFT:
			launch_X -= 50;
			m_imgBulletPlayer.BitBlt(pDC->m_hDC, launch_X, launch_Y);
			pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
			break;
		case VK_RIGHT:
			launch_X += 50;
			m_imgBulletPlayer.BitBlt(pDC->m_hDC, launch_X, launch_Y);
			pView->m_ImgBackground.BitBlt(pDC->m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
			break;

		}

		if (launch_X == 1 || launch_Y == 2)
		{
			m_imgBulletPlayer.Destroy();
		}

		Sleep(10);
	}


	//m_aBullet.theBulletWay(KeyInput, player_x, player_y);
	
}
