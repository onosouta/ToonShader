#include "BoxComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Physics.h"

BoxComponent::BoxComponent(Actor* _owner, int _order)
	:Component(_owner, _order)
	,box(Vector3::Zero, Vector3::Zero)
	,world_box(Vector3::Zero, Vector3::Zero)
	,is_rotate(true)
{
	owner->GetGame()->GetPhysics()->AddBox(this);
}

BoxComponent::~BoxComponent()
{
	owner->GetGame()->GetPhysics()->RemoveBox(this);
}

void BoxComponent::UpdateWorldTransform()
{
	world_box = box;

	//�X�P�[��
	world_box.min *= owner->GetScale();
	world_box.max *= owner->GetScale();

	//��]
	if (is_rotate)
	{
		//world_box.Rotate(owner->GetRotation());//�v
	}

	//�ړ�
	world_box.min += owner->GetPosition();
	world_box.max += owner->GetPosition();
}