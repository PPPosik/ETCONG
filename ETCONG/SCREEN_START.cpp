// SCREEN_START.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ETCONG.h"
#include "SCREEN_START.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"
// SCREEN_START

IMPLEMENT_DYNCREATE(SCREEN_START, CFormView)

SCREEN_START::SCREEN_START()
	: CFormView(IDD_SCREEN_START)
{
	m_ImgBackground.Load(_T("res\\ETCONG_Start.png"));
}

SCREEN_START::~SCREEN_START()
{
}

void SCREEN_START::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_btnStart);

}

BEGIN_MESSAGE_MAP(SCREEN_START, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_START, &SCREEN_START::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// SCREEN_START 진단입니다.

#ifdef _DEBUG
void SCREEN_START::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SCREEN_START::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SCREEN_START 메시지 처리기입니다.

void SCREEN_START::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	CView *pView = (CView*)pChild->GetActiveView();
	pView = pApp->SwitchView(1000, 0);
}


void SCREEN_START::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	AfxGetApp()->GetMainWnd()->SetWindowTextW(_T("Enter The Crypt Of Necro Gungeon"));
	m_btnStart.LoadBitmaps(IDB_BITMAP_START, IDB_BITMAP_START, IDB_BITMAP_START, IDB_BITMAP_START);
	m_btnStart.SizeToContent();
}


void SCREEN_START::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	pDC = GetDC();
	m_ImgBackground.BitBlt(pDC->m_hDC, 0, 0);
}