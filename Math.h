#pragma once
#include <limits>

namespace Math
{
	const float pi = 3.14159265f;

	const float infinity = std::numeric_limits<float>::infinity();
	const float neg_infinity = -infinity;

	inline float ToRadians(float _d)
	{
		return _d * pi / 180.0f;
	}

	inline float ToDegrees(float _r)
	{
		return _r * 180.0f / pi;
	}

	inline bool NearZero(float _v)
	{
		if (fabs(_v) < 0.001f)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	template <typename T>
	T Max(const T& _a, const T& _b)
	{
		if (_a > _b)
		{
			return _a;
		}
		else
		{
			return _b;
		}
	}

	template <typename T>
	T Min(const T& _a, const T& _b)
	{
		if (_a < _b)
		{
			return _a;
		}
		else
		{
			return _b;
		}
	}

	template <typename T>
	T Clamp(const T& _v, const T& _min, const T& _max)
	{
		return Min(_max, Max(_min, _v));
	}

	inline float Abs(float _v)
	{
		return fabs(_v);
	}

	inline float Sqrt(float _v)
	{
		return sqrtf(_v);
	}

	inline float Sin(float _a)
	{
		return sinf(_a);
	}

	inline float Cos(float _a)
	{
		return cosf(_a);
	}

	inline float Tan(float _a)
	{
		return tanf(_a);
	}

	inline float Asin(float _a)
	{
		return asinf(_a);
	}

	inline float Acos(float _a)
	{
		return acosf(_a);
	}

	inline float Atan(float _a)
	{
		return atanf(_a);
	}

	inline float Atan2(float _y, float _x)
	{
		return atan2f(_y, _x);
	}

	inline float Cot(float _a)
	{
		return 1.0f / Tan(_a);
	}

	inline float Lerp(float _a, float _b, float _t)
	{
		return _a + _t * (_b - _a);
	}
}

//2次元ベクトル
class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		,y(0.0f)
	{}

	explicit Vector2(float _x, float _y)
		:x(_x)
		,y(_y)
	{}

	const float* GetPointer() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	friend Vector2 operator+(const Vector2& _a, const Vector2& _b)
	{
		return Vector2(_a.x + _b.x, _a.y + _b.y);
	}

	friend Vector2 operator-(const Vector2& _a, const Vector2& _b)
	{
		return Vector2(_a.x - _b.x, _a.y - _b.y);
	}

	friend Vector2 operator*(const Vector2& _a, const Vector2& _b)
	{
		return Vector2(_a.x * _b.x, _a.y * _b.y);
	}

	friend Vector2 operator*(const Vector2& _v, float _s)
	{
		return Vector2(_v.x * _s, _v.y * _s);
	}

	friend Vector2 operator*(float _s, const Vector2& _v)
	{
		return Vector2(_s * _v.x, _s * _v.y);
	}

	Vector2& operator+=(const Vector2& _v)
	{
		x += _v.x;
		y += _v.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& _v)
	{
		x -= _v.x;
		y -= _v.y;
		return *this;
	}

	Vector2& operator*=(float _s)
	{
		x *= _s;
		y *= _s;
		return *this;
	}

	float LengthSq() const
	{
		return x * x + y * y;
	}

	float Length() const
	{
		return Math::Sqrt(LengthSq());
	}

	void Normalize()
	{
		float l = Length();
		x /= l;
		y /= l;
	}

	static Vector2 Normalize(const Vector2 _v)
	{
		Vector2 v = _v;
		v.Normalize();
		return v;
	}

	static float Dot(const Vector2& _a, const Vector2& _b)
	{
		return _a.x * _b.x + _a.y + _b.y;
	}

	static float Cross(const Vector2& _a, const Vector2& _b)
	{
		return _a.x * _b.y - _a.y * _b.x;
	}

	static Vector2 Lerp(const Vector2& _a, const Vector2& _b, float _t)
	{
		return Vector2(_a + _t * (_b - _a));
	}

	static Vector2 Reflect(const Vector2& _v, const Vector2& _n)
	{
		return _v - 2.0f * Vector2::Dot(_v, _n) * _n;
	}

	static Vector2 Transform(const Vector2& _v, const class Matrix3& _m, float _w = 1.0f);

	static const Vector2 Zero;
	static const Vector2 UnitX;
	static const Vector2 UnitY;
};

//3次元ベクトル
class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
		:x(0.0f)
		,y(0.0f)
		,z(0.0f)
	{}

	explicit Vector3(float _x, float _y, float _z)
		:x(_x)
		,y(_y)
		,z(_z)
	{}

	const float* GetPointer() const
	{
		return reinterpret_cast<const float*>(&x);
	}

	friend Vector3 operator+(const Vector3& _a, const Vector3& _b)
	{
		return Vector3(_a.x + _b.x, _a.y + _b.y, _a.z + _b.z);
	}

	friend Vector3 operator-(const Vector3& _v)
	{
		return Vector3(-_v.x, -_v.y, _v.z);
	}
	friend Vector3 operator-(const Vector3& _a, const Vector3& _b)
	{
		return Vector3(_a.x - _b.x, _a.y - _b.y, _a.z - _b.z);
	}

	friend Vector3 operator*(const Vector3& _a, const Vector3& _b)
	{
		return Vector3(_a.x * _b.x, _a.y * _b.y, _a.z * _b.z);
	}

	friend Vector3 operator*(const Vector3& _v, float _s)
	{
		return Vector3(_v.x * _s, _v.y * _s, _v.z * _s);
	}

	friend Vector3 operator*(float s, const Vector3& _v)
	{
		return Vector3(s * _v.x, s * _v.y, s * _v.z);
	}

	Vector3& operator+=(const Vector3& _v)
	{
		x += _v.x;
		y += _v.y;
		z += _v.z;
		return *this;
	}

	Vector3& operator-=(const Vector3& _v)
	{
		x -= _v.x;
		y -= _v.y;
		z -= _v.z;
		return *this;
	}

	Vector3& operator*=(float _s)
	{
		x *= _s;
		y *= _s;
		z *= _s;
		return *this;
	}

	Vector3& operator*=(Vector3 _v)
	{
		x *= _v.x;
		y *= _v.y;
		z *= _v.z;
		return *this;
	}

	float LengthSqare() const
	{
		return x * x + y * y + z * z;
	}

	float Length()
	{
		return Math::Sqrt(LengthSqare());
	}

	void Normalize()
	{
		float l = Length();
		x /= l;
		y /= l;
		z /= l;
	}

	static Vector3 Normalize(const Vector3& _v)
	{
		Vector3 v = _v;
		v.Normalize();
		return v;
	}

	static float Dot(const Vector3& _a, const Vector3& _b)
	{
		return (_a.x * _b.x + _a.y * _b.y + _a.z * _b.z);
	}

	static Vector3 Cross(const Vector3& _a, const Vector3& _b)
	{
		Vector3 v;
		v.x = _a.y * _b.z - _a.z * _b.y;
		v.y = _a.z * _b.x - _a.x * _b.z;
		v.z = _a.x * _b.y - _a.y * _b.x;
		return v;
	}

	static Vector3 Lerp(const Vector3& _a, const Vector3& _b, float _t)
	{
		return Vector3(_a - _t * (_b - _a));
	}

	static Vector3 Reflect(const Vector3& _v, const Vector3& _n)
	{
		return _v - 2.0f * Vector3::Dot(_v, _n) * _n;
	}

	static Vector3 Transform(const Vector3& _v, const class Matrix4& _m, float _w = 1.0f);
	static Vector3 Transform(const Vector3& _v, const class Quaternion& _q);

	static Vector3 ApplyMatrix4(const Vector3& _v, const Matrix4& _m, float _w = 1.0f);

	const static Vector3 Zero;
	const static Vector3 UnitX;
	const static Vector3 UnitY;
	const static Vector3 UnitZ;
	static const Vector3 Infinity;
};

//行列 3×3
class Matrix3
{
public:
	float matrix3[3][3];

	Matrix3()
	{
		*this = Matrix3::Identity;
	}

	explicit Matrix3(float _matrix3[3][3])
	{
		memcpy(matrix3, _matrix3, 9 * sizeof(float));
	}

	friend Matrix3 operator*(const Matrix3& _a, const Matrix3& _b)
	{
		Matrix3 m;

		//0
		m.matrix3[0][0] =
			_a.matrix3[0][0] * _b.matrix3[0][0] +
			_a.matrix3[0][1] * _b.matrix3[1][0] +
			_a.matrix3[0][2] * _b.matrix3[2][0];

		m.matrix3[0][1] =
			_a.matrix3[0][0] * _b.matrix3[0][1] +
			_a.matrix3[0][1] * _b.matrix3[1][1] +
			_a.matrix3[0][2] * _b.matrix3[2][1];

		m.matrix3[0][2] =
			_a.matrix3[0][0] * _b.matrix3[0][2] +
			_a.matrix3[0][1] * _b.matrix3[1][2] +
			_a.matrix3[0][2] * _b.matrix3[2][2];

		//1
		m.matrix3[1][0] =
			_a.matrix3[1][0] * _b.matrix3[0][0] +
			_a.matrix3[1][1] * _b.matrix3[1][0] +
			_a.matrix3[1][2] * _b.matrix3[2][0];

		m.matrix3[1][1] =
			_a.matrix3[1][0] * _b.matrix3[0][1] +
			_a.matrix3[1][1] * _b.matrix3[1][1] +
			_a.matrix3[1][2] * _b.matrix3[2][1];

		m.matrix3[1][2] =
			_a.matrix3[1][0] * _b.matrix3[0][2] +
			_a.matrix3[1][1] * _b.matrix3[1][2] +
			_a.matrix3[1][2] * _b.matrix3[2][2];

		//2
		m.matrix3[2][0] =
			_a.matrix3[2][0] * _b.matrix3[0][0] +
			_a.matrix3[2][1] * _b.matrix3[1][0] +
			_a.matrix3[2][2] * _b.matrix3[2][0];

		m.matrix3[2][1] =
			_a.matrix3[2][0] * _b.matrix3[0][1] +
			_a.matrix3[2][1] * _b.matrix3[1][1] +
			_a.matrix3[2][2] * _b.matrix3[2][1];

		m.matrix3[2][2] =
			_a.matrix3[2][0] * _b.matrix3[0][2] +
			_a.matrix3[2][1] * _b.matrix3[1][2] +
			_a.matrix3[2][2] * _b.matrix3[2][2];

		return m;
	}

	Matrix3& operator*=(const Matrix3& _m)
	{
		*this = *this * _m;
		return *this;
	}

	static Matrix3 CreateScale(float _x, float _y)
	{
		float m[3][3] =
		{
			{ _x,   0.0f, 0.0f },
			{ 0.0f, _y,   0.0f },
			{ 0.0f, 0.0f, 1.0f },
		};
		return Matrix3(m);
	}

	static Matrix3 CreateScale(const Vector2& _v)
	{
		return CreateScale(_v.x, _v.y);
	}

	static Matrix3 CreateScale(float _s)
	{
		return CreateScale(_s, _s);
	}

	static Matrix3 CreateRotation(float _a)
	{
		float m[3][3] =
		{
			{ Math::Cos(_a),  Math::Sin(_a), 0.0f },
			{ -Math::Sin(_a), Math::Cos(_a), 0.0f },
			{ 0.0f,           0.0f,          1.0f },
		};
		return Matrix3(m);
	}

	static Matrix3 CreateTranslation(const Vector2& _v)
	{
		float m[3][3] =
		{
			{ 1.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f },
			{ _v.x, _v.y, 1.0f },
		};
		return Matrix3(m);
	}

	static const Matrix3 Identity;
};

//行列 4×4
class Matrix4
{
public:
	float matrix4[4][4];

	Matrix4()
	{
		*this = Matrix4::Identity;
	}

	explicit Matrix4(float _matrix4[4][4])
	{
		memcpy(matrix4, _matrix4, 16 * sizeof(float));
	}

	const float* GetPointer() const
	{
		return reinterpret_cast<const float*>(&matrix4[0][0]);
	}

	friend Matrix4 operator*(const Matrix4& _a, const Matrix4& _b)
	{
		Matrix4 m;

		//0
		m.matrix4[0][0] =
			_a.matrix4[0][0] * _b.matrix4[0][0] +
			_a.matrix4[0][1] * _b.matrix4[1][0] +
			_a.matrix4[0][2] * _b.matrix4[2][0] +
			_a.matrix4[0][3] * _b.matrix4[3][0];

		m.matrix4[0][1] =
			_a.matrix4[0][0] * _b.matrix4[0][1] +
			_a.matrix4[0][1] * _b.matrix4[1][1] +
			_a.matrix4[0][2] * _b.matrix4[2][1] +
			_a.matrix4[0][3] * _b.matrix4[3][1];

		m.matrix4[0][2] =
			_a.matrix4[0][0] * _b.matrix4[0][2] +
			_a.matrix4[0][1] * _b.matrix4[1][2] +
			_a.matrix4[0][2] * _b.matrix4[2][2] +
			_a.matrix4[0][3] * _b.matrix4[3][2];

		m.matrix4[0][3] =
			_a.matrix4[0][0] * _b.matrix4[0][3] +
			_a.matrix4[0][1] * _b.matrix4[1][3] +
			_a.matrix4[0][2] * _b.matrix4[2][3] +
			_a.matrix4[0][3] * _b.matrix4[3][3];

		//1
		m.matrix4[1][0] =
			_a.matrix4[1][0] * _b.matrix4[0][0] +
			_a.matrix4[1][1] * _b.matrix4[1][0] +
			_a.matrix4[1][2] * _b.matrix4[2][0] +
			_a.matrix4[1][3] * _b.matrix4[3][0];

		m.matrix4[1][1] =
			_a.matrix4[1][0] * _b.matrix4[0][1] +
			_a.matrix4[1][1] * _b.matrix4[1][1] +
			_a.matrix4[1][2] * _b.matrix4[2][1] +
			_a.matrix4[1][3] * _b.matrix4[3][1];

		m.matrix4[1][2] =
			_a.matrix4[1][0] * _b.matrix4[0][2] +
			_a.matrix4[1][1] * _b.matrix4[1][2] +
			_a.matrix4[1][2] * _b.matrix4[2][2] +
			_a.matrix4[1][3] * _b.matrix4[3][2];

		m.matrix4[1][3] =
			_a.matrix4[1][0] * _b.matrix4[0][3] +
			_a.matrix4[1][1] * _b.matrix4[1][3] +
			_a.matrix4[1][2] * _b.matrix4[2][3] +
			_a.matrix4[1][3] * _b.matrix4[3][3];

		//2
		m.matrix4[2][0] =
			_a.matrix4[2][0] * _b.matrix4[0][0] +
			_a.matrix4[2][1] * _b.matrix4[1][0] +
			_a.matrix4[2][2] * _b.matrix4[2][0] +
			_a.matrix4[2][3] * _b.matrix4[3][0];

		m.matrix4[2][1] =
			_a.matrix4[2][0] * _b.matrix4[0][1] +
			_a.matrix4[2][1] * _b.matrix4[1][1] +
			_a.matrix4[2][2] * _b.matrix4[2][1] +
			_a.matrix4[2][3] * _b.matrix4[3][1];

		m.matrix4[2][2] =
			_a.matrix4[2][0] * _b.matrix4[0][2] +
			_a.matrix4[2][1] * _b.matrix4[1][2] +
			_a.matrix4[2][2] * _b.matrix4[2][2] +
			_a.matrix4[2][3] * _b.matrix4[3][2];

		m.matrix4[2][3] =
			_a.matrix4[2][0] * _b.matrix4[0][3] +
			_a.matrix4[2][1] * _b.matrix4[1][3] +
			_a.matrix4[2][2] * _b.matrix4[2][3] +
			_a.matrix4[2][3] * _b.matrix4[3][3];

		//3
		m.matrix4[3][0] =
			_a.matrix4[3][0] * _b.matrix4[0][0] +
			_a.matrix4[3][1] * _b.matrix4[1][0] +
			_a.matrix4[3][2] * _b.matrix4[2][0] +
			_a.matrix4[3][3] * _b.matrix4[3][0];

		m.matrix4[3][1] =
			_a.matrix4[3][0] * _b.matrix4[0][1] +
			_a.matrix4[3][1] * _b.matrix4[1][1] +
			_a.matrix4[3][2] * _b.matrix4[2][1] +
			_a.matrix4[3][3] * _b.matrix4[3][1];

		m.matrix4[3][2] =
			_a.matrix4[3][0] * _b.matrix4[0][2] +
			_a.matrix4[3][1] * _b.matrix4[1][2] +
			_a.matrix4[3][2] * _b.matrix4[2][2] +
			_a.matrix4[3][3] * _b.matrix4[3][2];

		m.matrix4[3][3] =
			_a.matrix4[3][0] * _b.matrix4[0][3] +
			_a.matrix4[3][1] * _b.matrix4[1][3] +
			_a.matrix4[3][2] * _b.matrix4[2][3] +
			_a.matrix4[3][3] * _b.matrix4[3][3];

		return m;
	}

	Matrix4& operator*=(const Matrix4& _m)
	{
		*this = *this * _m;
		return *this;
	}

	void Invert();

	Vector3 GetTranslation() const
	{
		return Vector3(matrix4[3][0], matrix4[3][1], matrix4[3][2]);
	}

	static Matrix4 CreateScale(float _x, float _y, float _z)
	{
		float m[4][4] =
		{
			{ _x,   0.0f, 0.0f, 0.0f },
			{ 0.0f, _y,   0.0f, 0.0f },
			{ 0.0f, 0.0f, _z,   0.0f },
			{ 0.0f, 0.0f, 0.0f, 1.0f },
		};
		return Matrix4(m);
	}

	static Matrix4 CreateScale(const Vector3& _v)
	{
		return CreateScale(_v.x, _v.y, _v.z);
	}

	static Matrix4 CreateScale(float _s)
	{
		return CreateScale(_s, _s, _s);
	}

	static Matrix4 CreateRotationX(float _a)
	{
		float m[4][4] =
		{
			{ 1.0f, 0.0f,           0.0f,          0.0f },
			{ 0.0f, Math::Cos(_a),  Math::Sin(_a), 0.0f },
			{ 0.0f, -Math::Sin(_a), Math::Cos(_a), 0.0f },
			{ 0.0f, 0.0f,           0.0f,          1.0f },
		};
		return Matrix4(m);
	}

	static Matrix4 CreateRotationY(float _a)
	{
		float m[4][4] =
		{
			{ Math::Cos(_a), 0.0f, -Math::Sin(_a), 0.0f },
			{ 0.0f,          1.0f, 0.0f,           0.0f },
			{ Math::Sin(_a), 0.0f, Math::Cos(_a),  0.0f },
			{ 0.0f,          0.0f, 0.0f,           1.0f },
		};
		return Matrix4(m);
	}

	static Matrix4 CreateRotationZ(float _a)
	{
		float m[4][4] =
		{
			{ Math::Cos(_a),  Math::Sin(_a), 0.0f, 0.0f },
			{ -Math::Sin(_a), Math::Cos(_a), 0.0f, 0.0f },
			{ 0.0f,           0.0f,          1.0f, 0.0f },
			{ 0.0f,           0.0f,          0.0f, 1.0f },
		};
		return Matrix4(m);
	}

	static Matrix4 CreateRotation(const class Quaternion& _q);

	static Matrix4 CreateTranslation(const Vector3& _v)
	{
		float m[4][4] =
		{
			{ 1.0f, 0.0f, 0.0f, 0.0f },
			{ 0.0f, 1.0f, 0.0f, 0.0f },
			{ 0.0f, 0.0f, 1.0f, 0.0f },
			{ _v.x, _v.y, _v.z, 1.0f },
		};
		return Matrix4(m);
	}

	static Matrix4 CreateLookAt(const Vector3& _eye, const Vector3& _target, const Vector3& _up)
	{
		Vector3 z = Vector3::Normalize(_target - _eye);
		Vector3 x = Vector3::Normalize(Vector3::Cross(_up, z));
		Vector3 y = Vector3::Normalize(Vector3::Cross(z, x));

		Vector3 transform;
		transform.x = -Vector3::Dot(x, _eye);
		transform.y = -Vector3::Dot(y, _eye);
		transform.z = -Vector3::Dot(z, _eye);

		float m[4][4] =
		{
			{ x.x,         y.x,         z.x,         0.0f },
			{ x.y,         y.y,         z.y,         0.0f },
			{ x.z,         y.z,         z.z,         0.0f },
			{ transform.x, transform.y, transform.z, 1.0f },
		};
		return Matrix4(m);
	}

	//正射影
	static Matrix4 CreateOrthographic(float _width, float _height, float _near, float _far)
	{
		float m[4][4] =
		{
			{ 2.0f / _width, 0.0f,           0.0f,                   0.0f },
			{ 0.0f,          2.0f / _height, 0.0f,                   0.0f },
			{ 0.0f,          0.0f,           1.0f / (_far - _near),  0.0f },
			{ 0.0f,          0.0f,           _near / (_near - _far), 1.0f },
		};
		return Matrix4(m);
	}

	//透視射影
	static Matrix4 CreatePerspective(float _fov, float _width, float _height, float _near, float _far)
	{
		float y = Math::Cot(_fov / 2.0f);
		float x = y * _height / _width;

		float m[4][4] =
		{
			{ x,    0.0f, 0.0f,                           0.0f },
			{ 0.0f, y,    0.0f,                           0.0f },
			{ 0.0f, 0.0f, _far / (_far - _near),          1.0f },
			{ 0.0f, 0.0f, -_near * _far / (_far - _near), 0.0f },
		};
		return Matrix4(m);
	}

	//2D
	static Matrix4 ViewProjection(float _w, float _h)
	{
		float m[4][4] =
		{
			{ 2.0f / _w, 0.0f,      0.0f, 0.0f },
			{ 0.0f,      2.0f / _h, 0.0f, 0.0f },
			{ 0.0f,      0.0f,      1.0f, 0.0f },
			{ 0.0f,      0.0f,      0.0f, 1.0f },
		};
		return Matrix4(m);
	}

	static const Matrix4 Identity;
};

//クォータニオン
class Quaternion
{
public:
	float x;
	float y;
	float z;
	float w;

	Quaternion()
	{
		*this = Quaternion::Identity;
	}

	explicit Quaternion(float _x, float _y, float _z, float _w)
		:x(_x)
		,y(_y)
		,z(_z)
		,w(_w)
	{}

	explicit Quaternion(const Vector3& _v, float _a)
	{
		float sin = Math::Sin(_a / 2.0f);
		x = _v.x * sin;
		y = _v.y * sin;
		z = _v.z * sin;
		w = Math::Cos(_a / 2.0f);
	}

	float Length() const
	{
		return Math::Sqrt(x * x + y * y + z * z + w * w);
	}

	void Normalize()
	{
		float l = Length();
		x /= l;
		y /= l;
		z /= l;
		w /= l;
	}

	static float Dot(const Quaternion& _a, const Quaternion& _b)
	{
		return _a.x * _b.x + _a.y * _b.y + _a.z * _b.z + _a.w * _b.w;
	}

	//線形補間
	static Quaternion Lerp(const Quaternion& _a, const Quaternion& _b, float _t)
	{
		Quaternion q;
		q.x = Math::Lerp(_a.x, _b.x, _t);
		q.y = Math::Lerp(_a.y, _b.y, _t);
		q.z = Math::Lerp(_a.z, _b.z, _t);
		q.w = Math::Lerp(_a.w, _b.w, _t);
		q.Normalize();
		return q;
	}

	//球面線形補間
	static Quaternion Slerp(const Quaternion& _a, const Quaternion& _b, float _t)
	{
		float rawCosm = Quaternion::Dot(_a, _b);

		float cosom = -rawCosm;
		if (rawCosm >= 0.0f)
		{
			cosom = rawCosm;
		}

		float scale0, scale1;

		if (cosom < 0.9999f)
		{
			const float omega = Math::Acos(cosom);
			const float invSin = 1.0f / Math::Sin(omega);
			scale0 = Math::Sin((1.0f - _t) * omega) * invSin;
			scale1 = Math::Sin(_t * omega) * invSin;
		}
		else
		{
			scale0 = 1.0f - _t;
			scale1 = _t;
		}

		if (rawCosm < 0.0f)
		{
			scale1 = -scale1;
		}

		Quaternion q;
		q.x = scale0 * _a.x + scale1 * _b.x;
		q.y = scale0 * _a.y + scale1 * _b.y;
		q.z = scale0 * _a.z + scale1 * _b.z;
		q.w = scale0 * _a.w + scale1 * _b.w;
		q.Normalize();
		return q;
	}

	static Quaternion Concatenate(const Quaternion& _a, const Quaternion& _b)
	{
		Quaternion q;

		Vector3 a_v(_a.x, _a.y, _a.z);
		Vector3 b_v(_b.x, _b.y, _b.z);
		Vector3 v = _b.w * a_v + _a.w * b_v + Vector3::Cross(b_v, a_v);

		q.x = v.x;
		q.y = v.y;
		q.z = v.z;
		q.w = _b.w * _a.w - Vector3::Dot(b_v, a_v);

		return q;
	}

	static const Quaternion Identity;
};