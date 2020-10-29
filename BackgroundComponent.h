#pragma once
#include <vector>
#include "Math.h"
#include "SpriteComponent.h"

//�w�i�R���|�[�l���g
class BackgroundComponent : public SpriteComponent
{
public:
	BackgroundComponent(class Actor* _owner, int _order = 10);

	void Update(float _delta_time) override;
	//void Draw(SDL_Renderer* _renderer) override;

	void SetTextures(const std::vector<SDL_Texture*>& _textures);

	float GetSpeed() const { return speed; }
	void SetSpeed(float _speed) { speed = _speed; }

private:
	//�e�N�X�`��
	struct Texture
	{
		SDL_Texture* texture;
		Vector2 offset;
	};
	std::vector<Texture> textures;

	float speed;
	Vector2 screen_size;
};