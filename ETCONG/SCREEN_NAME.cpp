// SCREEN_NAME.cpp : ���� �����Դϴ�.
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
	m_ImageBackground.Load(_T("res\\title.bmp"));
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
	ON_EN_CHANGE(IDC_EDIT1, &SCREEN_NAME::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON_GOBACK, &SCREEN_NAME::OnBnClickedButtonGoback)
	ON_BN_CLICKED(IDC_BUTTON_START_GAME, &SCREEN_NAME::OnBnClickedButtonStartGame)
END_MESSAGE_MAP()


// SCREEN_NAME �����Դϴ�.

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


// SCREEN_NAME �޽��� ó�����Դϴ�.


void SCREEN_NAME::OnEnChangeEdit1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SCREEN_NAME::OnBnClickedButtonGoback()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
	//CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	//CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	//CView *pView = (CView*)pChild->GetActiveView();
	//pView = pApp->SwitchView(1003);
}


void SCREEN_NAME::OnBnClickedButtonStartGame()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//UpdateData(TRUE);
	//if (m_strName.IsEmpty()) {
	//	AfxMessageBox(_T("�����ϴ� ����� �̸�!"));
	//	m_strName = _T("��ġ��..�̷��Զ� ���� ������...");
	//	UpdateData(FALSE);
	//	return;
	//}

	m_strName.Empty();
	UpdateData(FALSE);

	CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	CView *pView = (CView*)pChild->GetActiveView();
	pView = pApp->SwitchView(1001);
}


CString SCREEN_NAME::GetPlayerName()
{
	return m_strName;
}


void SCREEN_NAME::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_btnStarts.AutoLoad(IDC_BUTTON_START_GAME, this);
	m_btnStarts.LoadBitmaps(IDB_BITMAP1, IDB_BITMAP2, IDB_BITMAP1, IDB_BITMAP2);
	m_btnStarts.SizeToContent();

	pDC = GetDC();

	m_ImageBackground.BitBlt(pDC->m_hDC, 0, 0);
}
