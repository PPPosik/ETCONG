
// ETCONG.h : ETCONG 응용 프로그램에 대한 주 헤더 파일
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH에 대해 이 파일을 포함하기 전에 'stdafx.h'를 포함합니다."
#endif

#include "resource.h"       // 주 기호입니다.
#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "SCREEN_STORY.h"
// CETCONGApp:
// 이 클래스의 구현에 대해서는 ETCONG.cpp을 참조하십시오.
//

class CETCONGApp : public CWinApp
{
public:
	CETCONGApp();


// 재정의입니다.
public:
	virtual BOOL InitInstance();

// 구현입니다.
	CView* SwitchView(int CurrentView, int story);
	CView* m_pStartScreen;
	CView* m_pNameScreen;
	SCREEN_STORY* m_pStoryScreen;
	CETCONGView* m_pGameScreen;
	int m_nCurrentView;
	int getCurrentView();
	void setCurrentView(int value);
	void CallDeath(bool bWho);
	bool m_bInited;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	bool bViewInit;
};

extern CETCONGApp theApp;
