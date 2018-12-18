#pragma once
#include "afxext.h"
#include "atlimage.h"



// SCREEN_NAME 폼 뷰입니다.

class SCREEN_NAME : public CFormView
{
	DECLARE_DYNCREATE(SCREEN_NAME)

public:
	SCREEN_NAME();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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