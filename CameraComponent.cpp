#include "CameraComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"

CameraComponent::CameraComponent(Actor* _owner, int _order)
	:Component(_owner, order)
{}

void CameraComponent::SetView(const Matrix4& _view)
{
	owner->GetGame()->GetRenderer()->SetView(_view);
}