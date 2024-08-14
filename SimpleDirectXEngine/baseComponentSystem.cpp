#include "baseComponentSystem.h"

baseComponentSystem* baseComponentSystem::m_shared_instance = nullptr;

baseComponentSystem::baseComponentSystem()
{
    m_physics_system = new physicsSystem();
}

baseComponentSystem::~baseComponentSystem()
{
}

baseComponentSystem* baseComponentSystem::get()
{
    if(m_shared_instance == nullptr)
    {
        init();
    }

    return m_shared_instance;
}

void baseComponentSystem::init()
{
    m_shared_instance = new baseComponentSystem();
}


void baseComponentSystem::destroy()
{
    delete m_shared_instance; // not confusing at all :D
}

physicsSystem* baseComponentSystem::getPhysicsSystem()
{
    return m_physics_system;
}

