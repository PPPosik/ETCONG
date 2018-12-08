#pragma once



// NewView 폼 뷰입니다.

class NewView : public CFormView
{
	DECLARE_DYNCREATE(NewView)

public:
	NewView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~NewView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

public:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};


