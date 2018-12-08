// NewView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ETCONG.h"
#include "NewView.h"


// NewView

IMPLEMENT_DYNCREATE(NewView, CFormView)

NewView::NewView()
	: CFormView(IDD_NEWVIEW)
{

}

NewView::~NewView()
{
}

void NewView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(NewView, CFormView)
END_MESSAGE_MAP()


// NewView 진단입니다.

#ifdef _DEBUG
void NewView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void NewView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// NewView 메시지 처리기입니다.
