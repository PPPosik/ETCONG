#include "stdafx.h"
#include "CustomThread.h"

#include "MainFrm.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"

#define MOVE 100
#define ATTACK 101
#define AFTER_MOVE 102
#define AFTER_ATTACK 103

CCustomThread::CCustomThread()
{
	pClick = NULL;
	pAbsolute = NULL;
}


CCustomThread::~CCustomThread()
{
}


UINT CCustomThread::ThreadAbsolute(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;
	CDC *pDC = pView->GetDC();
	int beat = 0;
	

	while (1)
	{		
		if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK)
			pView->m_nTimerFlag = MOVE;
		else if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE)
			pView->m_nTimerFlag = ATTACK;
		
		pView->Invalidate();
		Sleep(pView->m_nTime);
	}

	return 0;
}


UINT CCustomThread::ThreadClickDelay(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;

	while (1) {
		pView->m_bClickable = true;
		Sleep(pView->m_nClick);
		pView->m_bClickable = false;
		Sleep(pView->m_nDelay);
	}

	return 0;
}


void CCustomThread::StartThread()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();
	printf("¾²·ñµå : %d\n", pView->GetDlgCtrlID());

	pClick = AfxBeginThread(ThreadClickDelay, pView);
	pAbsolute = AfxBeginThread(ThreadAbsolute, pView);

	if (pClick == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pClick->m_hThread);
	pClick->m_hThread = NULL;

	if (pAbsolute == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pAbsolute->m_hThread);
	pAbsolute->m_hThread = NULL;
}

void CCustomThread::StopThread()
{
	pClick->SuspendThread();
	pAbsolute->SuspendThread();

	DWORD dwResult;
	::GetExitCodeThread(pClick->m_hThread, &dwResult);
	::GetExitCodeThread(pAbsolute->m_hThread, &dwResult);

	delete pClick;
	delete pAbsolute;
}
