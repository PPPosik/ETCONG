#pragma once



// SCREEN_GAME �� ���Դϴ�.

class SCREEN_GAME : public CFormView
{
	DECLARE_DYNCREATE(SCREEN_GAME)

public:
	SCREEN_GAME();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~SCREEN_GAME();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SCREEN_GAME };
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
};


