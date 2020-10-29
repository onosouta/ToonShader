#pragma once
#include "Actor.h"

//ƒJƒƒ‰
class CameraActor : public Actor
{
public:
	CameraActor(class Game* _game);

	void ActorUpdate(float _delta_time) override;
	void ActorInput(const Uint8* _key) override;

private:
	class MoveComponent* move_component;
};