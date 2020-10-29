#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "glew.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"

SpriteComponent::SpriteComponent(Actor* _owner, int _order)
	:Component(_owner)
	,texture(nullptr)
	,order(_order)
	,texture_width(0)
	,texture_height(0)
{
	owner->GetGame()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner->GetGame()->GetRenderer()->RemoveSprite(this);
}

//void SpriteComponent::Draw(SDL_Renderer* _renderer)
//{
//	if (texture)
//	{
//		SDL_Rect rect;
//		rect.w = static_cast<int>(texture_width * owner->GetScale());	//w
//		rect.h = static_cast<int>(texture_height * owner->GetScale());	//h
//		rect.x = static_cast<int>(owner->GetPosition().x - rect.w / 2);	//x
//		rect.y = static_cast<int>(owner->GetPosition().y - rect.h / 2);	//y
//
//		//•`‰æ
//		SDL_RenderCopyEx(
//			_renderer,								//SDL_Renderer
//			texture,								//SDL_Texture
//			nullptr,								//SDL_Rect
//			&rect,									//SDL_Rect
//			-Math::ToDegrees(owner->GetRotation()),	//angle
//			nullptr,								//SDL_Point
//			SDL_FLIP_NONE);							//SDL_RendererFlip
//	}
//}
void SpriteComponent::Draw(Shader* _shader)
{
	if (texture)
	{
		Matrix4 scale_matrix = Matrix4::CreateScale(
			static_cast<float>(texture_width),
			static_cast<float>(texture_height),
			1.0f);

		Matrix4 world_transform = scale_matrix * owner->GetWorld();

		_shader->SetMatrixUniform("world_transform", world_transform);
		texture->SetActive();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* _texture)//SDL_Texture* _texture)
{
	texture = _texture;
	//SDL_QueryTexture(
	//	_texture,			//SDL_Texture
	//	nullptr,			//format
	//	nullptr,			//access
	//	&texture_width,		//w
	//	&texture_height);	//h
	texture_width = texture->GetWidth();
	texture_height = texture->GetHeight();
}