#include "Animation.h"
#include "Bone.h"
#include "document.h"
#include <fstream>
#include "rapidjson.h"
#include "SDL.h"
#include "Skeleton.h"
#include <sstream>

bool Animation::Load(const std::string& _name)
{
	std::ifstream animation_file(_name);
	if (!animation_file.is_open())
	{
		SDL_Log("%s file not found", _name.c_str());
		return false;
	}

	std::stringstream s_stream;
	s_stream << animation_file.rdbuf();
	std::string contents = s_stream.str();

	//RapidJSON
	rapidjson::StringStream string_stream(contents.c_str());
	rapidjson::Document document;
	document.ParseStream(string_stream);

	rapidjson::Value& json_frames = document["frames"];
	rapidjson::Value& json_second = document["length"];
	rapidjson::Value& json_bone_num = document["bonecount"];

	frame_num = json_frames.GetUint();//フレーム数
	second = json_second.GetDouble();//アニメーションの長さ
	bone_num = json_bone_num.GetUint();//ボーンの数

	#pragma region アニメーションを読み込む

	animations.resize(bone_num);

	rapidjson::Value& json_animations = document["tracks"];
	for (rapidjson::SizeType i = 0; i < json_animations.Size(); i++)
	{
		int bone_index = json_animations[i]["bone"].GetUint();

		rapidjson::Value& transform = json_animations[i]["transforms"];
		for (rapidjson::SizeType j = 0; j < transform.Size(); j++)
		{
			Bone bone;

			rapidjson::Value& r = transform[j]["rot"];
			rapidjson::Value& t = transform[j]["trans"];

			bone.rotation.x = r[0].GetDouble();
			bone.rotation.y = r[1].GetDouble();
			bone.rotation.z = r[2].GetDouble();
			bone.rotation.w = r[3].GetDouble();

			bone.translation.x = t[0].GetDouble();
			bone.translation.y = t[1].GetDouble();
			bone.translation.z = t[2].GetDouble();

			animations[bone_index].emplace_back(bone);
		}
	}

	#pragma endregion
}

void Animation::GetAnimationPose(std::vector<Matrix4>& _out, const Skeleton* _skeleton, float _t) const
{
	if (_out.size() != bone_num)
	{
		_out.resize(bone_num);
	}

	float length = second / (frame_num - 1);//フレームの長さ

	//インデックスを計算
	size_t frame = static_cast<size_t>(_t / length);
	size_t next = frame + 1;

	//ルートのポーズを設定
	if (animations[0].size() > 0)
	{
		//補間
		Bone interpolate = Bone::Interpolate(
			animations[0][frame],
			animations[0][next],
			_t / length - frame);

		_out[0] = interpolate.ToMatrix();
	}
	else
	{
		_out[0] = Matrix4::Identity;
	}

	const std::vector<Bone>& bones = _skeleton->GetBones();
	//ルート以外のポーズを設定
	for (size_t bone = 1; bone < bone_num; bone++)
	{
		Matrix4 local;
		if (animations[bone].size() > 0)
		{
			//補間
			Bone interpolate = Bone::Interpolate(
				animations[bone][frame],
				animations[bone][next],
				_t / length - frame);

			local = interpolate.ToMatrix();
		}

		_out[bone] = local *_out[bones[bone].GetParent()];
	}
}