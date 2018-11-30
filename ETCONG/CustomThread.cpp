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

	while (1)
	{
		Sleep(pView->m_nTime);

		if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK)
			pView->m_nTimerFlag = MOVE;
		else if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE)
			pView->m_nTimerFlag = ATTACK;

		if (pView->m_nTimerFlag == MOVE) {
			move.BitBlt(pDC->m_hDC, 0, 0);
		}
		else if (pView->m_nTimerFlag == ATTACK) {
			attack.BitBlt(pDC->m_hDC, 0, 0);
		}
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


UINT CCustomThread::ThreadInitial(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;

	pView->m_bClickable = false;
	Sleep(pView->m_nInit);
	pView->m_bClickable = true;

	CWinThread *p2 = NULL;
	p2 = AfxBeginThread(ThreadClickDelay, pView);
	if (p2 == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(p2);

	return 0;
}


void CCustomThread::StartThread()
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();

	CWinThread *pClick = NULL;
	CWinThread *pAbsolute = NULL;

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

