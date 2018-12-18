// SCREEN_START.cpp : ���� �����Դϴ�.
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


// SCREEN_START �����Դϴ�.

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


// SCREEN_START �޽��� ó�����Դϴ�.

void SCREEN_START::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	CView *pView = (CView*)pChild->GetActiveView();
	pView = pApp->SwitchView(1000, 0);
}


void SCREEN_START::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	AfxGetApp()->GetMainWnd()->SetWindowTextW(_T("Enter The Crypt Of Necro Gungeon"));
	m_btnStart.LoadBitmaps(IDB_BITMAP_START, IDB_BITMAP_START, IDB_BITMAP_START, IDB_BITMAP_START);
	m_btnStart.SizeToContent();
}


void SCREEN_START::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	pDC = GetDC();
	m_ImgBackground.BitBlt(pDC->m_hDC, 0, 0);
}