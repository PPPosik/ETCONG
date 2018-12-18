#pragma once
#include "afxext.h"
#include "atlimage.h"



// SCREEN_NAME �� ���Դϴ�.

class SCREEN_NAME : public CFormView
{
	DECLARE_DYNCREATE(SCREEN_NAME)

public:
	SCREEN_NAME();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~SCREEN_NAME();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREEN_NAME };
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
	afx_msg void OnBnClickedButtonStartGame();
	//	CString m_strName;
	CString m_strName;
	CString GetPlayerName();
	CBitmapButton m_btnStarts;
	virtual void OnDraw(CDC* /*pDC*/);
	CImage m_ImageBackground;
};