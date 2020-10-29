#pragma once
#include "Component.h"

//スプライトコンポーネント
class SpriteComponent : public Component
{
public:
	SpriteComponent(class Actor* _owner, int _order = 100);
	~SpriteComponent();

	//virtual void Draw(SDL_Renderer* _renderer);
	virtual void Draw(class Shader* _shader);

	//virtual void SetTexture(SDL_Texture* _texture);
	virtual void SetTexture(class Texture* _texture);

	//ゲッター
	int GetOrder() const { return order; }
	int GetTextureWidth() const { return texture_width; }
	int GetTextureHeight() const { return texture_height; }

protected:
	//SDL_Texture* texture;
	class Texture* texture;//テクスチャ
	int order;
	int texture_width;
	int texture_height;
};