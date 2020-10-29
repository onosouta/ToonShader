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

	#pragma region ボーンを読み込む

	rapidjson::Value& json_bone = document["bones"];
	Bone bone;

	rapidjson::Value& bone_num = document["bonecount"];//ボーンの数
	for (rapidjson::SizeType i = 0; i < bone_num.GetUint(); i++)
	{
		rapidjson::Value& name = json_bone[i]["name"];//名前
		bone.SetName(name.GetString());

		rapidjson::Value& parent = json_bone[i]["parent"];//親
		bone.SetParent(parent.GetInt());

		//バインドポーズ
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

//バインドポーズの逆行列を計算
void Skeleton::ComputeBindPoses()
{
	inv_bind_poses.resize(GetBones().size());

	//ルート
	inv_bind_poses[0] = bones[0].ToMatrix();

	//グローバルポーズを計算
	for (int i = 1; i < inv_bind_poses.size(); i++)
	{
		inv_bind_poses[i] =
			bones[i].ToMatrix() *					//ローカルポーズ
			inv_bind_poses[bones[i].GetParent()];	//親のグローバルポーズ
	}

	//逆行列を計算
	for (int i = 0; i < inv_bind_poses.size(); i++)
	{
		inv_bind_poses[i].Invert();
	}
}