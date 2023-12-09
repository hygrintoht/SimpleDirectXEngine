#include "uiManager.h"

#include <iostream>

#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_dx11.h"
#include "Imgui/imgui_impl_win32.h"

#include "graphicsEngine.h"
#include "deviceContext.h"
#include "uiTestScreen.h"
#include "uiEngineProfiler.h"
#include "uiInspector.h"
#include "uiToolbar.h"
#include "uiWorldOutliner.h"
#include "swapChain.h"
#include "uiDebugConsole.h"

uiManager* uiManager::m_sharedInstance = nullptr;;

uiManager::uiManager(HWND windowHandle,swapChain* _swapChain)
{
	m_swap_chain = _swapChain;

	m_window_handle = windowHandle;

	const uiNames ui_names;

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplWin32_Init(windowHandle);
	ImGui_ImplDX11_Init(graphicsEngine::get()->getD3D11Device(), graphicsEngine::get()->getImmediateDeviceContext()->getDeviceContext());

	// create and add all needed ui screens below then add each to the ui list(not ui table)
	auto* ui_toolbar = new uiToolbar(ui_names.MENU_SCREEN);
	m_ui_list.push_back(ui_toolbar);

	auto* ui_test_screen = new uiTestScreen(ui_names.TEST_SCREEN);
	m_ui_list.push_back(ui_test_screen);

	auto* ui_engine_profiler = new uiEngineProfiler(ui_names.PROFILER_SCREEN);
	m_ui_list.push_back(ui_engine_profiler);

	auto* ui_inspector = new uiInspector(ui_names.INSPECTOR_SCREEN);
	m_ui_list.push_back(ui_inspector);

	auto* ui_world_outliner = new uiWorldOutliner(ui_names.HIERARCHY_SCREEN);
	m_ui_list.push_back(ui_world_outliner);

	auto* ui_debug_window = new uiDebugConsole(ui_names.DEBUG_WINDOW);
	m_ui_list.push_back(ui_debug_window);

	// end of ui creation

	// for each ui screen in ui list
	for (int i = 0; i < this->m_ui_list.size(); i++) 
	{	// add ui screen to ui table and assign its name as its key
		m_ui_table[m_ui_list[i]->getName()] = m_ui_list[i];
	}
}

uiManager::~uiManager()
{
}

uiManager* uiManager::get()
{
	if (m_sharedInstance != nullptr)
		return m_sharedInstance;
}

void uiManager::init(HWND windowHandle, swapChain* _swapChain)
{
	if(m_sharedInstance == nullptr)
		m_sharedInstance = new uiManager(windowHandle, _swapChain);
}

void uiManager::destroy()
{

}

void uiManager::drawUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);
	for (auto& m_ui : this->m_ui_list)
	{
		m_ui->drawUI();
	}
}

HWND uiManager::getWindowHandle()
{
	return m_window_handle;
}

swapChain* uiManager::getSwapChain()
{
	return m_swap_chain;
}

void uiManager::toggleUIScreen(std::string _uiName)
{
	for(auto ui : m_ui_list)
	{
		if(ui->getName() == _uiName)
		{
			ui->m_active = !ui->m_active;
			std::cout << "bool" << ui->m_active << std::endl;
		}
	}
}
