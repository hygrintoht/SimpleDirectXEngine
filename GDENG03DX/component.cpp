#include "component.h"

component::component(std::string name, componentType type, gameObject* owner)
{
	m_name = name;
	m_type = type;
	m_owner = owner;
}


component::~component()
{
}

void component::attachOwner(gameObject* owner)
{
	m_owner = owner;
}

void component::detachOwner()
{
	m_owner = nullptr;
}

gameObject* component::getOwner()
{
	return m_owner;
}

component::componentType component::getType()
{
	return m_type;
}

std::string component::getName()
{
	return m_name;
}
