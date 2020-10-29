#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(Actor* _owner, int _order)
	:SpriteComponent(_owner, _order)
	,frame(0.0f)
	,fps(24.0f)
{}

void AnimationComponent::Update(float _delta_time)
{
	SpriteComponent::Update(_delta_time);

	if (textures.size() > 0)
	{
		frame += fps * _delta_time;

		while (frame >= textures.size())
		{
			frame -= textures.size();
		}

		SetTexture(textures[static_cast<int>(frame)]);//SpriteComponent::SetTexture
	}
}

//void AnimationComponent::SetTextures(const std::vector<SDL_Texture*>& _textures)
void AnimationComponent::SetTextures(const std::vector<Texture*>& _textures)
{
	textures = _textures;

	if (textures.size() > 0)
	{
		frame = 0.0f;
		SetTexture(textures[0]);
	}
}