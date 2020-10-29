#pragma once
#include "Math.h"
#include <vector>

//����
struct Line
{
	Vector3 start;	//�n�_
	Vector3 end;	//�I�_

	Line(const Vector3& _start, const Vector3& _end);
	
	Vector3 Point(float _t) const;//0��t��1
	float Distance(const Vector3& _point) const;//�����Ɠ_�̋���
	static float Distance(const Line& _a, const Line& _b);//�����Ɛ����̋���
};

//����
struct Plane
{
	Vector3 normal;	//�@��
	float d;		//���_�Ƃ̋���

	Plane(const Vector3& _normal, float _d);
	Plane(const Vector3& _a, const Vector3& _b, const Vector3& _c);

	float Distance(const Vector3& _point) const;//���ʂƓ_�̋���
};

//��
struct Sphere
{
	Vector3 center;	//���S
	float radius;	//���a

	Sphere(const Vector3& _center, float _radius);

	bool Contain(const Vector3& _point) const;
};

struct AABB
{
	Vector3 min;	//�ŏ�
	Vector3 max;	//�ő�

	AABB(const Vector3& _min, const Vector3& _max);

	void Update(const Vector3& _point);//�ő�ƍŏ���_point�ōX�V

	void Rotate(const Quaternion& _q);//��]
	bool Contain(const Vector3& _point) const;
	float Distance(const Vector3& _point) const;//AABB�Ɠ_�̋���
};

//�J�v�Z��
struct Capsule
{
	Line line;		//����
	float radius;	//���a

	Capsule(const Vector3& _start, const Vector3& _end, float _radius);

	Vector3 Point(float _t) const;//0��t��1
	bool Contain(const Vector3& _point) const;
};

//�|���S��
struct Polygon
{
	std::vector<Vector2> vertices;//���_

	bool Contain(const Vector2& _point) const;
};

bool Intersect(const Sphere& _a, const Sphere& _b);			//��
bool Intersect(const AABB& _a, const AABB& _b);				//AABB
bool Intersect(const Capsule& _a, const Capsule& _b);		//�J�v�Z��
bool Intersect(const Sphere& _sphere, const AABB& _box);	//����AABB

bool Intersect(const Line& _line, const Sphere& _sphere, float& _t);				//�����Ƌ�
bool Intersect(const Line& _line, const Plane& _plane, float& _t);					//�����ƕ���
bool Intersect(const Line& _line, const AABB& _aabb, float& _t, Vector3& _normal);	//������AABB

//�X�C�[�v
bool SphereSweep(const Sphere& _p0, const Sphere& _p1, const Sphere& _q0, const Sphere& _q1, float& _t);