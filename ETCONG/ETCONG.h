
// ETCONG.h : ETCONG ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "ETCONGDoc.h"
#include "ETCONGView.h"
#include "SCREEN_STORY.h"
// CETCONGApp:
// �� Ŭ������ ������ ���ؼ��� ETCONG.cpp�� �����Ͻʽÿ�.
//

class CETCONGApp : public CWinApp
{
public:
	CETCONGApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.
	CView* m_pNewView;
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
