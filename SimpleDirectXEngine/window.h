#pragma once
#define NOMINMAX
#include <Windows.h>

class engineTime;

class window
{
public:

	window();
	~window();

	bool init();
	bool release();
	bool boadcast();

	bool isRunning();

	RECT getClientWindowRect();
	void setHWND(HWND hwnd);

	virtual void onCreate();
	virtual void onUpdate();
	virtual void onDestroy();

	virtual void onFocus();
	virtual void onKillFocus();

protected:
	HWND m_hwnd;
	bool m_is_run;
};