#include "stdafx.h"
#include "Player.h"
#include "GameGraphics.h"
#include "ETCONG.h"

CPlayer::CPlayer()
{
	m_nLife = 3;
	m_pPos = CPoint(100, 100);
	IsAlive = true;
}


CPlayer::~CPlayer() {

}


int CPlayer::getLife() {
	return m_nLife;
}


void CPlayer::setLife(int life) {
	m_nLife = life;
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
}


void CPlayer::OuchHurt()
{
	m_nLife = m_nLife - 1;
	if (m_nLife == 0)
	{
		IsAlive = false;
		CETCONGApp *pApp = (CETCONGApp*)AfxGetApp();
		pApp->CallDeath(true);
		
	}
}
