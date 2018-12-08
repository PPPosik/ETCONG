// SCREEN_GAME.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "ETCONG.h"
#include "SCREEN_GAME.h"


// SCREEN_GAME

IMPLEMENT_DYNCREATE(SCREEN_GAME, CFormView)

SCREEN_GAME::SCREEN_GAME()
	: CFormView(IDD_SCREEN_GAME)
{

}

SCREEN_GAME::~SCREEN_GAME()
{
}

void SCREEN_GAME::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(SCREEN_GAME, CFormView)
END_MESSAGE_MAP()


// SCREEN_GAME 진단입니다.

#ifdef _DEBUG
void SCREEN_GAME::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SCREEN_GAME::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SCREEN_GAME 메시지 처리기입니다.
