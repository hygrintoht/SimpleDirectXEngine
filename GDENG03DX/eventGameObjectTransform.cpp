#include "eventGameObjectTransform.h"

#include "debugLog.h"
#include "eventHistoryManager.h"
#include "gameObjectManager.h"

eventGameObjectTransform::eventGameObjectTransform(gameObject* _gameObject, matrix4x4 _matrix) : m_game_object(_gameObject), m_matrix(_matrix)
{
	debugLog::get()->addLog("transform changed: " + m_game_object->getName());
}

eventGameObjectTransform::~eventGameObjectTransform()
{
}

void eventGameObjectTransform::getState()
{
	debugLog::get()->addLog("transform get state: " + m_game_object->getName());
	m_game_object->m_transform.setMatrix(m_matrix);
}

eventAbstract* eventGameObjectTransform::createCurrentState()
{
	return new eventGameObjectTransform(m_game_object, m_game_object->m_transform); // record current transform of the object
}