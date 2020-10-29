#include "Bone.h"

//�s��ɕϊ�
Matrix4 Bone::ToMatrix() const
{
	Matrix4 r = Matrix4::CreateRotation(rotation);
	Matrix4 t = Matrix4::CreateTranslation(translation);

	return r * t;
}

//�{�[��_a�ƃ{�[��_b����
Bone Bone::Interpolate(const Bone& _a, const Bone& _b, float _t)
{
	Bone bone;
	bone.rotation = Quaternion::Slerp(_a.rotation, _b.rotation, _t);
	bone.translation = Vector3::Lerp(_a.translation, _b.translation, _t);
	return bone;
}