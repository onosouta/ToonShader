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
		//�A�j���[�V�������X�V
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
		//���[���h���W
		_shader->SetMatrixUniform(
			"world_transform",
			mesh->GetWolrd() * owner->GetWorld());
		//�s��p���b�g
		_shader->SetMatrixUniform("transforms", matrix_palette[0], MAX_BONE);

		//�e�N�X�`��
		Texture* texture = mesh->GetTexture(tex_index);
		if (texture)
		{
			texture->SetActive();
		}

		//���_�z��I�u�W�F�N�g
		VertexArray* vertex_array = mesh->GetVertexArray();
		vertex_array->SetActive();

		//�`��
		glDrawElements(GL_TRIANGLES, vertex_array->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
	}
}

//�A�j���[�V�������Đ�
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

	return animation->GetFrameNum();//�t���[����
}

//�s��p���b�g���v�Z
void SkinMeshComponent::ComputeMatrixPalette()
{
	//�t�o�C���h�|�[�Y�s��
	const std::vector<Matrix4>& inverse_bind_poses = skeleton->GetInvBindPoses();

	//���݂̃|�[�Y
	std::vector<Matrix4> poses;
	animation->GetAnimationPose(poses, skeleton, anime_time);

	//�s��p���b�g���v�Z
	for (size_t i = 0; i < skeleton->GetBones().size(); i++)
	{
		matrix_palette[i] =
			inverse_bind_poses[i] *	//�t�o�C���h�|�[�Y�s��
			poses[i];				//���݂̃|�[�Y
	}
}