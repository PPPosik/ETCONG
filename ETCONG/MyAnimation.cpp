#include "stdafx.h"
#include "MyAnimation.h"

#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"

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
}


void CMyAnimation::PlayAnimation(LPVOID view)
{
	CETCONGView *pView = (CETCONGView*)view;
	
	

	for (int i = 0; i < MAX_MOVE_CNT; i++) {
		pView->m_display.ActiveMoveAnimation(i);
		pView->Invalidate(TRUE);		
		Sleep(20);
	}

	pView->m_display.EndMoveAnimation();
	pView->Invalidate(TRUE);

	
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
	
	
	PlayAnimation(pView);

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
	CloseHandle(pAnimation->m_hThread);
	pAnimation->m_hThread = NULL;
}