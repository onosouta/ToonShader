#pragma once
#include "Math.h"
#include <string>

//ボーン
class Bone
{
public:
	Quaternion rotation;
	Vector3 translation;

	Matrix4 ToMatrix() const;

	//補間
	static Bone Interpolate(const Bone& _a, const Bone& _b, float _t);

	//ゲッター
	std::string GetName() const { return name; }
	int GetParent() const { return parent; }

	//セッター
	void SetName(const std::string& _name) { name = _name; }
	void SetParent(int _parent) { parent = _parent; }

private:
	std::string name;	//名前
	int parent;			//親

	Matrix4 matrix;//行列
};