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
	, m_strStory(_T(""))
//	, m_pBackgroundPos(0)
//	, m_nBackgroundWidth(0)
//	, m_nBackgroundHeight(0)
, m_nStoryScene(0)
, inited(false)
{
//	m_ImgBackground.Load(_T("res\\bgtest.bmp"));
//	m_nBackgroundWidth = m_ImgBackground.GetWidth();
//	m_nBackgroundHeight = m_ImgBackground.GetHeight();
//	m_bmpBackground.LoadBitmapW(IDB_BITMAP3);
	storySet[0].Load(_T("res\\title.bmp"));
	storySet[1].Load(_T("res\\bgtest.bmp"));
	storySet[2].Load(_T("res\\BGImage.bmp"));
	storySet[3].Load(_T("res\\title.bmp"));
}

SCREEN_STORY::~SCREEN_STORY()
{
}

void SCREEN_STORY::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STORY, m_strStory);
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


	//CDC* pDC = GetDC();
	//m_ImgBackground = storySet[m_nStoryScene++];
	//m_ImgBackground.BitBlt(pDC->m_hDC, 0, 0);

	//m_btnNext.LoadBitmaps(IDB_BITMAP4, IDB_BITMAP4, IDB_BITMAP4, IDB_BITMAP4);
	//m_btnNext.SizeToContent();
	//m_btnSkip.LoadBitmaps(IDB_BITMAP5, IDB_BITMAP5, IDB_BITMAP5, IDB_BITMAP5);
	//m_btnSkip.SizeToContent();
}


void SCREEN_STORY::OnDraw(CDC* pDC)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	drawBG();

	//printf("init call\n");
	//CStdioFile story_text;

	//vector<CString> strStory;
	//
	//// CFile::modeRead  ->  파일을 읽기 모드로 연다. ( 파일이 없다면 실패한다. )
	//// CFile::typeText  ->  파일의 속성을 텍스트 형식으로 지정한다. ( 생략 가능)
	//
	//if (story_text.Open(_T("res\\ETCONG_STORY.txt"), CFile::modeRead | CFile::typeText)) {

	//	// 성공적으로 파일이 열렸으면 원하는 작업을 한다.

	//	CString display_str, str;
	//	printf("func call\n");
	//	// 파일에 더이상 텍스트 내용이 없을때까지 한줄씩 반복해서 읽어서 str 변수에 저장한다.
	//	while (story_text.ReadString(str)) {

	//		// 읽어들인 한줄의 텍스트를 display_str 변수에 추가한다.
	//		m_strStory += str;

	//		// 멀티라인 속성을 가진 에디트 컨트롤은 줄의 끝에 "\r\n" 가 있어야지 줄바꿈을 해준다.
	//		// ReadString 함수가 한줄의 텍스트를 읽을때 해당줄의 끝에있는 "\n" 은 읽어서 버리기
	//		// 때문에 텍스트의 한줄끝에 "\n" 이 있다고 할지라도 반드시 "\n" 을 붙여야 합니다.
	//		m_strStory += "\r\n";
	//	}

	//	// 반복문을 빠져나오면 display_str에 텍스트 파일의 내용이 모두 저장되어 있습니다.
	//	SetDlgItemText(IDC_EDIT_STORY, display_str);

	//	story_text.Close();
	//}
	//else {
	//	printf("no call\n");
	//	AfxMessageBox(_T("ERROR"));
	//}
}


void SCREEN_STORY::OnBnClickedButtonNext()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	drawBG();
}




//BOOL SCREEN_STORY::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//	if (m_bmpBackground.m_hObject)
//		return true;
//
//	CRect rect;
//	GetClientRect(&rect);
//
//	CDC dc;
//	dc.CreateCompatibleDC(pDC);
//	CBitmap* pOldBitmap = dc.SelectObject(&m_bmpBackground);
//
//	BITMAP bmap;
//	m_bmpBackground.GetBitmap(&bmap);
//	pDC->StretchBlt(0, 0, 1280, 720, &dc, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);
//	dc.SelectObject(pOldBitmap);
//
//	return true;
//}
