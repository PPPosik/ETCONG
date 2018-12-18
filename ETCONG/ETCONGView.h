
// ETCONGView.h : CETCONGView Ŭ������ �������̽�
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
public: // serialization������ ��������ϴ�.
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

#ifndef _DEBUG  // ETCONGView.cpp�� ����� ����
inline CETCONGDoc* CETCONGView::GetDocument() const
   { return reinterpret_cast<CETCONGDoc*>(m_pDocument); }
#endif

