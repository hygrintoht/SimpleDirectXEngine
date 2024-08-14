#pragma once
#include "eventAbstract.h"

#include "gameObject.h"
//#include "transform.h"
#include "matrix4x4.h"

class eventGameObjectTransform : public eventAbstract
{
public:
	eventGameObjectTransform(gameObject* _gameObject, matrix4x4 _matrix);
	~eventGameObjectTransform() override;

	void getState() override;
	eventAbstract* createCurrentState() override;

private:
	gameObject* m_game_object;
	//transform m_transform;
	matrix4x4 m_matrix;
};