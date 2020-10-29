#include "SkinMeshComponent.h"
#include "Actor.h"
#include "Animation.h"
#include "Mesh.h"
#include "Shader.h"
#include "Skeleton.h"
#include "Texture.h"
#include "VertexArray.h"

SkinMeshComponent::SkinMeshComponent(Actor* _owner)
	:MeshComponent(_owner, true)
{}

void SkinMeshComponent::Update(float delta_time)
{
	if (skeleton && animation)
	{
		//アニメーションを更新
		anime_time += play_rate * delta_time;
		while (anime_time > animation->GetSecond())
		{
			anime_time -= animation->GetSecond();
		}

		ComputeMatrixPalette();
	}
}

void SkinMeshComponent::Draw(Shader* _shader)
{
	if (mesh)
	{
		//ワールド座標
		_shader->SetMatrixUniform(
			"world_transform",
			mesh->GetWolrd() * owner->GetWorld());
		//行列パレット
		_shader->SetMatrixUniform("transforms", matrix_palette[0], MAX_BONE);

		//テクスチャ
		Texture* texture = mesh->GetTexture(tex_index);
		if (texture)
		{
			texture->SetActive();
		}

		//頂点配列オブジェクト
		VertexArray* vertex_array = mesh->GetVertexArray();
		vertex_array->SetActive();

		//描画
		glDrawElements(GL_TRIANGLES, vertex_array->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
	}
}

//アニメーションを再生
float SkinMeshComponent::PlayAnimation(Animation* _animation, float _play_rate)
{
	animation = _animation;
	play_rate = _play_rate;
	anime_time = 0.0f;

	if (!animation)
	{
		return 0.0f;
	}

	ComputeMatrixPalette();

	return animation->GetFrameNum();//フレーム数
}

//行列パレットを計算
void SkinMeshComponent::ComputeMatrixPalette()
{
	//逆バインドポーズ行列
	const std::vector<Matrix4>& inverse_bind_poses = skeleton->GetInvBindPoses();

	//現在のポーズ
	std::vector<Matrix4> poses;
	animation->GetAnimationPose(poses, skeleton, anime_time);

	//行列パレットを計算
	for (size_t i = 0; i < skeleton->GetBones().size(); i++)
	{
		matrix_palette[i] =
			inverse_bind_poses[i] *	//逆バインドポーズ行列
			poses[i];				//現在のポーズ
	}
}