#pragma once
#include "physicsSystem.h"

class baseComponentSystem
{
public:
	static baseComponentSystem* get();
	static void init();
	static void destroy();

	physicsSystem* getPhysicsSystem();
	
private:
	baseComponentSystem();
	~baseComponentSystem();
	baseComponentSystem(baseComponentSystem const&) {}
	baseComponentSystem& operator = (baseComponentSystem const&) { }
	static baseComponentSystem* m_shared_instance;

	physicsSystem* m_physics_system;
};
