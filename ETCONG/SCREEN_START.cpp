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
	pView = pApp->SwitchView(1000);
}


void SCREEN_START::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//m_bmpButton.CreateBitmap(50, 20, 1, 256, NULL);

	//m_bmpButton.LoadBitmap(_T("res\\Button3.png"));
	//CButton* pButton = (CButton*)GetDlgItem(IDC_BUTTON_START);
	//pButton->ModifyStyle(0, BS_BITMAP);
	//pButton->SetBitmap(m_bmpButton);
	//m_btnStart.SetBitmap(HBITMAP(m_bmpButton));
	//HICON hBmp = (HICON)LoadImage(_T("res\\Button3.png"), MAKEINTRESOURCE(IDC_BUTTON_START), IMAGE_ICON, 4, 33, LR_DEFAULTCOLOR);
	//	m_btnStart.SetIcon(hBmp);
	//m_bmpButton.LoadBitmap(_T("res\\Button3.png"));
	//m_btnStart.ModifyStyle(0, BS_BITMAP);
	//m_btnStart.SetBitmap(HBITMAP(m_bmpButton));
	//CButton* pBtn = (CButton*)GetDlgItem(IDC_BUTTON_START);
	//pBtn->ModifyStyle(0, BS_ICON);
	//HICON hIcn = (HICON)LoadImageW(
	//	AfxGetApp()->m_hInstance,
	//	_T("res\\Button3.png"),
	//	IMAGE_ICON,
	//	63, 66, // use actual size
	//	LR_DEFAULTCOLOR
	//);
	//pBtn->SetIcon(hIcn);
	//m_bmpButton.LoadBitmapW(IDB_BITMAP1);
	//m_btnStart.SetBitmap(m_bmpButton);
	//HBITMAP hBitImg = NULL;
	//LPCTSTR strImgName = _T("res\\button.bmp");
	//strImgName.Format("P%d_OFF.bmp", m_btnStart);
	//hBitImg = _LoadBitMapFromFile(strImgName);
	//((CButton*)GetDlgItem(IDC_BUTTON_START))->SetBitmap(hBitImg);
	//CBitmap hBitmap;
	//hBitmap.LoadBitmapW(IDB_BITMAP2);
	//m_btnStart.Create(_T("Test"), WS_CHILD | WS_VISIBLE | BS_BITMAP, rect, this, NULL);
	//m_btnStart.SetBitmap(hBitmap);
	//m_btnStart.ShowWindow(SW_SHOW);
	m_btnStart.LoadBitmaps(IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP1, IDB_BITMAP2);
	m_btnStart.SizeToContent();
}
