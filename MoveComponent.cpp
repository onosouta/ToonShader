#include "MoveComponent.h"
#include "Actor.h"
#include "Math.h"

MoveComponent::MoveComponent(Actor* _owner, int _order)
	:Component(_owner, _order)
	,angle_speed(0.0f)
	,front_speed(0.0f)
{}

void MoveComponent::Update(float _delta_time)
{
	//‰ñ“]
	if (!Math::NearZero(angle_speed))
	{
		Quaternion r = owner->GetRotation();
		float a = angle_speed * _delta_time;
		Quaternion incremental(Vector3::UnitZ, a);
		r = Quaternion::Concatenate(r, incremental);
		owner->SetRotation(r);
	}

	//ˆÚ“®
	if (!Math::NearZero(front_speed))
	{
		Vector3 p = owner->GetPosition();
		p += owner->GetFront() * front_speed * _delta_time;
		owner->SetPosition(p);
	}
}