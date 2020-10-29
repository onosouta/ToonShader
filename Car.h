#pragma once
#include "Actor.h"

//ŽÔ
class Car : public Actor
{
public:
	Car(class Game* _game);

	void ActorInput(const Uint8* _key) override;
	void ActorUpdate(float _delta_time) override;

private:
	class MoveComponent* move;
	class BoxComponent* box;

	float acceleration;

	float angle;
};