
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
	m_customThread = CCustomThread();

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

	m_sound.stage1Play();
	m_customThread.StartThread();
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

	m_ImgBackground.BitBlt(pDC->m_hDC, m_pBackgroundPos.x, m_pBackgroundPos.y);
	m_player.drawMove(pDC);

	ReleaseDC(pDC);
}


void CETCONGView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	m_sound.stop();
}


