#include "stdafx.h"
#include "SoundPlayer.h"

#pragma comment (lib, "winmm")
#include <mmsystem.h>

CSoundPlayer::CSoundPlayer()
{
}


CSoundPlayer::~CSoundPlayer()
{
}


void CSoundPlayer::stage1Play() {
	// SND_ASYNC | SND_LOOP
	PlaySound(_T("res\\testMusic.wav"), AfxGetInstanceHandle(), SND_ASYNC);
}


void CSoundPlayer::stop() {
	sndPlaySound(NULL, SND_ASYNC);
}

