#include "physicsComponent.h"

#include "baseComponentSystem.h"
#include "gameObject.h"

physicsComponent::physicsComponent(std::string name, gameObject* owner) : component(name, Physics, owner)
{
	baseComponentSystem::get()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physics_common = baseComponentSystem::get()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physics_world = baseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();

	vector3 scale = this->getOwner()->m_transform.getScale();
	Transform transform;
	matrix4x4 mat = getOwner()->m_transform.getGLMatrixFromMatrix();
	transform.setFromOpenGL(*mat.m_mat);
	BoxShape* box_shape = physics_common->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
	this->m_rigidBody = physics_world->createRigidBody(transform);
	this->m_rigidBody->addCollider(box_shape, transform);
	this->m_rigidBody->updateMassPropertiesFromColliders();
	this->m_rigidBody->setMass(m_mass);
	this->m_rigidBody->setType(BodyType::DYNAMIC);

	transform = this->m_rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	getOwner()->m_transform.setMatrixFromGLMatrix(matrix);
	//std::cout << "My component is updating: " << m_name << std::endl;
}

physicsComponent::~physicsComponent()
{
	baseComponentSystem::get()->getPhysicsSystem()->unregisterComponent(this);
	component::~component();
}

void physicsComponent::perform(float deltaTime)
{
	const Transform transform = this->m_rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->m_transform.setMatrixFromGLMatrix(matrix);
	//std::cout << "My component is updating: " << m_name << std::endl;
}

RigidBody* physicsComponent::getRigidBody()
{
	return m_rigidBody;
}