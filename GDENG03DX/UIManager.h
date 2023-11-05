#pragma once
//#include "iostream"
#include "vector"
#include "string"
#include "unordered_map"

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"

#include "window.h"
#include "uiScreenAbstract.h"

struct uiNames
{
	const std::string PROFILER_SCREEN = "PROFILER_SCREEN";
	const std::string MENU_SCREEN = "MENU_SCREEN";
	const std::string INSPECTOR_SCREEN = "INSPECTOR_SCREEN";
	const std::string HIERARCHY_SCREEN = "HIERARCHY_SCREEN";
	const std::string TEST_SCREEN = "TEST_SCREEN";
};

class uiManager
{
public:
	

	static void init(HWND windowHandle);
	static void destroy();

	static uiManager* get();

	void drawUI();

	static constexpr int WINDOW_WIDTH = 1440;
	static constexpr int WINDOW_HEIGHT = 900;

private:
	uiManager(HWND windowHandle);
	~uiManager();

	uiManager(uiManager const& ) {}
	uiManager& operator= (uiManager const&) {}

	static uiManager* m_sharedInstance;

	std::vector<uiScreenAbstract*> m_ui_list;
	std::unordered_map<std::string, uiScreenAbstract*> m_ui_table;
};
