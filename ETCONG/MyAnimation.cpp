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
	m_ImgMove1.Load(_T("res\\1.png"));
	m_ImgMove2.Load(_T("res\\2.png"));
	m_ImgMove3.Load(_T("res\\3.png"));
	m_ImgMove4.Load(_T("res\\4.png"));
	m_ImgMove5.Load(_T("res\\5.png"));
	m_ImgMove6.Load(_T("res\\6.png"));
	m_ImgMove7.Load(_T("res\\7.png"));
	m_ImgMove8.Load(_T("res\\8.png"));
	m_ImgMove9.Load(_T("res\\9.png"));

	m_nWidth = m_ImgMove1.GetWidth();
	m_nHeight = m_ImgMove1.GetHeight();
}


void CMyAnimation::PlayAnimation(CDC *pDC)
{	
	printf("%d %d\n", m_pPos.x, m_pPos.y);

	//m_ImgMove1.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	m_ImgMove1.TransparentBlt(pDC->m_hDC, m_pPos.x, m_pPos.y, m_nWidth, m_nHeight, RGB(255, 255, 255));
	Sleep(20);
	m_ImgMove2.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);
	m_ImgMove3.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);
	m_ImgMove4.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);
	m_ImgMove5.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);
	m_ImgMove6.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);
	m_ImgMove7.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);
	m_ImgMove8.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);
	m_ImgMove9.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	Sleep(20);

	//CImage i1, i2, i3, i4, i5, i6, i7, i8, i9;
	//
	//i1.Load(_T("res\\1.png"));
	//i1.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i2.Load(_T("res\\2.png"));
	//i2.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i3.Load(_T("res\\3.png"));
	//i3.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i4.Load(_T("res\\4.png"));
	//i4.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i5.Load(_T("res\\5.png"));
	//i5.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i6.Load(_T("res\\6.png"));
	//i6.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i7.Load(_T("res\\7.png"));
	//i7.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i8.Load(_T("res\\8.png"));
	//i8.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
	//i9.Load(_T("res\\9.png"));
	//i9.BitBlt(pDC->m_hDC, 100, 100);
	//Sleep(40);
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

	PlayAnimation(pDC);

	return 0;
}


UINT CMyAnimation::ThreadStaticAnimation(LPVOID _mothod)
{
	STRUCT* pStruct = (STRUCT*)_mothod;
	CETCONGView* pView = pStruct->pView;
	CMyAnimation* self = pStruct->self;

	return self->ThreadAnimation(pView);
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