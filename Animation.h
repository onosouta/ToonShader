#pragma once
#include "Bone.h"
#include <string>
#include <vector>

//アニメーション
class Animation
{
public:
	bool Load(const std::string& _name);

	//ゲッター
	float GetFrameNum() const { return frame_num; }
	float GetSecond() const { return second; }
	float GetBoneNum() const { return bone_num; }

	//ポーズ
	void GetAnimationPose(std::vector<Matrix4>& _out, const class Skeleton* _skeleton, float _t) const;

private:
	std::vector<std::vector<Bone>> animations;//アニメーション
	float frame_num;	//フレーム数
	float second;		//アニメーションの長さ
	float bone_num;		//ボーンの数
};