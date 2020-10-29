#include "Collision.h"
#include <algorithm>
#include <array>

Line::Line(const Vector3& _start, const Vector3& _end)
	:start(_start)	//始点
	,end(_end)		//終点
{}

//0≦t≦1
Vector3 Line::Point(float _t) const
{
	return start + (end - start) * _t;
}

float Line::Distance(const Vector3& _point) const
{
	//start = a
	//end = b
	//_point = c
	Vector3 ab = end - start;
	Vector3 ba = ab * -1.0f;
	Vector3 ac = _point - start;
	Vector3 bc = _point - end;

	//acの長さ
	if (Vector3::Dot(ab, bc) < 0.0f)
	{
		return bc.LengthSqare();
	}
	//bcの長さ
	else if (Vector3::Dot(ba, bc) < 0.0f)
	{
		return bc.LengthSqare();
	}
	//cを投影
	else
	{
		Vector3 p = Vector3::Dot(ac, ab) / Vector3::Dot(ab, ab) * ab;
		return (ac - p).LengthSqare();
	}
}

float Line::Distance(const Line& _a, const Line& _b)
{
	return 1.0f;
}

Plane::Plane(const Vector3& _normal, float _d)
	:normal(_normal)	//法線
	,d(_d)				//原点との距離
{}

Plane::Plane(const Vector3& _a, const Vector3& _b, const Vector3& _c)
{
	Vector3 ab = _b - _a;
	Vector3 ac = _c - _a;

	normal = Vector3::Cross(ab, ac);//法線を計算
	normal.Normalize();

	//d = -P・n
	d = -Vector3::Dot(_a, normal);
}

float Plane::Distance(const Vector3& _point) const
{
	//_point・n - d
	return Vector3::Dot(_point, normal) - d;
}

Sphere::Sphere(const Vector3& _center, float _radius)
	:center(_center)	//中心
	,radius(_radius)	//半径
{}

bool Sphere::Contain(const Vector3& _point) const
{
	return (center - _point).LengthSqare() <= (radius * radius);
}

AABB::AABB(const Vector3& _min, const Vector3& _max)
	:min(_min)	//最小
	,max(_max)	//最大
{}

void AABB::Update(const Vector3& _point)
{
	min.x = Math::Min(min.x, _point.x);
	min.y = Math::Min(min.y, _point.y);
	min.z = Math::Min(min.z, _point.z);

	max.x = Math::Max(max.x, _point.x);
	max.y = Math::Max(max.y, _point.y);
	max.z = Math::Max(max.z, _point.z);
}

void AABB::Rotate(const Quaternion& _q)
{
	std::array<Vector3, 8> points;//角8個

	points[0] = min;
	points[1] = Vector3(max.x, min.y, min.z);
	points[2] = Vector3(min.x, max.y, min.z);
	points[3] = Vector3(min.x, min.y, max.z);
	points[4] = Vector3(min.x, max.y, max.z);
	points[5] = Vector3(max.x, min.y, max.z);
	points[6] = Vector3(max.x, max.y, min.z);
	points[7] = max;

	Vector3 p = Vector3::Transform(points[0], _q);
	min = p;
	max = p;
	//回転
	for (size_t i = 1; i < points.size(); i++)
	{
		p = Vector3::Transform(points[i], _q);
		Update(p);
	}
}

bool AABB::Contain(const Vector3& _point) const
{
	bool is_out =
		_point.x < min.x ||
		_point.y < min.y ||
		_point.z < min.z ||
		_point.x > max.x ||
		_point.y > max.y ||
		_point.z > max.z;
	return !is_out;
}

float AABB::Distance(const Vector3& _point) const
{
	float dx = Math::Max(min.x - _point.x, 0.0f);
	dx = Math::Max(dx, _point.x - max.x);
	float dy = Math::Max(min.y - _point.y, 0.0f);
	dy = Math::Max(dy, _point.y - max.y);
	float dz = Math::Max(min.z - _point.z, 0.0f);
	dz = Math::Max(dz, _point.z - max.z);

	return dx * dx + dy * dy + dz * dz;
}

Capsule::Capsule(const Vector3& _start, const Vector3& _end, float _radius)
	:line(_start, _end)	//線分
	,radius(_radius)	//半径
{}

Vector3 Capsule::Point(float _t) const
{
	return line.Point(_t);
}

bool Capsule::Contain(const Vector3& _point) const
{
	return line.Distance(_point) <= (radius * radius);
}

bool Polygon::Contain(const Vector2& _point) const
{
	float sum = 0.0f;
	Vector2 a, b;//頂点
	for (size_t i = 0; i < vertices.size() - 1; i++)
	{
		a = vertices[i] - _point;//_pointからaへのベクトル
		a.Normalize();
		b = vertices[i + 1] - _point;//_pointからbへのベクトル
		b.Normalize();

		sum += Math::Acos(Vector2::Dot(a, b));
	}

	a = vertices.back() - _point;
	a.Normalize();
	b = vertices.front() - _point;
	b.Normalize();

	sum += Math::Acos(Vector2::Dot(a, b));

	//sum≒360 true
	return Math::NearZero(sum - Math::pi * 2.0f);
}

//球
bool Intersect(const Sphere& _a, const Sphere& _b)
{
	return
		(_a.center - _b.center).LengthSqare() <=
		((_a.radius + _b.radius) * (_a.radius + _b.radius));
}

//AABB
bool Intersect(const AABB& _a, const AABB& _b)
{
	bool no =
		_a.max.x < _b.min.x ||
		_a.max.y < _b.min.y ||
		_a.max.z < _b.min.z ||
		_b.max.x < _a.min.x ||
		_b.max.y < _a.min.y ||
		_b.max.z < _a.min.z;
	return !no;
}

//カプセル
bool Intersect(const Capsule& _a, const Capsule& _b)
{
	return
		Line::Distance(_a.line, _b.line) <=
		((_a.radius + _b.radius) * (_a.radius + _b.radius));
}

//球とAABB
bool Intersect(const Sphere& _sphere, const AABB& _aabb)
{
	return
		_aabb.Distance(_sphere.center) <=
		(_sphere.radius * _sphere.radius);
}

//線分と球
bool Intersect(const Line& _line, const Sphere& _sphere, float& _t)
{
	Vector3 x = _line.start - _sphere.center;
	Vector3 y = _line.end - _line.start;
	float a = Vector3::Dot(y, y);
	float b = 2.0f * Vector3::Dot(x, y);
	float c = Vector3::Dot(x, x) - _sphere.radius * _sphere.radius;

	//判別式
	float d = b * b - 4.0f * a * c;//b^2 - 4ac
	if (d < 0.0f)
	{
		return false;
	}
	else
	{
		d = Math::Sqrt(d);
		float min = (-b - d) / (2.0f * a);
		float max = (-b + d) / (2.0f * a);
		if (min >= 0.0f && min <= 1.0f)//0≦t≦1か
		{
			_t = min;
			return true;
		}
		else if (max >= 0.0f && max <= 1.0f)//0≦t≦1か
		{
			_t = max;
			return true;
		}
		else
		{
			return false;
		}
	}
}

//線分と平面
bool Intersect(const Line& _line, const Plane& _plane, float & _t)
{
	float d = Vector3::Dot(_line.end - _line.start, _plane.normal);//分母
	if (Math::NearZero(d))
	{
		if (Math::NearZero(Vector3::Dot(_line.start, _plane.normal) - _plane.d))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		float m = -Vector3::Dot(_line.start, _plane.normal) - _plane.d;//分子
		_t = m / d;
		if (_t >= 0.0f && _t <= 1.0f)//0≦t≦1か
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

bool Intersect(float _start, float _end, float _side, const Vector3& _normal, std::vector<std::pair<float, Vector3>>& _out)
{
	float d = _end - _start;//分母
	if (Math::NearZero(d))
	{
		return false;
	}
	else
	{
		float m = -_start * _side;//分子
		float t = m / d;
		if (t >= 0.0f && t <= 1.0f)//0≦t≦1か
		{
			_out.emplace_back(t, _normal);
			return true;
		}
		else
		{
			return false;
		}
	}
}

//線分とAABB
bool Intersect(const Line& _line, const AABB& _aabb, float& _t, Vector3& _normal)
{
	std::vector<std::pair<float, Vector3>> values;

	//x
	Intersect(_line.start.x, _line.end.x, _aabb.min.x, Vector3::UnitX * -1.0f, values);
	Intersect(_line.start.x, _line.end.x, _aabb.max.x, Vector3::UnitX, values);
	//y
	Intersect(_line.start.y, _line.end.y, _aabb.min.y, Vector3::UnitY * -1.0f, values);
	Intersect(_line.start.y, _line.end.y, _aabb.max.y, Vector3::UnitY, values);
	//z
	Intersect(_line.start.z, _line.end.z, _aabb.min.z, Vector3::UnitZ * -1.0f, values);
	Intersect(_line.start.z, _line.end.z, _aabb.max.z, Vector3::UnitZ, values);

	//ソート
	std::sort(values.begin(), values.end(), [](
		const std::pair<float, Vector3>& a,
		const std::pair<float, Vector3>& b)
	{
		return a.first < b.first;
	});

	Vector3 point;
	for (auto& v : values)
	{
		point = _line.Point(v.first);
		if (_aabb.Contain(point))
		{
			_t = v.first;		//t
			_normal = v.second;	//法線
			return true;
		}
	}

	return false;
}

//スイープ&プルーン
bool SphereSweep(const Sphere& p0, const Sphere& p1, const Sphere& q0, const Sphere& q1, float& _t)
{
	Vector3 x = p0.center - q0.center;
	Vector3 y = p1.center - p0.center - (q1.center - q0.center);
	float a = Vector3::Dot(y, y);
	float b = 2.0f * Vector3::Dot(x, y);
	float c = Vector3::Dot(x, x) - (p0.radius + q0.radius) * (p0.radius + q0.radius);

	//判別式
	float d = b * b - 4.0f * a * c;//b^2 - 4ac
	if (d < 0.0f)
	{
		return false;
	}
	else
	{
		d = Math::Sqrt(d);
		_t = (-b - d) / (2.0f * a);
		if (_t >= 0.0f && _t <= 0.0f)//0≦t≦1か
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}