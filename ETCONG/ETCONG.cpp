
// ETCONG.cpp : 응용 프로그램에 대한 클래스 동작을 정의합니다.
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
	// 표준 파일을 기초로 하는 문서 명령입니다.
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CETCONGApp 생성

CETCONGApp::CETCONGApp()
	: m_pOldView(NULL)
	, m_pNewView(NULL)
	, m_pStartScreen(NULL)
	, m_pNameScreen(NULL)
	, m_nCurrentView(VIEW_START)
{
	// TODO: 아래 응용 프로그램 ID 문자열을 고유 ID 문자열로 바꾸십시오(권장).
	// 문자열에 대한 서식: CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ETCONG.AppID.NoVersion"));

	// TODO: 여기에 생성 코드를 추가합니다.
	// InitInstance에 모든 중요한 초기화 작업을 배치합니다.
}

// 유일한 CETCONGApp 개체입니다.

CETCONGApp theApp;


// CETCONGApp 초기화

BOOL CETCONGApp::InitInstance()
{
	CWinApp::InitInstance();


	EnableTaskbarInteraction(FALSE);

	// RichEdit 컨트롤을 사용하려면  AfxInitRichEdit2()가 있어야 합니다.	
	// AfxInitRichEdit2();

	// 표준 초기화
	// 이들 기능을 사용하지 않고 최종 실행 파일의 크기를 줄이려면
	// 아래에서 필요 없는 특정 초기화
	// 루틴을 제거해야 합니다.
	// 해당 설정이 저장된 레지스트리 키를 변경하십시오.
	// TODO: 이 문자열을 회사 또는 조직의 이름과 같은
	// 적절한 내용으로 수정해야 합니다.
	SetRegistryKey(_T("로컬 응용 프로그램 마법사에서 생성된 응용 프로그램"));
	LoadStdProfileSettings(4);  // MRU를 포함하여 표준 INI 파일 옵션을 로드합니다.


	// 응용 프로그램의 문서 템플릿을 등록합니다.  문서 템플릿은
	//  문서, 프레임 창 및 뷰 사이의 연결 역할을 합니다.
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CETCONGDoc),
		RUNTIME_CLASS(CMainFrame),       // 주 SDI 프레임 창입니다.
		RUNTIME_CLASS(SCREEN_START));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// 표준 셸 명령, DDE, 파일 열기에 대한 명령줄을 구문 분석합니다.
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// 명령줄에 지정된 명령을 디스패치합니다.
	// 응용 프로그램이 /RegServer, /Register, /Unregserver 또는 /Unregister로 시작된 경우 FALSE를 반환합니다.
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
	// 창 하나만 초기화되었으므로 이를 표시하고 업데이트합니다.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// CETCONGApp 메시지 처리기


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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

// 대화 상자를 실행하기 위한 응용 프로그램 명령입니다.
void CETCONGApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CETCONGApp 메시지 처리기





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
		AfxMessageBox(_T("미구현"));
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
//	printf("스뤠드 : %d\n", pView->GetDlgCtrlID());
	
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
