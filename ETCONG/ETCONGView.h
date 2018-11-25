
// ETCONGView.h : CETCONGView 클래스의 인터페이스
//

#pragma once
#include "Player.h"
#include "atlimage.h"
#include "atltypes.h"
#include "SoundPlayer.h"


class CETCONGView : public CView
{
protected: // serialization에서만 만들어집니다.
	CETCONGView();
	DECLARE_DYNCREATE(CETCONGView)

// 특성입니다.
public:
	CETCONGDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CETCONGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // ETCONGView.cpp의 디버그 버전
inline CETCONGDoc* CETCONGView::GetDocument() const
   { return reinterpret_cast<CETCONGDoc*>(m_pDocument); }
#endif

