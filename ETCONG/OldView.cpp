// OldView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ETCONG.h"
#include "OldView.h"


// OldView

IMPLEMENT_DYNCREATE(OldView, CFormView)

OldView::OldView()
	: CFormView(IDD_OLDVIEW)
{

}

OldView::~OldView()
{
}

void OldView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(OldView, CFormView)
END_MESSAGE_MAP()


// OldView 진단입니다.

#ifdef _DEBUG
void OldView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void OldView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// OldView 메시지 처리기입니다.
