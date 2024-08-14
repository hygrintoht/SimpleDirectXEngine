#pragma once

#include "iostream"
#include "cmath"

#include "matrix4x4.h"

class quaternion {
public:
    quaternion()
    {
    }
    quaternion(double w, double x, double y, double z) : m_w(w), m_x(x), m_y(y), m_z(z)
    {
    }
    
    double m_w = 1, m_x = 0, m_y = 0, m_z = 0;

    // operator overloads
    quaternion operator +(const quaternion& _quaternion) const
    {
        return quaternion(m_w + _quaternion.m_w, m_x + _quaternion.m_x, m_y + _quaternion.m_y, m_z + _quaternion.m_z);
    }

    quaternion operator -(const quaternion& _quaternion) const
    {
        return quaternion(m_w - _quaternion.m_w, m_x - _quaternion.m_x, m_y - _quaternion.m_y, m_z - _quaternion.m_z);
    }
    
    quaternion operator *(const quaternion& _quaternion) const
    {
        return quaternion
        (
            m_w * _quaternion.m_w - m_x * _quaternion.m_x - m_y * _quaternion.m_y - m_z * _quaternion.m_z,
            m_w * _quaternion.m_x + m_x * _quaternion.m_w + m_y * _quaternion.m_z - m_z * _quaternion.m_y,
            m_w * _quaternion.m_y - m_x * _quaternion.m_z + m_y * _quaternion.m_w + m_z * _quaternion.m_x,
            m_w * _quaternion.m_z + m_x * _quaternion.m_y - m_y * _quaternion.m_x + m_z * _quaternion.m_w
        );
    }
    
    // get value
    double magnitude() const
    {
        return std::sqrt(m_w * m_w + m_x * m_x + m_y * m_y + m_z * m_z);
    }

    quaternion normalize() const
    {
        double mag = magnitude();
        if (mag == 0.0) // magnitude can not be zero(divide by zero)
        {
            return *this;
        }
        return quaternion(m_w / mag, m_x / mag, m_y / mag, m_z / mag);
    }

    quaternion conjugate() const
	{
        return quaternion(m_w, -m_x, -m_y, -m_z);
    }
    
    quaternion rotateVector(const quaternion& vector) const
	{
        quaternion qv(0.0, vector.m_x, vector.m_y, vector.m_z);
        quaternion result = (*this) * qv * conjugate();
        return quaternion(0.0, result.m_x, result.m_y, result.m_z);
    }

    matrix4x4 toRotationMatrix() const
	{
        float xx = m_x * m_x;
        float yy = m_y * m_y;
        float zz = m_z * m_z;
        float xy = m_x * m_y;
        float xz = m_x * m_z;
        float yz = m_y * m_z;
        float wx = m_w * m_x;
        float wy = m_w * m_y;
        float wz = m_w * m_z;

        float mat[4][4] =
        {
            1 - 2 * (yy + zz),     2 * (xy - wz),     2 * (xz + wy), 0.0,
                2 * (xy + wz), 1 - 2 * (xx + zz),     2 * (yz - wx), 0.0,
        	    2 * (xz - wy),     2 * (yz + wx), 1 - 2 * (xx + yy), 0.0,
                          0.0,               0.0,               0.0, 1.0
        };

        matrix4x4 temp;
        memcpy(temp.m_mat, mat, 4 * 4 * sizeof(float));
        return temp;
    }
    // static functions
    static quaternion fromRotationMatrix(const matrix4x4& matrix)
	{
        double trace = matrix.getTrace();

        if (trace > 0.0) 
        {
            double s = 0.5 / std::sqrt(trace + 1.0);
            return quaternion
        	(                                        0.25 / s,
                (matrix.m_mat[2][1] - matrix.m_mat[1][2]) * s,
                (matrix.m_mat[0][2] - matrix.m_mat[2][0]) * s,
                (matrix.m_mat[1][0] - matrix.m_mat[0][1]) * s
            );
        }

        if (matrix.m_mat[0][0]> matrix.m_mat[1][1]&& matrix.m_mat[0][0]> matrix.m_mat[2][2]&& matrix.m_mat[0][0]> matrix.m_mat[3][3])
        {
            double s = 2.0 * std::sqrt(1.0 + matrix.m_mat[0][0]- matrix.m_mat[1][1]- matrix.m_mat[2][2]- matrix.m_mat[3][3]);
            return quaternion
            (
                (matrix.m_mat[2][1]- matrix.m_mat[1][2]) / s,
                                                    0.25 * s,
                (matrix.m_mat[0][1]+ matrix.m_mat[1][0]) / s,
                (matrix.m_mat[0][2]+ matrix.m_mat[2][0]) / s
            );
        }
        else if (matrix.m_mat[1][1]> matrix.m_mat[2][2]&& matrix.m_mat[1][1]> matrix.m_mat[3][3])
        {
            double s = 2.0 * std::sqrt(1.0 + matrix.m_mat[1][1]- matrix.m_mat[0][0]- matrix.m_mat[2][2]- matrix.m_mat[3][3]);
            return quaternion
        	(
                (matrix.m_mat[0][2]- matrix.m_mat[2][0]) / s,
                (matrix.m_mat[0][1]+ matrix.m_mat[1][0]) / s,
                                                    0.25 * s,
                (matrix.m_mat[1][2]+ matrix.m_mat[2][1]) / s
            );
        }
        else if (matrix.m_mat[2][2]> matrix.m_mat[3][3]) 
        {
            double s = 2.0 * std::sqrt(1.0 + matrix.m_mat[2][2]- matrix.m_mat[0][0]- matrix.m_mat[1][1]- matrix.m_mat[3][3]);
            return quaternion
        	(
                (matrix.m_mat[1][0]- matrix.m_mat[0][1]) / s,
                (matrix.m_mat[0][2]+ matrix.m_mat[2][0]) / s,
                (matrix.m_mat[1][2]+ matrix.m_mat[2][1]) / s,
                                                    0.25 * s
            );
        }
        else 
        {
            double s = 2.0 * std::sqrt(1.0 + matrix.m_mat[3][3]- matrix.m_mat[0][0]- matrix.m_mat[1][1]- matrix.m_mat[2][2]);
            return quaternion
        	(
                (matrix.m_mat[2][1]- matrix.m_mat[1][2]) / s,
                (matrix.m_mat[0][2]+ matrix.m_mat[2][0]) / s,
                (matrix.m_mat[1][2]+ matrix.m_mat[2][1]) / s,
                                                    0.25 * s
            );
        }
    }

    void rotateByEulerAngles(float roll, float pitch, float yaw) // roll pitch yaw
	{
        quaternion qx(std::cos(roll / 2), std::sin(roll / 2), 0.0, 0.0);
        quaternion qy(std::cos(pitch / 2), 0.0, std::sin(pitch / 2), 0.0);
        quaternion qz(std::cos(yaw / 2), 0.0, 0.0, std::sin(yaw / 2));

        *this = qx * qy * qz * (*this);
    }

    void rotateByEulerAngles(vector3 vector)
    {
        rotateByEulerAngles(vector.m_x, vector.m_y, vector.m_z);
    }

    static vector3 quaternionToEulerAngles(const quaternion& _quaternion) {
        vector3 out;

        double sinr_cosp = 2 * (_quaternion.m_w * _quaternion.m_x + _quaternion.m_y * _quaternion.m_z);
        double cosr_cosp = 1 - 2 * (_quaternion.m_x * _quaternion.m_x + _quaternion.m_y * _quaternion.m_y);
        out.m_x = std::atan2(sinr_cosp, cosr_cosp);

        double sinp = 2 * (_quaternion.m_w * _quaternion.m_y - _quaternion.m_z * _quaternion.m_x);
        if (std::abs(sinp) >= 1)
            out.m_y = std::copysign(3.1415f / 2, sinp);
        else
            out.m_y = std::asin(sinp);

        double siny_cosp = 2 * (_quaternion.m_w * _quaternion.m_z + _quaternion.m_x * _quaternion.m_y);
        double cosy_cosp = 1 - 2 * (_quaternion.m_y * _quaternion.m_y + _quaternion.m_z * _quaternion.m_z);
        out.m_z = std::atan2(siny_cosp, cosy_cosp);

        return out;
    }
};
