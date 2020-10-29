#include "CameraActor.h"
#include "Game.h"
#include "MoveComponent.h"
#include "Renderer.h"

CameraActor::CameraActor(Game* _game)
	:Actor(_game)
{
	move_component = new MoveComponent(this);
}

void CameraActor::ActorUpdate(float _delta_time)
{
	Actor::ActorUpdate(_delta_time);

	Vector3 camera_position = GetPosition();
	Vector3 target = GetPosition() + GetFront() * 100.0f;
	Vector3 up = Vector3::UnitY;

	Matrix4 view = Matrix4::CreateLookAt(camera_position, target, up);
	GetGame()->GetRenderer()->SetView(view);
}

void CameraActor::ActorInput(const Uint8* _key)
{
	//ˆÚ“®
	float front_speed = 0.0f;
	if (_key[SDL_SCANCODE_W])
	{
		front_speed += 300.0f;
	}
	if (_key[SDL_SCANCODE_S])
	{
		front_speed -= 300.0f;
	}
	move_component->SetFrontSpeed(front_speed);

	//‰ñ“]
	float angle_speed = 0.0f;
	if (_key[SDL_SCANCODE_A])
	{
		angle_speed -= Math::pi / 2.0f;
	}
	if (_key[SDL_SCANCODE_D])
	{
		angle_speed += Math::pi / 2.0f;
	}
	move_component->SetAngleSpeed(angle_speed);
}