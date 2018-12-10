#pragma once
#include "afxwin.h"
#include "atlimage.h"



// SCREEN_START 폼 뷰입니다.

class SCREEN_START : public CFormView
{
	DECLARE_DYNCREATE(SCREEN_START)

public:
	SCREEN_START();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SCREEN_START();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREEN_START };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	CBitmap m_bmpButton;
	CBitmapButton m_btnStart;
	virtual void OnInitialUpdate();


	virtual void OnDraw(CDC* /*pDC*/);
	CImage m_ImgBackground;
};


