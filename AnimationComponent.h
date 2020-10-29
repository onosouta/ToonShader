#pragma once
#include <vector>
#include "SpriteComponent.h"

//アニメーションコンポーネント
class AnimationComponent : public SpriteComponent
{
public:
	AnimationComponent(class Actor* _owner, int  _order = 100);

	void Update(float _delta_time) override;

	//void SetTextures(const std::vector<SDL_Texture*>& _textures);
	void SetTextures(const std::vector<class Texture*>& _textures);

	float GetFPS() const { return fps; }
	void SetFPS(float _fps) { fps = _fps; }

private:
	//std::vector<SDL_Texture*> textures;
	std::vector<class Texture*> textures;//テクスチャ
	float frame;	//フレーム数
	float fps;		//フレームレート
};