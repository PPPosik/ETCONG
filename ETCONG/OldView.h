#pragma once



// OldView �� ���Դϴ�.

class OldView : public CFormView
{
	DECLARE_DYNCREATE(OldView)

public:
	OldView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


