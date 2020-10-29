#pragma once
#include "Bone.h"
#include <string>
#include <vector>

//スケルトン
class Skeleton
{
public:
	bool Load(const std::string& _name);

	const std::vector<Bone>& GetBones() const { return bones; }
	const std::vector<Matrix4>& GetInvBindPoses() const { return inv_bind_poses; }

protected:
	void ComputeBindPoses();

private:
	std::vector<Bone> bones;//ボーン
	std::vector<Matrix4> inv_bind_poses;//バインドポーズの逆行列
};