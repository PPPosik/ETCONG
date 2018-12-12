#pragma once
#include "atlimage.h"
#include "atltypes.h"
#include "afxwin.h"
#include "afxext.h"



// SCREEN_STORY �� ���Դϴ�.

class SCREEN_STORY : public CFormView
{
	DECLARE_DYNCREATE(SCREEN_STORY)

public:
	SCREEN_STORY();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSkip();
	afx_msg void OnEnChangeEditStory();
	afx_msg void OnBnClickedButtonNext();

	virtual void OnInitialUpdate();
	virtual void OnDraw(CDC* /*pDC*/);

	void drawBG();

	bool inited;
	int m_nStoryScene;
	int nStoryType;

	CBitmapButton m_btnNext;
	CBitmapButton m_btnSkip;
	
	CImage m_ImgBackground;
	CImage storySet[4];
	CImage storyEnd[8];
	CImage storyDied[3];
};