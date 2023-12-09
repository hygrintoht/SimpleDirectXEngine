#pragma once
#include "component.h"
#include "mathUtils.h"
//#include "quaternion.h"
#include "vector"
#include "string"

class vertexBuffer;
class indexBuffer;
class constantBuffer;

class quaternion;

class gameObject
{
public:
	gameObject();
	gameObject(std::string name);
	virtual ~gameObject();

	virtual void init();
	virtual void release();

	virtual void update(matrix4x4 world_camera_temp, float top, float bottom, float right, float left); //update every frame
	virtual void update(float deltaTime,matrix4x4 world_camera_temp, float top, float bottom, float right, float left); //update every frame
	virtual void draw(); // draw object to scene

	enum gameObjectType
	{
		none = 0,
		mesh,
		cube
	};

	enum unityGameObjectType
	{
		non_object = -1,
		cube_object,
		physics_plane_object,
		physics_cube_object
	};

	void loadVertexBuffer(void* shader_byte_code, size_t size_byte_shader); // load vertex buffer to object
	constantBuffer* getConstantBuffer() const;

	std::string getName();
	void setName(std::string name);
	gameObjectType getType();
	unityGameObjectType getUnityType();

	matrix4x4 m_transform = matrix4x4::identityMatrix(); // transform of object(public);
	// remove because of transform class?
	void setPosition(vector3 position);
	void setScale(vector3 scale);
	void setRotation(vector3 rotation);
	void setRotation(quaternion rotation);

	void setMatrix(vector3 position, vector3 scale, quaternion rotation);

	void attachComponent(component* component);
	void detachComponent(component* component);

	component* findComponentByName(std::string name);
	component* findComponentOfType(component::componentType type, std::string name);
	std::vector<component*> getComponentsOfType(component::componentType type);
	std::vector<component*> getComponentsOfTypeRecursive(component::componentType type);

private:

	//buffer data
	vertexBuffer* m_vertex_buffer;
	indexBuffer* m_index_buffer;

protected:
	std::string m_name = "";
	gameObjectType m_game_object_type = none;
	unityGameObjectType m_unity_game_object_type = non_object;

	constantBuffer* m_constant_buffer;

	//scene data
	bool m_isActive = true; // active status
	//mesh data
	std::vector<vertex> m_vertex_list; // list of object vertices
	std::vector<unsigned int> m_index_list; // list of object indices

	std::vector<component*> m_componentList;
};
