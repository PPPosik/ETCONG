
// ETCONGView.h : CETCONGView Ŭ������ �������̽�
//

#pragma once
#include "Player.h"
#include "atlimage.h"
#include "atltypes.h"
#include "SoundPlayer.h"


class CETCONGView : public CView
{
protected: // serialization������ ��������ϴ�.
	CETCONGView();
	DECLARE_DYNCREATE(CETCONGView)

// Ư���Դϴ�.
public:
	CETCONGDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CETCONGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	CPlayer m_player;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	CPoint m_pBackgroundPos;
	CImage backgroundImg;
	void drawBackground();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	int m_nTimerFlag;
	CSoundPlayer m_sound;
	int m_nTime;
	int m_nClick;
	int m_nDelay;
	bool m_bClickable;
	void StartTimer();
	void EndTimer();
	afx_msg void OnDestroy();
};

#ifndef _DEBUG  // ETCONGView.cpp�� ����� ����
inline CETCONGDoc* CETCONGView::GetDocument() const
   { return reinterpret_cast<CETCONGDoc*>(m_pDocument); }
#endif

