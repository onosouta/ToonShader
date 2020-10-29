#pragma once
#include "Math.h"
#include <string>

//�{�[��
class Bone
{
public:
	Quaternion rotation;
	Vector3 translation;

	Matrix4 ToMatrix() const;

	//���
	static Bone Interpolate(const Bone& _a, const Bone& _b, float _t);

	//�Q�b�^�[
	std::string GetName() const { return name; }
	int GetParent() const { return parent; }

	//�Z�b�^�[
	void SetName(const std::string& _name) { name = _name; }
	void SetParent(int _parent) { parent = _parent; }

private:
	std::string name;	//���O
	int parent;			//�e

	Matrix4 matrix;//�s��
};