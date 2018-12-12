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
	CImage move, attack;
	HRESULT hResultMove = move.Load(_T("res\\player.png"));
	HRESULT hResultAttack = attack.Load(_T("res\\attack.png"));
	int beat = 0;
	

	while (1)
	{
		//Sleep(pView->m_nTime);
		
		Sleep(10);
		beat += 10;
		//pView->m_display.DisplayThread();
		
		if (beat == pView->m_nTime) {
			beat = 0;
			if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK)
				pView->m_nTimerFlag = MOVE;
			else if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE)
				pView->m_nTimerFlag = ATTACK;
		}
		pView->Invalidate();
		
		/*
		if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK)
			pView->m_nTimerFlag = MOVE;
		else if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE)
			pView->m_nTimerFlag = ATTACK;
		pView->Invalidate();
		*/
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
	CloseHandle(pClick);

	if (pAbsolute == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(pAbsolute);
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
