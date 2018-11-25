#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer() {
	m_nLife = 3;
	m_Img.Load(_T("res\player.png"));
	m_nWidth = 100;
	m_nHeight = 100;
	m_Ppos = CPoint(100, 100);
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
	m_Img.Destroy();
	HRESULT hResult = m_Img.Load(_T("res\\player.png"));
	m_nWidth = m_Img.GetWidth();
	m_nHeight = m_Img.GetHeight();
	if (FAILED(hResult)) {
		AfxMessageBox(_T("Img ERROR"));
		return;
	}
	m_Img.BitBlt(pDC->m_hDC, m_Ppos.x, m_Ppos.y);
}


void CPlayer::drawAttack(CDC *pDC) {
	m_Img.Destroy();
	HRESULT hResult = m_Img.Load(_T("res\\attack.png"));
	m_nWidth = m_Img.GetWidth();
	m_nHeight = m_Img.GetHeight();
	if (FAILED(hResult)) {
		AfxMessageBox(_T("Img ERROR"));
		return;
	}
	m_Img.BitBlt(pDC->m_hDC, m_Ppos.x, m_Ppos.y);
}


void CPlayer::drawError(CDC *pDC) {
	m_Img.Destroy();
	HRESULT hResult = m_Img.Load(_T("res\\error.png"));
	m_nWidth = m_Img.GetWidth();
	m_nHeight = m_Img.GetHeight();
	if (FAILED(hResult)) {
		AfxMessageBox(_T("Img ERROR"));
		return;
	}
	m_Img.BitBlt(pDC->m_hDC, m_Ppos.x, m_Ppos.y);
}


CPoint CPlayer::getPos() {
	return m_Ppos;
}


void CPlayer::setPos(int x, int y) {
	m_Ppos = CPoint(x, y);
}

