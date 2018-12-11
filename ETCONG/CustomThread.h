#pragma once
class CCustomThread
{
public:
	CCustomThread();
	~CCustomThread();

	static UINT ThreadAbsolute(LPVOID _mothod);
	static UINT ThreadClickDelay(LPVOID _mothod);
	void StartThread();
	void StopThread();

	CWinThread *pClick;
	CWinThread *pAbsolute;
};

