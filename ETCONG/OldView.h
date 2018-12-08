#pragma once



// OldView 폼 뷰입니다.

class OldView : public CFormView
{
	DECLARE_DYNCREATE(OldView)

public:
	OldView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~OldView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OLDVIEW };
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


