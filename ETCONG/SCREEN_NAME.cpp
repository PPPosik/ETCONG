// SCREEN_NAME.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ETCONG.h"
#include "SCREEN_NAME.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"

// SCREEN_NAME

IMPLEMENT_DYNCREATE(SCREEN_NAME, CFormView)

SCREEN_NAME::SCREEN_NAME()
	: CFormView(IDD_SCREEN_NAME)
	, m_strName(_T(""))
{
	m_ImageBackground.Load(_T("res\\ETCONG_Name.jpg"));
}

SCREEN_NAME::~SCREEN_NAME()
{
}

void SCREEN_NAME::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_BUTTON_START_GAME, m_strName);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_BUTTON_START_GAME, m_btnStarts);
}

BEGIN_MESSAGE_MAP(SCREEN_NAME, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_START_GAME, &SCREEN_NAME::OnBnClickedButtonStartGame)
END_MESSAGE_MAP()


// SCREEN_NAME 진단입니다.

#ifdef _DEBUG
void SCREEN_NAME::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SCREEN_NAME::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SCREEN_NAME 메시지 처리기입니다.

void SCREEN_NAME::OnBnClickedButtonStartGame()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	if (m_strName.IsEmpty()) {
		AfxMessageBox(_T("없습니다 당신의 이름!"));
		m_strName = _T("그치만..이렇게라도 하지 않으면...");
		UpdateData(FALSE);
		return;
	}

	m_strName.Empty();
	UpdateData(FALSE);

	CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	CView *pView = (CView*)pChild->GetActiveView();
	pView = pApp->SwitchView(1001, 2001);
}




void SCREEN_NAME::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_btnStarts.AutoLoad(IDC_BUTTON_START_GAME, this);
	m_btnStarts.LoadBitmaps(IDB_BITMAP_OK, IDB_BITMAP_OK, IDB_BITMAP_OK, IDB_BITMAP_OK);
	m_btnStarts.SizeToContent();
	pDC = GetDC();

	m_ImageBackground.StretchBlt(pDC->m_hDC, 0, 0, 1270, 685);
}