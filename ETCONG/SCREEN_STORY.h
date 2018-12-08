#pragma once
#include "atlimage.h"
#include "atltypes.h"
#include "afxwin.h"



// SCREEN_STORY 폼 뷰입니다.

class SCREEN_STORY : public CFormView
{
	DECLARE_DYNCREATE(SCREEN_STORY)

public:
	SCREEN_STORY();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~SCREEN_STORY();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREEN_STORY };
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
	afx_msg void OnBnClickedButtonSkip();
	
	CString m_strStory;
	afx_msg void OnEnChangeEditStory();
	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);
	afx_msg void OnBnClickedButtonNext();
	CImage m_ImgBackground;
	void drawBackground();
//	CPoint m_pBackgroundPos;
//	int m_nBackgroundWidth;
//	int m_nBackgroundHeight;
//	CBitmap m_bmpBackground;
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


