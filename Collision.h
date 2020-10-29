#pragma once
#include "Math.h"
#include <vector>

//線分
struct Line
{
	Vector3 start;	//始点
	Vector3 end;	//終点

	Line(const Vector3& _start, const Vector3& _end);
	
	Vector3 Point(float _t) const;//0≦t≦1
	float Distance(const Vector3& _point) const;//線分と点の距離
	static float Distance(const Line& _a, const Line& _b);//線分と線分の距離
};

//平面
struct Plane
{
	Vector3 normal;	//法線
	float d;		//原点との距離

	Plane(const Vector3& _normal, float _d);
	Plane(const Vector3& _a, const Vector3& _b, const Vector3& _c);

	float Distance(const Vector3& _point) const;//平面と点の距離
};

//球
struct Sphere
{
	Vector3 center;	//中心
	float radius;	//半径

	Sphere(const Vector3& _center, float _radius);

	bool Contain(const Vector3& _point) const;
};

struct AABB
{
	Vector3 min;	//最小
	Vector3 max;	//最大

	AABB(const Vector3& _min, const Vector3& _max);

	void Update(const Vector3& _point);//最大と最小を_pointで更新

	void Rotate(const Quaternion& _q);//回転
	bool Contain(const Vector3& _point) const;
	float Distance(const Vector3& _point) const;//AABBと点の距離
};

//カプセル
struct Capsule
{
	Line line;		//線分
	float radius;	//半径

	Capsule(const Vector3& _start, const Vector3& _end, float _radius);

	Vector3 Point(float _t) const;//0≦t≦1
	bool Contain(const Vector3& _point) const;
};

//ポリゴン
struct Polygon
{
	std::vector<Vector2> vertices;//頂点

	bool Contain(const Vector2& _point) const;
};

bool Intersect(const Sphere& _a, const Sphere& _b);			//球
bool Intersect(const AABB& _a, const AABB& _b);				//AABB
bool Intersect(const Capsule& _a, const Capsule& _b);		//カプセル
bool Intersect(const Sphere& _sphere, const AABB& _box);	//球とAABB

bool Intersect(const Line& _line, const Sphere& _sphere, float& _t);				//線分と球
bool Intersect(const Line& _line, const Plane& _plane, float& _t);					//線分と平面
bool Intersect(const Line& _line, const AABB& _aabb, float& _t, Vector3& _normal);	//線分とAABB

//スイープ
bool SphereSweep(const Sphere& _p0, const Sphere& _p1, const Sphere& _q0, const Sphere& _q1, float& _t);