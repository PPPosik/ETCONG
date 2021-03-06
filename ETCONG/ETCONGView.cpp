
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
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
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
	, m_bStageStart(false)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	m_player = CPlayer();
	m_player.ImageInit();
	m_aEnemy = CEnemy();
	m_aEnemy.ImageInit();
	m_pBackgroundPos = CPoint(-800,-340);
	m_nTimerFlag = AFTER_MOVE;
	m_sound = CSoundPlayer();
	m_nTime = 400;
	m_nClick = 200;
	m_nDelay = 200;
	m_nInit = 200;
	m_bClickable = false;
	m_bError = false;
	m_ImgBackground.Load(_T("res\\background.png"));
	m_nBackgroundWidth = m_ImgBackground.GetWidth();
	m_nBackgroundHeight = m_ImgBackground.GetHeight();

	m_customThread = CCustomThread();
	m_animation = CMyAnimation();
	m_animation.InitAnimation();

	// 수정 필요
	m_player.setPos(1280 / 2 - 50, 720 / 2 - 50);
	m_animation.setPos(1280 / 2 - 50, 720 / 2 - 100);

	m_display = CGameGraphics();
	m_display.Init();
	
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
	if (!m_bStageStart) {
		m_bStageStart = true;
		m_sound.stage1Play();
		m_customThread.StartThread();
	}
	CETCONGDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	m_display.DisplayThread();
	//drawBackground();
	
	
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
	int widthBias = 100;
	int heightBias = 100;
	int playerPosX = m_player.getPos().x;
	int playerPosY = m_player.getPos().y;
	int enemyPosX = m_aEnemy.m_pPos.x;
	int enemyPosY = m_aEnemy.m_pPos.y;

	if (m_bClickable) {
		if (nChar == VK_LEFT) {
			m_display.LeftPlayer();
		}
		else if (nChar == VK_RIGHT) {
			m_display.RightPlayer();
		}

		if (m_nTimerFlag == MOVE) {
			switch (nChar) {
			case VK_LEFT:
				if (m_pBackgroundPos.x < -200) {
					x = x + widthBias;
					enemyPosX = enemyPosX + widthBias;
				}
				m_bClickable = false;
				m_nTimerFlag = AFTER_MOVE;
				m_animation.StartThread();
				break;
			case VK_RIGHT:
				if (m_pBackgroundPos.x > -2700) {
					x = x - widthBias;
					enemyPosX = enemyPosX - widthBias;
				}
				m_bClickable = false;
				m_nTimerFlag = AFTER_MOVE;
				m_animation.StartThread();
				break;
			case VK_UP:
				if (m_pBackgroundPos.y <= 40) {
					y = y + heightBias;
					enemyPosY = enemyPosY + heightBias;
				}
				m_bClickable = false;
				m_nTimerFlag = AFTER_MOVE;
				m_animation.StartThread();
				break;
			case VK_DOWN:
				if (m_pBackgroundPos.y > -1340) {
					y = y - heightBias;
					enemyPosY = enemyPosY - heightBias;
				}
				m_bClickable = false;
				m_nTimerFlag = AFTER_MOVE;
				m_animation.StartThread();
				break;
			case VK_ADD:
			{	//시연용
				CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
				CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
				CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
				CView *pView = (CView*)pChild->GetActiveView();
				pView = pApp->SwitchView(1003, 2003);
			}
			default:
				break;
			}
			m_pBackgroundPos.x = x;
			m_pBackgroundPos.y = y;
			m_aEnemy.m_pPos.x = enemyPosX;
			m_aEnemy.m_pPos.y = enemyPosY;
			
		}
		else if (m_nTimerFlag == ATTACK) {
			m_newone.PlayerBulletThread(nChar);
			m_nTimerFlag = AFTER_ATTACK;
			m_bClickable = false;
		}
	}
	ReleaseDC(pDC);
	Invalidate(TRUE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CETCONGView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_sound.stop();
	m_customThread.StopThread();
	m_display.pDisplay = NULL;
	
}


void CETCONGView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
}


BOOL CETCONGView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;
}

