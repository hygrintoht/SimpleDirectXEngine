#include "gameObject.h"

#include "iostream"

#include "graphicsEngine.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "constantBuffer.h"
#include "deviceContext.h"

#include "matrix4x4.h"
#include "quaternion.h"

gameObject::gameObject()
{
}

gameObject::gameObject(std::string name)
{
	m_name = name;
}

gameObject::~gameObject()
{
}

void gameObject::init()
{
	//m_transform.setIdentity();

	m_vertex_buffer = graphicsEngine::get()->createVertexBuffer();
	m_index_buffer = graphicsEngine::get()->createIndexBuffer();
	m_constant_buffer = graphicsEngine::get()->createConstantBuffer();

	m_index_buffer->load(m_index_list.data() , m_index_list.size());

	constant cc;
	cc.m_time = 0;

	m_constant_buffer->load(&cc, sizeof(constant)); // default constant;
}

void gameObject::release()
{
	m_vertex_buffer->release();
	m_index_buffer->release();
	m_constant_buffer->release();
	//delete this;
}

void gameObject::update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{
}

void gameObject::update(float deltaTime, matrix4x4 world_camera_temp, float top, float bottom, float right, float left)
{
}

void gameObject::draw()
{
	graphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vertex_buffer);
	graphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_index_buffer);
	graphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_index_buffer->getSizeIndexList(), 0, 0);
}

void gameObject::loadVertexBuffer(void* shader_byte_code, size_t size_byte_shader)
{
	m_vertex_buffer->load(m_vertex_list.data(), sizeof(vertex), m_vertex_list.size(), shader_byte_code, size_byte_shader);
}

constantBuffer* gameObject::getConstantBuffer() const
{
	return m_constant_buffer;
}

std::string gameObject::getName()
{
	return m_name;
}

void gameObject::setName(std::string name)
{
	m_name = name;
}

gameObject::gameObjectType gameObject::getType()
{
	return m_game_object_type;
}

gameObject::unityGameObjectType gameObject::getUnityType()
{
	return m_unity_game_object_type;
}

void gameObject::setPosition(vector3 position)
{
	m_transform.setTranslation(position);
}

void gameObject::setScale(vector3 scale)
{
	m_transform.setScale(scale);
}

void gameObject::setRotation(vector3 rotation)
{
	m_transform.setRotation(rotation);
	//quaternion temp = quaternion::fromRotationMatrix(m_transform); // get quaternion from current rotation matrix
	//temp.rotateByEulerAngles(rotation); // rotate quaternion by euler angles ("add the rotation")
	//m_transform = m_transform * temp.toRotationMatrix(); // add the rotation to the transform
}

void gameObject::setRotation(quaternion rotation)
{
	m_transform = m_transform * rotation.toRotationMatrix();
}

void gameObject::setMatrix(vector3 position, vector3 scale, quaternion rotation)
{
	matrix4x4 _position;
	_position.identityMatrix();
	_position.setTranslation(position);

	matrix4x4 _scale;
	_scale.setScale(scale);

	matrix4x4 _rotation = rotation.toRotationMatrix();

	m_transform = _scale * _rotation * _position;
}


void gameObject::attachComponent(component* component)
{
	this->m_componentList.push_back(component);
	component->attachOwner(this);
}

void gameObject::detachComponent(component* component)
{
	for (int i = 0; i < this->m_componentList.size(); i++) 
	{
		if (this->m_componentList[i] == component) 
		{
			this->m_componentList.erase(this->m_componentList.begin() + i);
			break;
		}
	}
}

component* gameObject::findComponentByName(std::string name)
{
	for (auto* m_component : m_componentList) 
	{
		if (m_component->getName() == name)
		{
			return m_component;
		}
	}

	return NULL;
}

component* gameObject::findComponentOfType(component::componentType type, std::string name)
{
	for (auto* m_component : m_componentList) 
	{
		if (m_component->getName() == name && m_component->getType() == type) 
		{
			return m_component;
		}
	}

	return NULL;
}

std::vector<component*> gameObject::getComponentsOfType(component::componentType type)
{
	std::vector<component*> componentsOfType;
	for (auto* m_component : m_componentList) 
	{
		if (m_component->getType() == type) 
		{
			componentsOfType.push_back(m_component);
		}
	}

	return componentsOfType;
}

std::vector<component*> gameObject::getComponentsOfTypeRecursive(component::componentType type)
{
	std::vector<component*> componentsOfType;
	for (auto* m_component : m_componentList) 
	{
		if (m_component->getType() == type) 
		{
			componentsOfType.push_back(m_component);
		}
	}

	return componentsOfType;
}
