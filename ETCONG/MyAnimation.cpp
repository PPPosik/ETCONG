#include "stdafx.h"
#include "MyAnimation.h"

#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")


struct STRUCT {
	CETCONGView *pView;
	CMyAnimation *self;
};
STRUCT* pStruct = new STRUCT;


CMyAnimation::CMyAnimation()
{
	m_pPos = CPoint(200, 200);
	m_nWidth = 100;
	m_nHeight = 150;
}


CMyAnimation::~CMyAnimation()
{
}


void CMyAnimation::InitAnimation()
{
	CString str;
	for (int i = 1; i <= MAX_MOVE_CNT; i++) {
		str.Format(_T("res\\%d.png"), i);
		m_ImgMove[i - 1].Load(str);
	}
	m_ImgBackground.Load(_T("res\\background.png"));

	m_nWidth = m_ImgMove[0].GetWidth();
	m_nHeight = m_ImgMove[0].GetHeight();
}


void CMyAnimation::PlayAnimation(CDC *pDC, LPVOID view)
{
	CETCONGView *pView = (CETCONGView*)view;
	
	CRect rect;
	pView->GetClientRect(rect);
	CDC memDC;
	CBitmap* pOldBitmap;
	CBitmap bmp;

	memDC.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	for (int i = 0; i < MAX_MOVE_CNT; i++) {
		printf("%d ", i);
	
		pOldBitmap = (CBitmap*)memDC.SelectObject(&bmp);

		m_ImgBackground.BitBlt(memDC.m_hDC, pView->m_pBackgroundPos.x, pView->m_pBackgroundPos.y);
		m_ImgMove[i].TransparentBlt(memDC.m_hDC, m_pPos.x, m_pPos.y, m_nWidth, m_nHeight, RGB(255, 255, 255));
		pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		
		memDC.SelectObject(pOldBitmap);
		Sleep(20);
	}

	memDC.DeleteDC();
}


CPoint CMyAnimation::getPos()
{
	return m_pPos;
}


void CMyAnimation::setPos(int x, int y)
{
	m_pPos = CPoint(x, y);
}


UINT CMyAnimation::ThreadAnimation(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;
	CDC *pDC = pView->GetDC();
	
	PlayAnimation(pDC, pView);

	return 0;
}


UINT CMyAnimation::ThreadStaticAnimation(LPVOID _mothod)
{
	STRUCT* pStruct = (STRUCT*)_mothod;

	return pStruct->self->ThreadAnimation(pStruct->pView);
}


void CMyAnimation::StartThread()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();
	pStruct->pView = pView;
	pStruct->self = this;
	
	CWinThread *pAnimation = NULL;

	pAnimation = AfxBeginThread(ThreadStaticAnimation, pStruct);

	if (pAnimation == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pAnimation);
}