#pragma once



// NewView �� ���Դϴ�.

class NewView : public CFormView
{
	DECLARE_DYNCREATE(NewView)

public:
	NewView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


