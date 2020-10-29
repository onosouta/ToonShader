#pragma once
#include "Bone.h"
#include <string>
#include <vector>

//�A�j���[�V����
class Animation
{
public:
	bool Load(const std::string& _name);

	//�Q�b�^�[
	float GetFrameNum() const { return frame_num; }
	float GetSecond() const { return second; }
	float GetBoneNum() const { return bone_num; }

	//�|�[�Y
	void GetAnimationPose(std::vector<Matrix4>& _out, const class Skeleton* _skeleton, float _t) const;

private:
	std::vector<std::vector<Bone>> animations;//�A�j���[�V����
	float frame_num;	//�t���[����
	float second;		//�A�j���[�V�����̒���
	float bone_num;		//�{�[���̐�
};