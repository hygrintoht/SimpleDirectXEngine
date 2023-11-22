#include "physicsSystem.h"

#include "iostream"

#include "engineTime.h"
#include "physicsComponent.h"

physicsSystem::physicsSystem()
{
	m_physicsCommon = new PhysicsCommon();

	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);

	m_physicsWorld = m_physicsCommon->createPhysicsWorld(settings);
}

physicsSystem::~physicsSystem()
{
	delete this->m_physicsCommon;
}

void physicsSystem::registerComponent(physicsComponent* component)
{
	m_componentTable[component->getName()] = component;
	m_componentList.push_back(component);
}

void physicsSystem::unregisterComponent(physicsComponent* component)
{
	unregisterComponent(component->getName());
}

void physicsSystem::unregisterComponent(std::string name)
{
	for (int i = 0; i < m_componentList.size(); i++)
	{
		if (m_componentList[i]->getName() == name)
			m_componentList.erase(m_componentList.begin() + i);
	}

	m_componentTable.erase(name);
}

physicsComponent* physicsSystem::findComponentByName(std::string name)
{
	return m_componentTable[name];
}

std::vector<physicsComponent*> physicsSystem::getAllComponents()
{
	return m_componentList;
}

void physicsSystem::updateAllComponents()
{
	if (engineTime::get()->getDeltaTime() > 0.0f)
	{
		this->m_physicsWorld->update(engineTime::get()->getDeltaTime());
		for (auto* component : m_componentList)
			component->perform(engineTime::get()->getDeltaTime());
	}
}

PhysicsWorld* physicsSystem::getPhysicsWorld()
{
	return m_physicsWorld;
}

PhysicsCommon* physicsSystem::getPhysicsCommon()
{
	return m_physicsCommon;
}
