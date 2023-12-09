#pragma once
#include "vector3.h"
#include "quaternion.h"
#include "matrix4x4.h"

class transform
{
public:
	matrix4x4 m_transform;

	vector3 m_position;
	vector3 m_scale;
	quaternion m_rotation;
	vector3 m_euler_angles;

	static transform decomposeMatrix(matrix4x4 matrix)
	{
		transform out;

		out.m_position = matrix.getTranslation(); // position of matrix
		out.m_scale = matrix.getScale(); // scale of matrix
		/*
		// create a scale matrix
		matrix4x4 scaleMatrix;
		scaleMatrix.setIdentity();
		scaleMatrix.setScale(out.m_scale);
		scaleMatrix.inverse(); // get the inverse

		matrix4x4 unscaledMatrix = matrix * scaleMatrix;
		*/
		out.m_rotation = quaternion::fromRotationMatrix(matrix);
		out.m_euler_angles = quaternion::quaternionToEulerAngles(out.m_rotation);

		return out;
	}
};