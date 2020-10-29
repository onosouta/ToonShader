#include "Math.h"

const Vector2 Vector2::Zero(0.0f, 0.0f);
const Vector2 Vector2::UnitX(1.0f, 0.0f);
const Vector2 Vector2::UnitY(0.0f, 1.0f);

Vector2 Vector2::Transform(const Vector2& _v, const Matrix3& _m, float _w /*= 1.0f*/)
{
	Vector2 v;
	v.x = _v.x * _m.matrix3[0][0] + _v.y * _m.matrix3[1][0] + 1.0f * _m.matrix3[2][0];
	v.y = _v.x * _m.matrix3[0][1] + _v.y * _m.matrix3[1][1] + 1.0f * _m.matrix3[2][1];
	return v;
}

const Vector3 Vector3::Zero(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitX(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::UnitY(0.0f, 1.0f, 0.0f);
const Vector3 Vector3::UnitZ(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Infinity(Math::infinity, Math::infinity, Math::infinity);

Vector3 Vector3::Transform(const Vector3& _v, const Matrix4& _m, float _w /*= 1.0f*/)
{
	Vector3 v;
	v.x = _v.x * _m.matrix4[0][0] + _v.y * _m.matrix4[1][0] + _v.z * _m.matrix4[2][0] + 1.0f * _m.matrix4[3][0];
	v.y = _v.x * _m.matrix4[0][1] + _v.y * _m.matrix4[1][1] + _v.z * _m.matrix4[2][1] + 1.0f * _m.matrix4[3][1];
	v.x = _v.x * _m.matrix4[0][2] + _v.y * _m.matrix4[1][2] + _v.z * _m.matrix4[2][2] + 1.0f * _m.matrix4[3][2];
	return v;
}

Vector3 Vector3::Transform(const Vector3& _v, const Quaternion& _q)
{
	Vector3 q_v(_q.x, _q.y, _q.z);
	Vector3 v = _v;
	v += 2.0f * Vector3::Cross(q_v, Vector3::Cross(q_v, _v) + _q.w * _v);
	return v;
}

Vector3 Vector3::ApplyMatrix4(const Vector3& _v, const Matrix4& _m, float _w /*= 1.0f*/)
{
	Vector3 v;
	v.x = _v.x * _m.matrix4[0][0] + _v.y * _m.matrix4[1][0] + _v.z * _m.matrix4[2][0] + _w * _m.matrix4[3][0];
	v.y = _v.x * _m.matrix4[0][1] + _v.y * _m.matrix4[1][1] + _v.z * _m.matrix4[2][1] + _w * _m.matrix4[3][1];
	v.z = _v.x * _m.matrix4[0][2] + _v.y * _m.matrix4[1][2] + _v.z * _m.matrix4[2][2] + _w * _m.matrix4[3][2];
	float w = _v.x * _m.matrix4[0][3] + _v.y * _m.matrix4[1][3] + _v.z * _m.matrix4[2][3] + _w * _m.matrix4[3][3];

	if (!Math::NearZero(Math::Abs(w)))
	{
		w = 1.0f / w;
		v *= w;
	}
	return v;
}

static float matrix3_identity[3][3] =
{
	{ 1.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f },
};
const Matrix3 Matrix3::Identity(matrix3_identity);

static float matrix4_identity[4][4] =
{
	{ 1.0f, 0.0f, 0.0f, 0.0f },
	{ 0.0f, 1.0f, 0.0f, 0.0f },
	{ 0.0f, 0.0f, 1.0f, 0.0f },
	{ 0.0f, 0.0f, 0.0f, 1.0f },
};
const Matrix4 Matrix4::Identity(matrix4_identity);

//逆行列
void Matrix4::Invert()
{
	float tmp[12];
	float src[16];//入力配列
	float dst[16];//出力配列
	float det;

	src[0]  = matrix4[0][0];
	src[4]  = matrix4[0][1];
	src[8]  = matrix4[0][2];
	src[12] = matrix4[0][3];

	src[1]  = matrix4[1][0];
	src[5]  = matrix4[1][1];
	src[9]  = matrix4[1][2];
	src[13] = matrix4[1][3];

	src[2]  = matrix4[2][0];
	src[6]  = matrix4[2][1];
	src[10] = matrix4[2][2];
	src[14] = matrix4[2][3];

	src[3]  = matrix4[3][0];
	src[7]  = matrix4[3][1];
	src[11] = matrix4[3][2];
	src[15] = matrix4[3][3];

	tmp[0]  = src[10] * src[15];
	tmp[1]  = src[11] * src[14];
	tmp[2]  = src[9]  * src[15];
	tmp[3]  = src[11] * src[13];
	tmp[4]  = src[9]  * src[14];
	tmp[5]  = src[10] * src[13];
	tmp[6]  = src[8]  * src[15];
	tmp[7]  = src[11] * src[12];
	tmp[8]  = src[8]  * src[14];
	tmp[9]  = src[10] * src[12];
	tmp[10] = src[8]  * src[13];
	tmp[11] = src[9]  * src[12];

	dst[0]  = tmp[0] * src[5] + tmp[3] * src[6] + tmp[4]  * src[7];
	dst[0] -= tmp[1] * src[5] + tmp[2] * src[6] + tmp[5]  * src[7];
	dst[1]  = tmp[1] * src[4] + tmp[6] * src[6] + tmp[9]  * src[7];
	dst[1] -= tmp[0] * src[4] + tmp[7] * src[6] + tmp[8]  * src[7];
	dst[2]  = tmp[2] * src[4] + tmp[7] * src[5] + tmp[10] * src[7];
	dst[2] -= tmp[3] * src[4] + tmp[6] * src[5] + tmp[11] * src[7];
	dst[3]  = tmp[5] * src[4] + tmp[8] * src[5] + tmp[11] * src[6];
	dst[3] -= tmp[4] * src[4] + tmp[9] * src[5] + tmp[10] * src[6];
	dst[4]  = tmp[1] * src[1] + tmp[2] * src[2] + tmp[5]  * src[3];
	dst[4] -= tmp[0] * src[1] + tmp[3] * src[2] + tmp[4]  * src[3];
	dst[5]  = tmp[0] * src[0] + tmp[7] * src[2] + tmp[8]  * src[3];
	dst[5] -= tmp[1] * src[0] + tmp[6] * src[2] + tmp[9]  * src[3];
	dst[6]  = tmp[3] * src[0] + tmp[6] * src[1] + tmp[11] * src[3];
	dst[6] -= tmp[2] * src[0] + tmp[7] * src[1] + tmp[10] * src[3];
	dst[7]  = tmp[4] * src[0] + tmp[9] * src[1] + tmp[10] * src[2];
	dst[7] -= tmp[5] * src[0] + tmp[8] * src[1] + tmp[11] * src[2];

	tmp[0]  = src[2] * src[7];
	tmp[1]  = src[3] * src[6];
	tmp[2]  = src[1] * src[7];
	tmp[3]  = src[3] * src[5];
	tmp[4]  = src[1] * src[6];
	tmp[5]  = src[2] * src[5];
	tmp[6]  = src[0] * src[7];
	tmp[7]  = src[3] * src[4];
	tmp[8]  = src[0] * src[6];
	tmp[9]  = src[2] * src[4];
	tmp[10] = src[0] * src[5];
	tmp[11] = src[1] * src[4];

	dst[8]   = tmp[0]  * src[13] + tmp[3]  * src[14] + tmp[4]  * src[15];
	dst[8]  -= tmp[1]  * src[13] + tmp[2]  * src[14] + tmp[5]  * src[15];
	dst[9]   = tmp[1]  * src[12] + tmp[6]  * src[14] + tmp[9]  * src[15];
	dst[9]  -= tmp[0]  * src[12] + tmp[7]  * src[14] + tmp[8]  * src[15];
	dst[10]  = tmp[2]  * src[12] + tmp[7]  * src[13] + tmp[10] * src[15];
	dst[10] -= tmp[3]  * src[12] + tmp[6]  * src[13] + tmp[11] * src[15];
	dst[11]  = tmp[5]  * src[12] + tmp[8]  * src[13] + tmp[11] * src[14];
	dst[11] -= tmp[4]  * src[12] + tmp[9]  * src[13] + tmp[10] * src[14];
	dst[12]  = tmp[2]  * src[10] + tmp[5]  * src[11] + tmp[1]  * src[9];
	dst[12] -= tmp[4]  * src[11] + tmp[0]  * src[9]  + tmp[3]  * src[10];
	dst[13]  = tmp[8]  * src[11] + tmp[0]  * src[8]  + tmp[7]  * src[10];
	dst[13] -= tmp[6]  * src[10] + tmp[9]  * src[11] + tmp[1]  * src[8];
	dst[14]  = tmp[6]  * src[9]  + tmp[11] * src[11] + tmp[3]  * src[8];
	dst[14] -= tmp[10] * src[11] + tmp[2]  * src[8]  + tmp[7]  * src[9];
	dst[15]  = tmp[10] * src[10] + tmp[4]  * src[8]  + tmp[9]  * src[9];
	dst[15] -= tmp[8]  * src[9]  + tmp[11] * src[10] + tmp[5]  * src[8];

	det = src[0] * dst[0] + src[1] * dst[1] + src[2] * dst[2] + src[3] * dst[3];

	det = 1 / det;
	for (int j = 0; j < 16; j++)
	{
		dst[j] *= det;
	}

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matrix4[i][j] = dst[i * 4 + j];
		}
	}
}

Matrix4 Matrix4::CreateRotation(const class Quaternion& _q)
{
	float m[4][4];

	m[0][0] = 1.0f - 2.0f * _q.y * _q.y - 2.0f * _q.z * _q.z;
	m[0][1] = 2.0f * _q.x * _q.y + 2.0f * _q.w * _q.z;
	m[0][2] = 2.0f * _q.x * _q.z - 2.0f * _q.w * _q.y;
	m[0][3] = 0.0f;

	m[1][0] = 2.0f * _q.x * _q.y - 2.0f * _q.w * _q.z;
	m[1][1] = 1.0f - 2.0f * _q.x * _q.x - 2.0f * _q.z * _q.z;
	m[1][2] = 2.0f * _q.y * _q.z + 2.0f * _q.w * _q.x;
	m[1][3] = 0.0f;

	m[2][0] = 2.0f * _q.x * _q.z + 2.0f * _q.w * _q.y;
	m[2][1] = 2.0f * _q.y * _q.z - 2.0f * _q.w * _q.x;
	m[2][2] = 1.0f - 2.0f * _q.x * _q.x - 2.0f * _q.y * _q.y;
	m[2][3] = 0.0f;

	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;

	return Matrix4(m);
}

const Quaternion Quaternion::Identity(0.0f, 0.0f, 0.0f, 1.0f);