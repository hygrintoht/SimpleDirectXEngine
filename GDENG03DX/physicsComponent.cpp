#include "physicsComponent.h"

#include "baseComponentSystem.h"
#include "gameObject.h"

physicsComponent::physicsComponent(std::string name, gameObject* owner) : component(name, Physics, owner)
{
	baseComponentSystem::get()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physics_common = baseComponentSystem::get()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physics_world = baseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();

	m_scale = this->getOwner()->m_transform.getScale();

	matrix4x4 mat = getOwner()->m_transform.getGLMatrixFromMatrix();
	Transform transform;
	transform.setFromOpenGL(*mat.m_mat);
	// rigid body initialization
	this->m_rigidBody = physics_world->createRigidBody(transform); // position and rotation of object

	// collider initialization
	BoxShape* box_shape = physics_common->createBoxShape(Vector3(m_scale.m_x / 2, m_scale.m_y / 2, m_scale.m_z / 2));
	this->m_rigidBody->addCollider(box_shape, Transform(Vector3(0,0,0),Quaternion::identity())); // local position and rotation of object(0 pos 0 rot)

	this->m_rigidBody->updateMassPropertiesFromColliders();
	this->m_rigidBody->setMass(m_mass);
	this->m_rigidBody->setType(BodyType::DYNAMIC);

	transform = this->m_rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	getOwner()->m_transform.setMatrixFromGLMatrix(matrix, m_scale);
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

	this->getOwner()->m_transform.setMatrixFromGLMatrix(matrix, m_scale);
	//std::cout << "My component is updating: " << m_name << std::endl;
}

bool physicsComponent::getGravityEnabled()
{
	return m_gravity_enabled;
}

void physicsComponent::toggleGravity()
{
	m_gravity_enabled = !m_gravity_enabled;

	m_rigidBody->enableGravity(m_gravity_enabled);
}

void physicsComponent::addForce()
{
	m_rigidBody->applyLocalForceAtCenterOfMass(Vector3(10, 200, 0));
}

float physicsComponent::getMass()
{
	return m_mass;
}

void physicsComponent::setMass(float mass)
{
	m_mass = mass;
	m_rigidBody->setMass(mass);
}

RigidBody* physicsComponent::getRigidBody()
{
	return m_rigidBody;
}