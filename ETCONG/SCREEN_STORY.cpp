// SCREEN_STORY.cpp : ���� �����Դϴ�.
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


// SCREEN_STORY �����Դϴ�.

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


// SCREEN_STORY �޽��� ó�����Դϴ�.


void SCREEN_STORY::OnBnClickedButtonSkip()
{
	CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->GetMainWnd();
	CMDIChildWnd *pChild = (CMDIChildWnd*)pFrame->GetActiveFrame();
	CView *pView = (CView*)pChild->GetActiveView();
	pView = pApp->SwitchView(1002);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SCREEN_STORY::OnEnChangeEditStory()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CFormView::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}

void SCREEN_STORY::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

}

void SCREEN_STORY::drawBG()
{
	if (m_nStoryScene > 3) {
		AfxMessageBox(_T("���丮 ���̶��!"));
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
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	drawBG();

}


void SCREEN_STORY::OnBnClickedButtonNext()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	Invalidate();
}
