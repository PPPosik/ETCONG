
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

#define MOVE 100
#define ATTACK 101
#define AFTER_MOVE 102
#define AFTER_ATTACK 103

// CETCONGView

IMPLEMENT_DYNCREATE(CETCONGView, CView)

BEGIN_MESSAGE_MAP(CETCONGView, CView)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CETCONGView 생성/소멸

CETCONGView::CETCONGView()
	: m_pBackgroundPos(0)
	, m_nTimerFlag(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_player = CPlayer();
	m_pBackgroundPos = CPoint(0, 0);
	m_nTimerFlag = AFTER_ATTACK;
	m_sound = CSoundPlayer();

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
	SetTimer(0, 400, NULL);
	drawBackground();
	m_player.drawMove(pDC);

	m_sound.stage1Play();
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
			;
		}
		m_pBackgroundPos.x = x;
		m_pBackgroundPos.y = y;

		drawBackground();
		m_player.drawMove(pDC);

		m_nTimerFlag = AFTER_MOVE;
	}
	else if (m_nTimerFlag == ATTACK) {
		// 공격 키 아닌 키 누르면 disadvantage
		m_player.drawAttack(pDC);
		m_nTimerFlag = AFTER_ATTACK;
	}
	else {
		// disadvantage
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_nTimerFlag == AFTER_ATTACK)
		m_nTimerFlag = MOVE;
	else if (m_nTimerFlag == AFTER_MOVE)
		m_nTimerFlag = ATTACK;

	CView::OnTimer(nIDEvent);
}
