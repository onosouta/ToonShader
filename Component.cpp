#include "Component.h"
#include "Actor.h"

Component::Component(Actor* _owner, int _order)
	:owner(_owner)
	,order(_order)
{
	owner->AddComponent(this);
}

Component::~Component()
{
	owner->RemoveComponent(this);
}