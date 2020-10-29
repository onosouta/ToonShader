#include "BackgroundComponent.h"
#include "Actor.h"
#include "Game.h"

BackgroundComponent::BackgroundComponent(Actor* _owner, int _order)
	:SpriteComponent(_owner, _order)
	,speed(0.0f)
{
	screen_size = Vector2(
		owner->GetGame()->GetScreenWidth(),
		owner->GetGame()->GetScreenHeight());
}

void BackgroundComponent::Update(float _delta_time)
{
	SpriteComponent::Update(_delta_time);

	for (auto& t : textures)
	{
		t.offset.x += speed * _delta_time;

		if (t.offset.x < -screen_size.x)
		{
			t.offset.x = (textures.size() - 1) * screen_size.x - 1;
		}
	}
}

//void BackgroundComponent::Draw(SDL_Renderer* _renderer)
//{
//	for (auto& t : textures)
//	{
//		SDL_Rect rect;
//		rect.w = static_cast<int>(screen_size.x);	//w
//		rect.h = static_cast<int>(screen_size.y);	//h
//		rect.x = static_cast<int>(owner->GetPosition().x - rect.w / 2 + t.offset.x);	//x
//		rect.y = static_cast<int>(owner->GetPosition().y - rect.h / 2 + t.offset.y);	//y
//
//		//•`‰æ
//		SDL_RenderCopy(
//			_renderer,	//SDL_Renderer
//			t.texture,	//SDL_Texture
//			nullptr,	//SDL_Rect
//			&rect);		//SDL_Rect
//	}
//}

void BackgroundComponent::SetTextures(const std::vector<SDL_Texture*>& _textures)
{
	int count = 0;
	for (auto _t : _textures)
	{
		Texture t;
		t.texture = _t;
		t.offset.x = count * screen_size.x;
		t.offset.y = 0;
		textures.emplace_back(t);

		count++;
	}
}