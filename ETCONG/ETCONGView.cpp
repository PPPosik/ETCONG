
// ETCONGView.cpp : CETCONGView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ETCONG.h"
#endif

#include "ETCONGDoc.h"
#include "ETCONGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define RYTHME_TIMER 104
#define CLICK_TIMER 105
#define DELAY_TIMER 106
#define INIT_TIMER 107

#define MOVE 100
#define ATTACK 101
#define AFTER_MOVE 102
#define AFTER_ATTACK 103

// CETCONGView

IMPLEMENT_DYNCREATE(CETCONGView, CView)

BEGIN_MESSAGE_MAP(CETCONGView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CETCONGView 생성/소멸

CETCONGView::CETCONGView()
	: m_pBackgroundPos(0)
	, m_nTimerFlag(0)
	, m_nTime(0)
	, m_nClick(0)
	, m_bClickable(false)
	, m_nDelay(0)
	, m_nInit(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_player = CPlayer();
	m_player.ImageInit();
	m_pBackgroundPos = CPoint(0, 0);
	m_nTimerFlag = AFTER_MOVE;
	m_sound = CSoundPlayer();
	m_nTime = 400;
	m_nClick = 200;
	m_nDelay = 200;
	m_nInit = 200;
	m_bClickable = false;
	m_ImgBackground.Load(_T("res\\background.png"));

	// 수정 필요
	m_player.setPos(1280 / 2 - 50, 720 / 2 - 70);
}

CETCONGView::~CETCONGView()
{
}

BOOL CETCONGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CETCONGView 그리기

void CETCONGView::OnDraw(CDC* pDC)
{
	CETCONGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	drawBackground();

	/*CImage test;
	test.Load(_T("res\\player.png"));
	test.BitBlt(pDC->m_hDC, 0, 0);
	test.BitBlt(pDC->m_hDC, 50, 50);
	test.BitBlt(pDC->m_hDC, 100, 100);*/

	//StartTimer();
	m_sound.stage1Play();
	StartThread();
}


// CETCONGView 진단

#ifdef _DEBUG
void CETCONGView::AssertValid() const
{
	CView::AssertValid();
}

void CETCONGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CETCONGDoc* CETCONGView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CETCONGDoc)));
	return (CETCONGDoc*)m_pDocument;
}
#endif //_DEBUG


// CETCONGView 메시지 처리기


void CETCONGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CDC* pDC = GetDC();
	int x = m_pBackgroundPos.x;
	int y = m_pBackgroundPos.y;
	int widthBias = m_player.getWidth();
	int heightBias = m_player.getHeight();

	if (m_bClickable) {
		if (m_nTimerFlag == MOVE) {
			switch (nChar) {
			case VK_LEFT:
				x = x + widthBias;
				break;
			case VK_RIGHT:
				x = x - widthBias;
				break;
			case VK_UP:
				y = y + heightBias;
				break;
			case VK_DOWN:
				y = y - heightBias;
				break;
			default:
				// disadvantage
				m_player.drawError(pDC);
				;
			}
			m_pBackgroundPos.x = x;
			m_pBackgroundPos.y = y;

			drawBackground();
			//m_player.drawMove(pDC);

			////////////////////////
			/*CImage move;
			HRESULT hResult = move.Load(_T("res\\player.png"));
			if (FAILED(hResult)) {
				AfxMessageBox(_T("Img ERROR"));
				return;
			}
			move.BitBlt(pDC->m_hDC, 0, 0);*/
			////////////////////////

			m_nTimerFlag = AFTER_MOVE;
		}
		else if (m_nTimerFlag == ATTACK) {
			// 공격 키 아닌 키 누르면 disadvantage
			m_player.drawAttack(pDC);
			m_nTimerFlag = AFTER_ATTACK;
		}
		else {
			// disadvantage
			m_player.drawError(pDC);
		}
	}
	else {
		m_player.drawError(pDC);
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CETCONGView::drawBackground()
{
	CDC* pDC = GetDC();

	/*backgroundImg.Destroy();
	HRESULT hResult = backgroundImg.Load(_T("res\\background.png"));*/

	/*if (FAILED(hResult)) {
		AfxMessageBox(_T("Img ERROR"));
		return;
	}*/

	m_ImgBackground.BitBlt(pDC->m_hDC, m_pBackgroundPos.x, m_pBackgroundPos.y);
	m_player.drawMove(pDC);

	ReleaseDC(pDC);
}


void CETCONGView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nIDEvent == RYTHME_TIMER) {
		if (m_nTimerFlag == AFTER_ATTACK || m_nTimerFlag == ATTACK)
			m_nTimerFlag = MOVE;
		else if (m_nTimerFlag == AFTER_MOVE || m_nTimerFlag == MOVE)
			m_nTimerFlag = ATTACK;

		CDC *pDC = GetDC();
		if (m_nTimerFlag == MOVE) {
			CImage move;
			HRESULT hResult = move.Load(_T("res\\player.png"));
			if (FAILED(hResult)) {
				AfxMessageBox(_T("Img ERROR"));
				return;
			}
			move.BitBlt(pDC->m_hDC, 0, 0);
		}
		else if (m_nTimerFlag == ATTACK) {
			CImage attack;
			HRESULT hResult = attack.Load(_T("res\\attack.png"));
			if (FAILED(hResult)) {
				AfxMessageBox(_T("Img ERROR"));
				return;
			}
			attack.BitBlt(pDC->m_hDC, 0, 0);
		}
	}
	else if (nIDEvent == CLICK_TIMER) {
		SetTimer(DELAY_TIMER, m_nDelay, NULL);
		m_bClickable = false;
		KillTimer(CLICK_TIMER);
	}
	else if (nIDEvent == DELAY_TIMER) {
		SetTimer(CLICK_TIMER, m_nClick, NULL);
		m_bClickable = true;
		KillTimer(DELAY_TIMER);
	}
	else if (nIDEvent == INIT_TIMER) {
		SetTimer(CLICK_TIMER, m_nClick, NULL);
		m_bClickable = true;
		KillTimer(INIT_TIMER);
	}

	CView::OnTimer(nIDEvent);
}


void CETCONGView::StartTimer()
{
	// SetTimer(RYTHME_TIMER, m_nTime, NULL);
	SetTimer(INIT_TIMER, m_nInit, NULL);
}


void CETCONGView::EndTimer()
{
	KillTimer(RYTHME_TIMER);
	KillTimer(CLICK_TIMER);
	KillTimer(DELAY_TIMER);
}


void CETCONGView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_sound.stop();
	EndTimer();
}


UINT CETCONGView::ThreadAbsolute(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;

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
		
		CDC *pDC = pView->GetDC();
		if (pView->m_nTimerFlag == MOVE) {
			move.BitBlt(pDC->m_hDC, 0, 0);
		}
		else if (pView->m_nTimerFlag == ATTACK) {
			attack.BitBlt(pDC->m_hDC, 0, 0);
		}
	}
	return 0;
}


UINT CETCONGView::ThreadClickDelay(LPVOID _mothod)
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


UINT CETCONGView::ThreadInitial(LPVOID _mothod)
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


void CETCONGView::StartThread()
{
	CWinThread *p1 = NULL;
	CWinThread *p4 = NULL;

	p4 = AfxBeginThread(ThreadClickDelay, this);
	p1 = AfxBeginThread(ThreadAbsolute, this);

	if (p1 == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(p1);

	/*if (p4 == NULL) {
		AfxMessageBox(L"Error");
	}*/
	CloseHandle(p4);
}

