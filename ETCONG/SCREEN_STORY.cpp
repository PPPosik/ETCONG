// SCREEN_STORY.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ETCONG.h"
#include "SCREEN_STORY.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"


#define STORY_START 2001
#define STORY_CLEAR 2002
#define STORY_DIE_EINS 2003
#define STORY_DIE_ZWEI 2004
// SCREEN_STORY

IMPLEMENT_DYNCREATE(SCREEN_STORY, CFormView)

SCREEN_STORY::SCREEN_STORY()
	: CFormView(IDD_SCREEN_STORY)
	, m_nStoryScene(0)
	, inited(false)
	, nStoryType(STORY_START)
{
	storySet[0].Load(_T("res\\sceen1.png"));
	storySet[1].Load(_T("res\\sceen2.png"));
	storySet[2].Load(_T("res\\sceen3.png"));
	storySet[3].Load(_T("res\\sceen4.png"));

	storyEnd[0].Load(_T("res\\ETCONG_End1.jpg"));
	storyEnd[1].Load(_T("res\\ETCONG_End2.jpg"));
	storyEnd[2].Load(_T("res\\ETCONG_End3.jpg"));
	storyEnd[3].Load(_T("res\\ETCONG_End3-1.jpg"));
	storyEnd[4].Load(_T("res\\ETCONG_End4.jpg"));
	storyEnd[5].Load(_T("res\\ETCONG_End4-1.jpg"));
	storyEnd[6].Load(_T("res\\ETCONG_End5.jpg"));
	storyEnd[7].Load(_T("res\\ETCONG_End2.jpg"));

	storyDiedEins[0].Load(_T("res\\ETCONG_Die1.jpg"));
	storyDiedEins[1].Load(_T("res\\ETCONG_End2.jpg"));

	storyDiedZwei[0].Load(_T("res\\ETCONG_Die2.jpg"));
	storyDiedZwei[1].Load(_T("res\\ETCONG_End2.jpg"));
}

SCREEN_STORY::~SCREEN_STORY()
{
}

void SCREEN_STORY::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_NEXT, m_btnNext);
	DDX_Control(pDX, IDC_BUTTON_SKIP, m_btnSkip);
}

BEGIN_MESSAGE_MAP(SCREEN_STORY, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SKIP, &SCREEN_STORY::OnBnClickedButtonSkip)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &SCREEN_STORY::OnBnClickedButtonNext)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// SCREEN_STORY 진단입니다.

#ifdef _DEBUG
void SCREEN_STORY::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SCREEN_STORY::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SCREEN_STORY 메시지 처리기입니다.


void SCREEN_STORY::OnBnClickedButtonSkip()
{
	CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	CView *pView = (CView*)pChild->GetActiveView();
	pView = pApp->SwitchView(1002);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void SCREEN_STORY::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

}

void SCREEN_STORY::drawBG()
{	
	int nStorySize;
	CImage *pStory = NULL;

	switch (nStoryType) {
	
	case STORY_START:
		nStorySize = 4;
		pStory = storySet;
		break;

	case STORY_CLEAR:
		nStorySize = 8;
		pStory = storyEnd;
		break;

	case STORY_DIE_EINS:
		nStorySize = 2;
		pStory = storyDiedEins;
		break;

	case STORY_DIE_ZWEI:
		nStorySize = 2;
		pStory = storyDiedZwei;
		break;
	
	default:
		AfxMessageBox(_T("Undefined"));
		break;
	}
	if (m_nStoryScene >= nStorySize) {
		if (nStoryType == STORY_START) {
			CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
			CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
			CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
			CView *pView = (CView*)pChild->GetActiveView();
			pView = pApp->SwitchView(1002);
			return;
		}
		else {
			CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
			CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
			CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
			CView *pView = (CView*)pChild->GetActiveView();
			pView = pApp->SwitchView(1003);
			return;
		}
	}

	ReleaseDC(GetDC());
	CDC* pDC = GetDC();
	m_ImgBackground = pStory[m_nStoryScene++];
	m_ImgBackground.BitBlt(pDC->m_hDC, 0, -20);

	if (!inited) {
		m_btnNext.AutoLoad(IDC_BUTTON_NEXT, this);
		m_btnSkip.AutoLoad(IDC_BUTTON_SKIP, this);
		inited = true;
	}
	m_btnNext.LoadBitmaps(IDB_BITMAP4, IDB_BITMAP4, IDB_BITMAP4, IDB_BITMAP4);
	m_btnNext.SizeToContent();
	m_btnSkip.LoadBitmaps(IDB_BITMAP5, IDB_BITMAP5, IDB_BITMAP5, IDB_BITMAP5);
	m_btnSkip.SizeToContent();

} 


void SCREEN_STORY::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	drawBG();

}


void SCREEN_STORY::OnBnClickedButtonNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate();
}


void SCREEN_STORY::StoryChanged(int Scene)
{
	m_nStoryScene = 0;
	nStoryType = Scene;
}
