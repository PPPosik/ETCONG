
// ETCONGView.cpp : CETCONGView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CETCONGView ����/�Ҹ�

CETCONGView::CETCONGView()
	: m_pBackgroundPos(0)
	, m_nTimerFlag(0)
	, m_nTime(0)
	, m_nClick(0)
	, m_bClickable(false)
	, m_nDelay(0)
	, m_nInit(0)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	m_player = CPlayer();
	m_pBackgroundPos = CPoint(0, 0);
	m_nTimerFlag = AFTER_MOVE;
	m_sound = CSoundPlayer();
	m_nTime = 400;
	m_nClick = 200;
	m_nDelay = 200;
	m_nInit = 300;
	m_bClickable = false;

	// ���� �ʿ�
	m_player.setPos(1280 / 2 - 50, 720 / 2 - 70);
}

CETCONGView::~CETCONGView()
{
}

BOOL CETCONGView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CETCONGView �׸���

void CETCONGView::OnDraw(CDC* pDC)
{
	CETCONGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	drawBackground();
	m_player.drawMove(pDC);

	// StartTimer();
	StartThread();
	m_sound.stage1Play();
}


// CETCONGView ����

#ifdef _DEBUG
void CETCONGView::AssertValid() const
{
	CView::AssertValid();
}

void CETCONGView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CETCONGDoc* CETCONGView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CETCONGDoc)));
	return (CETCONGDoc*)m_pDocument;
}
#endif //_DEBUG


// CETCONGView �޽��� ó����


void CETCONGView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
			m_player.drawMove(pDC);

			////////////////////////
			CImage move;
			HRESULT hResult = move.Load(_T("res\\player.png"));
			if (FAILED(hResult)) {
				AfxMessageBox(_T("Img ERROR"));
				return;
			}
			move.BitBlt(pDC->m_hDC, 0, 0);
			////////////////////////

			m_nTimerFlag = AFTER_MOVE;
		}
		else if (m_nTimerFlag == ATTACK) {
			// ���� Ű �ƴ� Ű ������ disadvantage
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

	backgroundImg.Destroy();
	HRESULT hResult = backgroundImg.Load(_T("res\\background.png"));
	int width = backgroundImg.GetWidth();
	int height = backgroundImg.GetHeight();

	if (FAILED(hResult)) {
		AfxMessageBox(_T("Img ERROR"));
		return;
	}
	backgroundImg.BitBlt(pDC->m_hDC, m_pBackgroundPos.x, m_pBackgroundPos.y);
	m_player.drawMove(pDC);

	ReleaseDC(pDC);
}


void CETCONGView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_sound.stop();
	EndTimer();
}


UINT CETCONGView::ThreadFirst(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;

	while (1)
	{
		Sleep(pView->m_nTime);

		if (pView->m_nTimerFlag == AFTER_ATTACK || pView->m_nTimerFlag == ATTACK)
			pView->m_nTimerFlag = MOVE;
		else if (pView->m_nTimerFlag == AFTER_MOVE || pView->m_nTimerFlag == MOVE)
			pView->m_nTimerFlag = ATTACK;
		
		CDC *pDC = pView->GetDC();
		if (pView->m_nTimerFlag == MOVE) {
			CImage move;
			HRESULT hResult = move.Load(_T("res\\player.png"));
			if (FAILED(hResult)) {
				AfxMessageBox(_T("Img ERROR"));
				return -1;
			}
			move.BitBlt(pDC->m_hDC, 0, 0);
		}
		else if (pView->m_nTimerFlag == ATTACK) {
			CImage attack;
			HRESULT hResult = attack.Load(_T("res\\attack.png"));
			if (FAILED(hResult)) {
				AfxMessageBox(_T("Img ERROR"));
				return -1;
			}
			attack.BitBlt(pDC->m_hDC, 0, 0);
		}
	}
	return 0;
}


UINT CETCONGView::ThreadSecond(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;

	Sleep(pView->m_nDelay);
	pView->m_bClickable = false;

	CWinThread *p3 = NULL;
	p3 = AfxBeginThread(ThreadThird, pView);
	if (p3 == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(p3);

	return 0;
}


UINT CETCONGView::ThreadThird(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;

	Sleep(pView->m_nClick);
	pView->m_bClickable = true;

	CWinThread *p2 = NULL;
	p2 = AfxBeginThread(ThreadSecond, pView);
	if (p2 == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(p2);

	return 0;
}


UINT CETCONGView::ThreadFourth(LPVOID _mothod)
{
	CETCONGView *pView = (CETCONGView*)_mothod;

	Sleep(pView->m_nInit);
	pView->m_bClickable = true;

	CWinThread *p2 = NULL;
	p2 = AfxBeginThread(ThreadSecond, pView);
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

	p1 = AfxBeginThread(ThreadFirst, this);
	if (p1 == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(p1);

	p4 = AfxBeginThread(ThreadFourth, this);
	if (p4 == NULL) {
		AfxMessageBox(L"Error");
	}
	CloseHandle(p4);
}

