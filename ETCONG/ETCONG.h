
// ETCONG.h : ETCONG ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


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
	CView* SwitchView(int CurrentView);
	CView* m_pStartScreen;
	CView* m_pNameScreen;
	CView* m_pStoryScreen;
	CView* m_pGameScreen;
	int m_nCurrentView;
	int getCurrentView();
	void setCurrentView(int value);
	bool m_bInited;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CETCONGApp theApp;
