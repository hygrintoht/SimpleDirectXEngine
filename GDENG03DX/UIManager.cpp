#include "uiManager.h"

#include "graphicsEngine.h"
#include "deviceContext.h"

//#include "iostream"

#include "uiTestScreen.h"

uiManager* uiManager::m_sharedInstance = nullptr;;

uiManager::uiManager(HWND windowHandle)
{
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
	auto* ui_test_screen = new uiTestScreen(ui_names.TEST_SCREEN);
	m_ui_list.push_back(ui_test_screen);


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

void uiManager::init(HWND windowHandle)
{
	if(m_sharedInstance == nullptr)
		m_sharedInstance = new uiManager(windowHandle);
}

void uiManager::destroy()
{

}

void uiManager::drawUI()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	for (auto& i : this->m_ui_list)
	{
		i->drawUI();
	}
}
