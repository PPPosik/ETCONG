
// ETCONGView.h : CETCONGView 클래스의 인터페이스
//

#pragma once
#include "Player.h"
#include "atlimage.h"
#include "atltypes.h"
#include "SoundPlayer.h"
#include "CustomThread.h"
#include "MyAnimation.h"
#include "BulletCalculate.h"
#include "Enemy.h"
#include "GameGraphics.h"


class CETCONGView : public CView
{
public: // serialization에서만 만들어집니다.
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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDestroy();
	
	CPlayer m_player;
	CPoint m_pBackgroundPos;
	CImage backgroundImg;
	CImage m_ImgBackground;
	CSoundPlayer m_sound;
	CCustomThread m_customThread;
	CBulletCalculate m_newone;
	
	int m_nTimerFlag;
	int m_nTime;
	int m_nClick;
	int m_nDelay;
	int m_nInit;
	int m_nBackgroundWidth;
	int m_nBackgroundHeight;
	bool m_bClickable;
	bool m_bError;
	bool m_bStageStart;

	CMyAnimation m_animation;
	virtual void OnInitialUpdate();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	
	CImage m_imgBulletPlayer;
	CEnemy m_aEnemy;
	CGameGraphics m_display;

	void StopMember();
};

#ifndef _DEBUG  // ETCONGView.cpp의 디버그 버전
inline CETCONGDoc* CETCONGView::GetDocument() const
   { return reinterpret_cast<CETCONGDoc*>(m_pDocument); }
#endif

