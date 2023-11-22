#pragma once

#include <memory>
#include "vector3.h"
#include "vector4.h"

class matrix4x4
{
public:
	matrix4x4()
	{
	}

	~matrix4x4()
	{
	}
	
	float m_mat[4][4] = {};
	// operator overloads
	matrix4x4 operator * (const matrix4x4& matrix)
	{
		matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					m_mat[i][0] * matrix.m_mat[0][j]
					+ m_mat[i][1] * matrix.m_mat[1][j]
					+ m_mat[i][2] * matrix.m_mat[2][j]
					+ m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		return out;
	}

	void operator *= (const matrix4x4& matrix)
	{
		matrix4x4 out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				out.m_mat[i][j] =
					  m_mat[i][0] * matrix.m_mat[0][j]
					+ m_mat[i][1] * matrix.m_mat[1][j]
					+ m_mat[i][2] * matrix.m_mat[2][j]
					+ m_mat[i][3] * matrix.m_mat[3][j];
			}
		}
		setMatrix(out);
	}
	// set functions
	void setZero()
	{
		memset(m_mat, 0, sizeof(float) * 16);
	}

	void setIdentity()
	{
		memset(m_mat, 0, sizeof(float) * 16);
		m_mat[0][0] = 1;
		m_mat[1][1] = 1;
		m_mat[2][2] = 1;
		m_mat[3][3] = 1;
	}

	void setMatrix(const matrix4x4& matrix)
	{
		memcpy(m_mat, matrix.m_mat, sizeof(float) * 16);
	}
	// manipulations
	void setTranslation(const vector3& translation)
	{
		m_mat[3][0] = translation.m_x;
		m_mat[3][1] = translation.m_y;
		m_mat[3][2] = translation.m_z;
	}

	void setScale(const vector3& scale)
	{
		m_mat[0][0] = scale.m_x;
		m_mat[1][1] = scale.m_y;
		m_mat[2][2] = scale.m_z;
	}

	void setRotationX(float x)
	{
		m_mat[1][1] = cos(x);
		m_mat[1][2] = sin(x);
		m_mat[2][1] = -sin(x);
		m_mat[2][2] = cos(x);
	}

	void setRotationY(float y)
	{
		m_mat[0][0] = cos(y);
		m_mat[0][2] = -sin(y);
		m_mat[2][0] = sin(y);
		m_mat[2][2] = cos(y);
	}

	void setRotationZ(float z)
	{
		m_mat[0][0] = cos(z);
		m_mat[0][1] = sin(z);
		m_mat[1][0] = -sin(z);
		m_mat[1][1] = cos(z);
	}

	void setRotation(const vector3& rotation) //note: xyz rotation
	{
		float x = rotation.m_x;
		float y = rotation.m_y;
		float z = rotation.m_z;

		m_mat[0][0] = cos(y) * cos(z);
		m_mat[0][1] = cos(y) * sin(z);
		m_mat[0][2] = sin(y) * -1;
		m_mat[1][0] = sin(x) * sin(y) * cos(z) - cos(x) * sin(z);
		m_mat[1][1] = sin(x) * sin(y) * sin(z) + cos(x) * cos(z);
		m_mat[1][2] = sin(x) * cos(y);
		m_mat[2][0] = cos(x) * sin(y) * cos(z) + sin(x) * sin(z);
		m_mat[2][1] = cos(x) * sin(y) * sin(z) - sin(x) * cos(z);
		m_mat[2][2] = cos(x) * cos(y);
	}

	void inverse()
	{
		matrix4x4 out;
		vector4 v;
		float determinant = 0.0f;

		determinant = this->getDeterminant();
		if (!determinant) return;
		for (int i = 0; i < 4; i++)
		{
			vector4 vec[3];
			for (int j = 0; j < 4; j++)
			{
				if (j != i)
				{
					int a = j;
					if (j > i) a = a - 1;
					vec[a].m_x = (this->m_mat[j][0]);
					vec[a].m_y = (this->m_mat[j][1]);
					vec[a].m_z = (this->m_mat[j][2]);
					vec[a].m_w = (this->m_mat[j][3]);
				}
			}
			v.cross(vec[0], vec[1], vec[2]);

			out.m_mat[0][i] = pow(-1.0f, i) * v.m_x / determinant;
			out.m_mat[1][i] = pow(-1.0f, i) * v.m_y / determinant;
			out.m_mat[2][i] = pow(-1.0f, i) * v.m_z / determinant;
			out.m_mat[3][i] = pow(-1.0f, i) * v.m_w / determinant;
		}

		this->setMatrix(out);
	}

	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
	{
		float yscale = 1.0f / tan(fov / 2.0f);
		float xscale = yscale / aspect;
		m_mat[0][0] = xscale;
		m_mat[1][1] = yscale;
		m_mat[2][2] = zfar / (zfar - znear);
		m_mat[2][3] = 1.0f;
		m_mat[3][2] = (-znear * zfar) / (zfar - znear);
	}

	void setOrthoLH(float width, float height, float near_plane, float far_plane)
	{
		setIdentity();
		m_mat[0][0] = 2.0f / width;
		m_mat[1][1] = 2.0f / height;
		m_mat[2][2] = 1.0f / (far_plane - near_plane);
		m_mat[3][2] = -(near_plane / (far_plane - near_plane));
	}
	// get value
	float getDeterminant() const
	{
		vector4 v1 = vector4(this->m_mat[0][0], this->m_mat[1][0], this->m_mat[2][0], this->m_mat[3][0]);
		vector4 v2 = vector4(this->m_mat[0][1], this->m_mat[1][1], this->m_mat[2][1], this->m_mat[3][1]);
		vector4 v3 = vector4(this->m_mat[0][2], this->m_mat[1][2], this->m_mat[2][2], this->m_mat[3][2]);

		vector4 minor;
		minor.cross(v1, v2, v3);
		float determinant =
			  this->m_mat[0][3] * minor.m_x
			+ this->m_mat[1][3] * minor.m_y
			+ this->m_mat[2][3] * minor.m_z
			+ this->m_mat[3][3] * minor.m_w;
		determinant *= -1;

		return determinant;
	}

	float getTrace() const
	{
		return m_mat[0][0] + m_mat[1][1] + m_mat[2][2] + m_mat[3][3];
	}
	// forward axis
	vector3 getZDirection() const
	{
		return vector3(m_mat[2][0], m_mat[2][1], m_mat[2][2]);
	}
	// up axis
	vector3 getYDirection() const
	{
		return vector3(m_mat[1][0], m_mat[1][1], m_mat[1][2]);
	}
	// left axis
	vector3 getXDirection() const
	{
		return vector3(m_mat[0][0], m_mat[0][1], m_mat[0][2]);
	}

	vector3 getTranslation() const
	{
		return vector3(m_mat[3][0], m_mat[3][1], m_mat[3][2]);
	}

	vector3 getScale() const
	{
		return vector3(m_mat[0][0], m_mat[1][1], m_mat[2][2]);
	}

	/*
	vector3 getRotation()
	{
		return vector3();
	}
	*/
	
	// static functions
	static matrix4x4 zeroMatrix()
	{
		matrix4x4 temp;
		temp.setZero();
		return temp;
	}

	static matrix4x4 identityMatrix()
	{
		matrix4x4 temp;
		temp.setIdentity();
		return temp;
	}

	void setMatrixFromGLMatrix(float matrix[16])
	{
		matrix4x4 temp;
		//matrix4x4 scale;
		//scale.setIdentity();
		//scale.setScale(this->getScale());
		
		temp.m_mat[0][0] = matrix[0];
		temp.m_mat[0][1] = matrix[1];
		temp.m_mat[0][2] = matrix[2];
		temp.m_mat[0][3] = matrix[3];
		temp.m_mat[1][0] = matrix[4];
		temp.m_mat[1][1] = matrix[5];
		temp.m_mat[1][2] = matrix[6];
		temp.m_mat[1][3] = matrix[7];
		temp.m_mat[2][0] = matrix[8];
		temp.m_mat[2][1] = matrix[9];
		temp.m_mat[2][2] = matrix[10];
		temp.m_mat[2][3] = matrix[11];
		temp.m_mat[3][0] = matrix[12];
		temp.m_mat[3][1] = matrix[13];
		temp.m_mat[3][2] = matrix[14];
		temp.m_mat[3][3] = matrix[15];

		*this = temp;

		//*this *= scale;

		//*this *= temp;
		/*
		matrix4x4 newMat = temp;
		matrix4x4 scale;
		scale.setIdentity();
		scale.setScale(this->getScale());
		matrix4x4 trans;
		trans.setIdentity();
		trans.setTranslation(this->getTranslation());
		*this = scale.multiplyTo(trans.multiplyTo(newMat));
		*/

	}

	matrix4x4 getGLMatrixFromMatrix()
	{
		/*
		float matrix[16];
		matrix[0] = 1.0f;//m_mat[0][0];
		matrix[1] = m_mat[0][1];
		matrix[2] = m_mat[0][2];
		matrix[3] = m_mat[0][3];
		matrix[4] = m_mat[1][0];
		matrix[5] = 1.0f;//m_mat[1][1];
		matrix[6] = m_mat[1][2];
		matrix[7] = m_mat[1][3];
		matrix[8] = m_mat[2][0];
		matrix[9] = m_mat[2][1];
		matrix[10] = 1.0f;//m_mat[2][2];
		matrix[11] = m_mat[2][3];
		matrix[12] = m_mat[3][0];
		matrix[13] = m_mat[3][1];
		matrix[14] = m_mat[3][2];
		matrix[15] = 1.0f;//m_mat[3][3];

		return matrix;
		*/

		matrix4x4 temp = *this;
		temp.m_mat[0][0] = 1.0f;
		temp.m_mat[1][1] = 1.0f;
		temp.m_mat[2][2] = 1.0f;
		temp.m_mat[3][3] = 1.0f;

		return temp;
		/*
		matrix4x4 allMatrix, translationMatrix, scaleMatrix;
		allMatrix.setIdentity();
		translationMatrix.setIdentity();
		translationMatrix.setTranslation(this->getLocalPosition());
		scaleMatrix.setScale(vector3(1.0f,1.0f,1.0f)); //physics 3D only accepts uniform scale for rigidbody
		vector3 rotation = this->get
		Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.getX());
		Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.getY());
		Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.getZ());
		*/
	}
	matrix4x4 multiplyTo(matrix4x4 matrix)
	{
		matrix4x4 out;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				out.m_mat[i][j] =
					this->m_mat[i][0] * matrix.m_mat[0][j] + this->m_mat[i][1] * matrix.m_mat[1][j] +
					this->m_mat[i][2] * matrix.m_mat[2][j] + this->m_mat[i][3] * matrix.m_mat[3][j];
			}
		}

		return out;
	}
};