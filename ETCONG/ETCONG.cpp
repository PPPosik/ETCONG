
// ETCONG.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ETCONG.h"
#include "MainFrm.h"
#include "NewView.h"
#include "OldView.h"
#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include <afxpriv.h>
#include "SCREEN_NAME.h"
#include "SCREEN_START.h"
#include "SCREEN_STORY.h"
#include "SCREEN_GAME.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define VIEW_START 1000
#define VIEW_NAME 1001
#define VIEW_STORY 1002
#define VIEW_GAME 1003

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// CETCONGApp

BEGIN_MESSAGE_MAP(CETCONGApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CETCONGApp::OnAppAbout)
	// ǥ�� ������ ���ʷ� �ϴ� ���� ����Դϴ�.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CETCONGApp ����

CETCONGApp::CETCONGApp()
	: m_pOldView(NULL)
	, m_pNewView(NULL)
	, m_pStartScreen(NULL)
	, m_pNameScreen(NULL)
	, m_nCurrentView(VIEW_START)
{
	// TODO: �Ʒ� ���� ���α׷� ID ���ڿ��� ���� ID ���ڿ��� �ٲٽʽÿ�(����).
	// ���ڿ��� ���� ����: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ETCONG.AppID.NoVersion"));

	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}

// ������ CETCONGApp ��ü�Դϴ�.

CETCONGApp theApp;


// CETCONGApp �ʱ�ȭ

BOOL CETCONGApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	// ���� ���α׷��� ���� ���ø��� ����մϴ�.  ���� ���ø���
	//  ����, ������ â �� �� ������ ���� ������ �մϴ�.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CETCONGDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ������ â�Դϴ�.
		RUNTIME_CLASS(SCREEN_START));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ǥ�� �� ���, DDE, ���� ���⿡ ���� ������� ���� �м��մϴ�.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ����ٿ� ������ ����� ����ġ�մϴ�.
	// ���� ���α׷��� /RegServer, /Register, /Unregserver �Ǵ� /Unregister�� ���۵� ��� FALSE�� ��ȯ�մϴ�.
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	CView* pActiveView = ((CFrameWnd*)m_pMainWnd)->GetActiveView();
	m_pOldView = pActiveView;
	m_pNewView = (CView*) new NewView();
	m_pStartScreen = (CView*) new SCREEN_START();
	m_pNameScreen = (CView*) new SCREEN_NAME();
	m_pStoryScreen = (CView*) new SCREEN_STORY();
	m_pGameScreen = (CView*) new CETCONGView();
	CDocument* pCurrentDoc = ((CFrameWnd*)m_pMainWnd)->GetActiveDocument();

	// Initialize a CCreateContext to point to the active document.
	// With this context, the new view is added to the document
	// when the view is created in CView::OnCreate().
	CCreateContext newContext;
	newContext.m_pNewViewClass = NULL;
	newContext.m_pNewDocTemplate = NULL;
	newContext.m_pLastView = NULL;
	newContext.m_pCurrentFrame = NULL;
	newContext.m_pCurrentDoc = pCurrentDoc;

	// The ID of the initial active view is AFX_IDW_PANE_FIRST.
	// Incrementing this value by one for additional views works
	// in the standard document/view case but the technique cannot
	// be extended for the CSplitterWnd case.
	UINT viewID = AFX_IDW_PANE_FIRST + 1;
	CRect rect(0, 0, 0, 0); // Gets resized later.

	// Create the new view. In this example, the view persists for
	// the life of the application. The application automatically
	// deletes the view when the application is closed.
	m_pNewView->Create(NULL, (LPCTSTR)"AnyWindowName", WS_CHILD, rect, m_pMainWnd, IDD_NEWVIEW, &newContext);
	m_pStartScreen->Create(NULL, (LPCTSTR)"ETCONG Start", WS_CHILD, rect, m_pMainWnd, IDD_SCREEN_START, &newContext);
	m_pNameScreen->Create(NULL, (LPCTSTR)"ETCONG Name", WS_CHILD, rect, m_pMainWnd, IDD_SCREEN_NAME, &newContext);
	m_pStoryScreen->Create(NULL, (LPCTSTR)"ETCONG Story", WS_CHILD, rect, m_pMainWnd, IDD_SCREEN_STORY, &newContext);
	m_pGameScreen->Create(NULL, (LPCTSTR)"ETCONG Game", WS_CHILD, rect, m_pMainWnd, IDD_SCREEN_GAME, &newContext);
	// When a document template creates a view, the WM_INITIALUPDATE
	// message is sent automatically. However, this code must
	// explicitly send the message, as follows.
	//m_pNewView->SendMessage(WM_INITIALUPDATE, 0, 0);
	m_pStartScreen->SendMessage(WM_INITIALUPDATE, 0, 0);
	//m_pNameScreen->SendMessage(WM_INITIALUPDATE, 0, 0);
	//m_pStoryScreen->SendMessage(WM_INITIALUPDATE, 0, 0);
	//m_pGameScreen->SendMessage(WM_INITIALUPDATE, 0, 0);
	// â �ϳ��� �ʱ�ȭ�Ǿ����Ƿ� �̸� ǥ���ϰ� ������Ʈ�մϴ�.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// CETCONGApp �޽��� ó����


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// ��ȭ ���ڸ� �����ϱ� ���� ���� ���α׷� ����Դϴ�.
void CETCONGApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CETCONGApp �޽��� ó����





CView* CETCONGApp::SwitchView(int CurrentView)
{
	CView* pActiveView =
		((CFrameWnd*)m_pMainWnd)->GetActiveView();
	CView* pNewView = NULL;
	//if (pActiveView == m_pOldView)
	//	pNewView = m_pNewView;
	//else
	//	pNewView = m_pOldView;
	switch (CurrentView) {
	case VIEW_START:
		pNewView = m_pNameScreen;
		m_nCurrentView = VIEW_NAME;
		break;
	case VIEW_NAME:
		pNewView = m_pStoryScreen;
		m_nCurrentView = VIEW_STORY;
		break;
	case VIEW_STORY:
		pNewView = m_pGameScreen;
		m_nCurrentView = VIEW_GAME;
		m_pGameScreen->SendMessage(WM_INITIALUPDATE, 0, 0);
		break;
	case VIEW_GAME:
		if (m_bInited) {
			m_pOldView = pActiveView;
		}
		else {
			m_pOldView = pActiveView;
			pNewView = m_pStartScreen;
			m_nCurrentView = VIEW_START;
		}
		break;
	default:
		AfxMessageBox(_T("�̱���"));
		break;
	}
	// Exchange view window IDs so RecalcLayout() works.
#ifndef _WIN32
	UINT temp = ::GetWindowWord(pActiveView->m_hWnd, GWW_ID);
	::SetWindowWord(pActiveView->m_hWnd, GWW_ID, ::GetWindowWord(pNewView->m_hWnd, GWW_ID));
	::SetWindowWord(pNewView->m_hWnd, GWW_ID, temp);
#else
	UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
	::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID));

	::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
#endif
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();
//	printf("����� : %d\n", pView->GetDlgCtrlID());
	
	pActiveView->ShowWindow(SW_HIDE);
	pNewView->ShowWindow(SW_SHOW);
	((CFrameWnd*)m_pMainWnd)->SetActiveView(pNewView);
	((CFrameWnd*)m_pMainWnd)->RecalcLayout();
	pNewView->Invalidate();
	return pActiveView;

	//return nullptr;
}


int CETCONGApp::getCurrentView()
{
	return m_nCurrentView;
}



void CETCONGApp::setCurrentView(int value)
{
	m_nCurrentView = value;
}
