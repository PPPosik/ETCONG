// SCREEN_STORY.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ETCONG.h"
#include "SCREEN_STORY.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"

// SCREEN_STORY

IMPLEMENT_DYNCREATE(SCREEN_STORY, CFormView)

SCREEN_STORY::SCREEN_STORY()
	: CFormView(IDD_SCREEN_STORY)
	, m_nStoryScene(0)
	, inited(false)
	, nStoryType(0)
{
	//	m_ImgBackground.Load(_T("res\\bgtest.bmp"));
	//	m_nBackgroundWidth = m_ImgBackground.GetWidth();
	//	m_nBackgroundHeight = m_ImgBackground.GetHeight();
	//	m_bmpBackground.LoadBitmapW(IDB_BITMAP3);
	storySet[0].Load(_T("res\\sceen1.png"));
	storySet[1].Load(_T("res\\sceen2.png"));
	storySet[2].Load(_T("res\\sceen3.png"));
	storySet[3].Load(_T("res\\sceen4.png"));
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
	ON_EN_CHANGE(IDC_EDIT_STORY, &SCREEN_STORY::OnEnChangeEditStory)
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


void SCREEN_STORY::OnEnChangeEditStory()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CFormView::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

}

void SCREEN_STORY::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

}

void SCREEN_STORY::drawBG()
{
	if (m_nStoryScene > 3) {
		AfxMessageBox(_T("스토리 끝이라고!"));
		return;
	}

	ReleaseDC(GetDC());
	CDC* pDC = GetDC();
	m_ImgBackground = storySet[m_nStoryScene++];
	m_ImgBackground.BitBlt(pDC->m_hDC, 0, 0);

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
