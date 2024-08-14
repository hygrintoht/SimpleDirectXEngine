#include "window.h"
#include "engineTime.h"

#include "iostream"
#include "Imgui/imgui.h"

window* windowPTR = nullptr;

window::window()
{
	
}

window::~window()
{
	
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam))
		return true;

	switch (msg)
	{
		case WM_CREATE:
		{
			windowPTR->setHWND(hwnd);
			windowPTR->onCreate();
			break;
		}
		case WM_SETFOCUS:
		{
			//window* m_window = (window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			//m_window->onFocus();
			windowPTR->onFocus();
			break;
		}
		case WM_KILLFOCUS:
		{
			//window* m_window = (window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			//m_window->onKillFocus();
			windowPTR->onKillFocus();
			break;
		}
		
		case WM_DESTROY:
		{
			windowPTR->onDestroy();
			::PostQuitMessage(0);
			break;
		}
		default:
		{
			return ::DefWindowProcA(hwnd, msg, wparam, lparam);
		}
	}
	return NULL;
}
bool window::init()
{
	WNDCLASSEXA wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = "MyWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassExA(&wc)) 
		return false;

	if (!windowPTR)
		windowPTR = this;

	m_hwnd=::CreateWindowExA
	(
		WS_EX_OVERLAPPEDWINDOW,
		"MyWindowClass",
		"DirectX Application",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		1024,
		768,
		NULL,
		NULL,
		NULL,
		NULL
	);

	if (!m_hwnd) 
		return false;

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	m_is_run = true;

	engineTime::get();

	return true;
}

bool window::release()
{
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

bool window::boadcast()
{
	engineTime::get()->logFrameStart();
	MSG msg;

	windowPTR->onUpdate();

	while(::PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

	engineTime::get()->logFrameEnd();
	return true;
}

bool window::isRunning()
{
	return m_is_run;
}

RECT window::getClientWindowRect()
{
	RECT rect;
	::GetClientRect(this->m_hwnd, &rect);
	return rect;
}

void window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}


void window::onCreate()
{
}

void window::onUpdate()
{
}

void window::onDestroy()
{
	m_is_run = false;
}

void window::onFocus()
{
	std::cout << "test" << std::endl;
}

void window::onKillFocus()
{
	std::cout << "test1" << std::endl;
}