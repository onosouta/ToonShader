#pragma once
#include "MeshComponent.h"
#include "Math.h"
#include <vector>

const size_t MAX_BONE = 96;

//スキンメッシュコンポーネント
class SkinMeshComponent : public MeshComponent
{
public:
	SkinMeshComponent(class Actor* _owner);

	void Update(float _delta_time) override;
	void Draw(class Shader* _shader) override;

	void SetSkeleton(class Skeleton* _skeleton) { skeleton = _skeleton; }

	//再生
	float PlayAnimation(class Animation* _animation, float _animation_rate = 1.0f);

private:
	void ComputeMatrixPalette();

	Matrix4 matrix_palette[MAX_BONE];//行列パレット

	class Skeleton* skeleton;			//スケルトン
	const class Animation* animation;	//アニメーション
	float play_rate;
	float anime_time;
};