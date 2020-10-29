#pragma once
#include "Component.h"

//�X�v���C�g�R���|�[�l���g
class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* _owner, int _order = 100);
	~SpriteComponent();

	//virtual void Draw(SDL_Renderer* _renderer);
	virtual void Draw(class Shader* _shader);

	//virtual void SetTexture(SDL_Texture* _texture);
	virtual void SetTexture(class Texture* _texture);

	//�Q�b�^�[
	int GetOrder() const { return order; }
	int GetTextureWidth() const { return texture_width; }
	int GetTextureHeight() const { return texture_height; }

protected:
	//SDL_Texture* texture;
	class Texture* texture;//�e�N�X�`��
	int order;
	int texture_width;
	int texture_height;
};