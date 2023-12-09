#pragma once
#include "string"

class gameObject;

class component
{
public:
	enum componentType
	{
		NotSet = -1,
		Script,
		Renderer,
		Input,
		Physics
	};

	component(std::string name, componentType type, gameObject* owner);
	virtual ~component();

	void attachOwner(gameObject* owner);
	void detachOwner();
	gameObject* getOwner();
	componentType getType();
	std::string getName();

	virtual void perform(float deltaTime) = 0;

protected:
	gameObject* m_owner;
	componentType m_type;
	std::string m_name;
};
