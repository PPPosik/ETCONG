#include "stdafx.h"
#include "Player.h"
#include "GameGraphics.h"


CPlayer::CPlayer()
{
	m_nLife = 3;
	m_nWidth = 100;
	m_nHeight = 100;
	m_pPos = CPoint(100, 100);
	IsAlive = true;
}


CPlayer::~CPlayer() {

}


int CPlayer::getWidth() {
	return m_nWidth;
}


void CPlayer::setWidth(int width) {
	m_nWidth = width;
}


int CPlayer::getHeight() {
	return m_nHeight;
}


void CPlayer::setHeight(int height) {
	m_nHeight = height;
}


int CPlayer::getLife() {
	return m_nLife;
}


void CPlayer::setLife(int life) {
	m_nLife = life;
}


void CPlayer::drawMove(CDC *pDC) {
	if (IsAlive) {
		m_nWidth = m_ImgMove.GetWidth();
		m_nHeight = m_ImgMove.GetHeight();

		m_ImgMove.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	}
	
}


void CPlayer::drawAttack(CDC *pDC) {
	
	if (IsAlive) {
		m_nWidth = m_ImgAttack.GetWidth();
		m_nHeight = m_ImgAttack.GetHeight();

		m_ImgAttack.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	}
	
}


void CPlayer::drawError(CDC *pDC) {
	if (IsAlive) {
		m_nWidth = m_ImgError.GetWidth();
		m_nHeight = m_ImgError.GetHeight();

		m_ImgError.BitBlt(pDC->m_hDC, m_pPos.x, m_pPos.y);
	}
	
}


CPoint CPlayer::getPos() {
	return m_pPos;
}


void CPlayer::setPos(int x, int y) {
	m_pPos = CPoint(x, y);
}


void CPlayer::ImageInit()
{
	IsAlive = true;
	m_ImgMove.Load(_T("res\\player.png"));
	m_ImgAttack.Load(_T("res\\attack.png"));
	m_ImgError.Load(_T("res\\error.png"));
}


void CPlayer::OuchHurt()
{
	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	//CETCONGView *pView = (CETCONGView*)pFrame->GetActiveView();

	m_nLife = m_nLife - 1;
	//pView->m_display.PlayerHurt();
	if (m_nLife == 0)
	{
		IsAlive = false;
		printf("\nYOUDEAD\n");
	}
}
