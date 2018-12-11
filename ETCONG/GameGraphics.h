#pragma once
#include "atlImage.h"
class CGameGraphics
{
public:
	CGameGraphics();
	~CGameGraphics();
	void DisplayThread();
	UINT Display(LPVOID _mothod);
	static UINT DisplayStatic(LPVOID _mothod);

	CImage m_ImgBackground;
	CImage m_ImgMove;
	CImage m_ImgAttack;
	CImage m_ImgError;
	CImage m_imgEnemyDefault;
	CImage m_ImgMoveAni[9];
	CImage m_imgBulletfromUser;
	CImage m_imgMineAttack[3];
	CImage m_imgBlind;
	

	bool IsMoveActivated;
	int MotionCount;
	bool IsBulletShooted;
	CPoint m_nPlayerBulletPos;
	bool DoesEnemyaMined;
	CPoint m_nEnemyMinePos;
	int m_nEnemyMineLevel;
	bool DoesEnemyBlined;

	void Init();
	void ActiveMoveAnimation();
	void ActiveBulletAnimation(int x, int y);
	void EndBulletAnimation();
	void ActiveEnemyMine(int lv, int x, int y);
	void ActiveEnemyBlind();
	void RevealedPlayerBling();
};
