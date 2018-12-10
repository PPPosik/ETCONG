#pragma once
#include "afxwin.h"
#include "atlimage.h"



// SCREEN_START �� ���Դϴ�.

class SCREEN_START : public CFormView
{
	DECLARE_DYNCREATE(SCREEN_START)

public:
	SCREEN_START();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonStart();
	CBitmap m_bmpButton;
	CBitmapButton m_btnStart;
	virtual void OnInitialUpdate();


	virtual void OnDraw(CDC* /*pDC*/);
	CImage m_ImgBackground;
};


