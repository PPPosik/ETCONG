#pragma once



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
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonGoback();
	afx_msg void OnBnClickedButtonStartGame();
//	CString m_strName;
	CString m_strName;
	CString GetPlayerName();
};


