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
	, m_strStory(_T(""))
//	, m_pBackgroundPos(0)
//	, m_nBackgroundWidth(0)
//	, m_nBackgroundHeight(0)
{
	m_ImgBackground.Load(_T("res\\bgtest.bmp"));
//	m_nBackgroundWidth = m_ImgBackground.GetWidth();
//	m_nBackgroundHeight = m_ImgBackground.GetHeight();
//	m_bmpBackground.LoadBitmapW(IDB_BITMAP3);
}

SCREEN_STORY::~SCREEN_STORY()
{
}

void SCREEN_STORY::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STORY, m_strStory);
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


void SCREEN_STORY::OnDraw(CDC* pDC)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	drawBackground();

	//printf("init call\n");
	//CStdioFile story_text;

	//vector<CString> strStory;
	//
	//// CFile::modeRead  ->  ������ �б� ���� ����. ( ������ ���ٸ� �����Ѵ�. )
	//// CFile::typeText  ->  ������ �Ӽ��� �ؽ�Ʈ �������� �����Ѵ�. ( ���� ����)
	//
	//if (story_text.Open(_T("res\\ETCONG_STORY.txt"), CFile::modeRead | CFile::typeText)) {

	//	// ���������� ������ �������� ���ϴ� �۾��� �Ѵ�.

	//	CString display_str, str;
	//	printf("func call\n");
	//	// ���Ͽ� ���̻� �ؽ�Ʈ ������ ���������� ���پ� �ݺ��ؼ� �о str ������ �����Ѵ�.
	//	while (story_text.ReadString(str)) {

	//		// �о���� ������ �ؽ�Ʈ�� display_str ������ �߰��Ѵ�.
	//		m_strStory += str;

	//		// ��Ƽ���� �Ӽ��� ���� ����Ʈ ��Ʈ���� ���� ���� "\r\n" �� �־���� �ٹٲ��� ���ش�.
	//		// ReadString �Լ��� ������ �ؽ�Ʈ�� ������ �ش����� �����ִ� "\n" �� �о ������
	//		// ������ �ؽ�Ʈ�� ���ٳ��� "\n" �� �ִٰ� ������ �ݵ�� "\n" �� �ٿ��� �մϴ�.
	//		m_strStory += "\r\n";
	//	}

	//	// �ݺ����� ���������� display_str�� �ؽ�Ʈ ������ ������ ��� ����Ǿ� �ֽ��ϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//while()
}


void SCREEN_STORY::drawBackground()
{
	CDC* pDC = GetDC();

	m_ImgBackground.BitBlt(pDC->m_hDC, 0,0);


	//CFile file;
	//BITMAPFILEHEADER bfh;
	//BITMAPINFOHEADER bih;
	//BYTE* bits = NULL;

	//CBitmap bm;
	//CDC *clientDC;
	//CDC memDC;

	//try
	//{
	//	if (!file.Open(_T("res\\bgtest.bmp"), CFile::modeRead))
	//		throw "File not found";

	//	if (file.Read(&bfh, sizeof(BITMAPFILEHEADER)) < sizeof(BITMAPFILEHEADER)) {
	//		printf("aa");
	//		throw "Not bmp file";
	//	}
	//	if (file.Read(&bih, sizeof(BITMAPINFOHEADER)) < sizeof(BITMAPINFOHEADER)) {
	//		printf("bb");
	//		throw "Not bmp file";
	//	}
	//	bits = new BYTE[bih.biSizeImage];
	//	if (file.Read(bits, bih.biSizeImage) < bih.biSizeImage) {
	//		printf("cc");
	//		throw "Not bmp file";
	//	}
	//	if (!bm.CreateBitmap(bih.biWidth, bih.biHeight, bih.biPlanes, bih.biBitCount, bits))
	//		throw "Could not create bitmap";
	//	printf("dd");

	//	clientDC = this->GetDC();
	//	memDC.CreateCompatibleDC(clientDC);
	//	memDC.SelectObject(bm);
	//	clientDC->BitBlt(0, 0, bih.biWidth, bih.biHeight, &memDC, 0, 0, SRCCOPY);
	//}
	//catch (char *e)
	//{
	//	TRACE("%s\n", e);
	//}


	//CPaintDC dc(this);
	////==========================================
	////����̹��� ����
	//UINT tBG_IMAGE_ID = IDB_BITMAP3; //����� ����̹��� ID ����
	//CRect tRect;
	//GetClientRect(&tRect);
	////------------------------------------------
	////����̹��� �׸���. ���� ����
	//CBitmap tBitmap, *pOldBitmap;
	//CDC tMemdc; //�޸� DC ����
	//			//���� DC �� ȣȯ ������ �޸� DC ����
	//tMemdc.CreateCompatibleDC(&dc);
	////���ҽ� ��������.
	//tBitmap.LoadBitmap(IDB_BITMAP3);
	//pOldBitmap = tMemdc.SelectObject(&tBitmap);
	////�̹��� �Ѹ���. bitblt ��� ����
	//dc.BitBlt(0, 0, tRect.Width(), tRect.Height(), &tMemdc, 0, 0, SRCCOPY);

	////�޸� ����
	//tMemdc.SelectObject(pOldBitmap);
	//tBitmap.DeleteObject();
	//tMemdc.DeleteDC();


}


//BOOL SCREEN_STORY::OnEraseBkgnd(CDC* pDC)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
