#pragma once
#include "SDL.h"

//コンポーネント
class Component
{
public:
	Component(class Actor* _owner, int _order = 100);
	virtual ~Component();

	virtual void Input(const Uint8* _key) {}
	virtual void Update(float _delta_time) {}

	virtual void UpdateWorldTransform() {}

	//ゲッター
	Actor* GetOwner() { return owner; }
	int GetOrder() const { return order; }

protected:
	Actor* owner;
	int order;
};