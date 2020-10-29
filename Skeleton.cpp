#include "Skeleton.h"
#include <fstream>
#include "document.h"
#include "SDL.h"
#include "SkinMeshComponent.h"
#include <sstream>

bool Skeleton::Load(const std::string& _name)
{
	std::ifstream skeleton_file(_name);
	if (!skeleton_file.is_open())
	{
		SDL_Log("%s file not found", _name.c_str());
		return false;
	}

	std::stringstream s_stream;
	s_stream << skeleton_file.rdbuf();
	std::string contents = s_stream.str();

	//RapidJSON
	rapidjson::StringStream string_stream(contents.c_str());
	rapidjson::Document document;
	document.ParseStream(string_stream);

	#pragma region �{�[����ǂݍ���

	rapidjson::Value& json_bone = document["bones"];
	Bone bone;

	rapidjson::Value& bone_num = document["bonecount"];//�{�[���̐�
	for (rapidjson::SizeType i = 0; i < bone_num.GetUint(); i++)
	{
		rapidjson::Value& name = json_bone[i]["name"];//���O
		bone.SetName(name.GetString());

		rapidjson::Value& parent = json_bone[i]["parent"];//�e
		bone.SetParent(parent.GetInt());

		//�o�C���h�|�[�Y
		rapidjson::Value& bind_pose = json_bone[i]["bindpose"];

		rapidjson::Value& r = bind_pose["rot"];
		rapidjson::Value& t = bind_pose["trans"];

		bone.rotation.x = r[0].GetDouble();
		bone.rotation.y = r[1].GetDouble();
		bone.rotation.z = r[2].GetDouble();
		bone.rotation.w = r[3].GetDouble();

		bone.translation.x = t[0].GetDouble();
		bone.translation.y = t[1].GetDouble();
		bone.translation.z = t[2].GetDouble();

		bones.emplace_back(bone);
	}

	#pragma endregion

	ComputeBindPoses();
}

//�o�C���h�|�[�Y�̋t�s����v�Z
void Skeleton::ComputeBindPoses()
{
	inv_bind_poses.resize(GetBones().size());

	//���[�g
	inv_bind_poses[0] = bones[0].ToMatrix();

	//�O���[�o���|�[�Y���v�Z
	for (int i = 1; i < inv_bind_poses.size(); i++)
	{
		inv_bind_poses[i] =
			bones[i].ToMatrix() *					//���[�J���|�[�Y
			inv_bind_poses[bones[i].GetParent()];	//�e�̃O���[�o���|�[�Y
	}

	//�t�s����v�Z
	for (int i = 0; i < inv_bind_poses.size(); i++)
	{
		inv_bind_poses[i].Invert();
	}
}