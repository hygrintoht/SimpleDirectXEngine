#include "uiWorldOutliner.h"

#include "gameObject.h"
#include "Imgui/imgui.h"
#include "gameObjectManager.h"

void uiWorldOutliner::drawUI()
{
	if (m_active)
	{
		ImGui::Begin("World Outliner", &m_tool_active, ImGuiWindowFlags_None);
		for (int i = 0; i < gameObjectManager::get()->getGameObjectList()->size(); i++)
		{
			if (ImGui::Button(gameObjectManager::get()->getGameObjectList()->at(i)->getName().c_str()))
			{
				gameObjectManager::get()->setSelectedObject(gameObjectManager::get()->getGameObjectList()->at(i));
			}
		}
		ImGui::End();
	}
}
