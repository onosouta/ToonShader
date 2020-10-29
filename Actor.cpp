#include "Actor.h"
#include <algorithm>
#include "Component.h"
#include "Game.h"

Actor::Actor(Game* _game)
	:game(_game)
	,state(Active)
	,is_recalculate(true)
	,scale(Vector3(1.0f, 1.0f, 1.0f))
	,rotation(Quaternion::Identity)
	,position(Vector3::Zero)
{
	game->AddActor(this);
}

Actor::~Actor()
{
	game->RemoveActor(this);

	while (!components.empty())
	{
		delete components.back();
	}
}

void Actor::Input(const Uint8* _key)
{
	if (state == Active)
	{
		for (auto c : components)
		{
			c->Input(_key);
		}

		ActorInput(_key);
	}
}

void Actor::Update(float _delta_time)
{
	if (state == Active)
	{
		WorldTransform();

		UpdateComponent(_delta_time);
		ActorUpdate(_delta_time);

		WorldTransform();
	}
}

void Actor::WorldTransform()
{
	if (is_recalculate)
	{
		is_recalculate = false;

		//ワールド変換
		world = Matrix4::CreateScale(scale);
		world *= Matrix4::CreateRotation(rotation);
		world *= Matrix4::CreateTranslation(Vector3(position.x, position.y, 0.0f));

		for (auto c : components)
		{
			c->UpdateWorldTransform();
		}
	}
}

void Actor::UpdateComponent(float delta_time)
{
	for (auto c : components)
	{
		c->Update(delta_time);
	}
}

void Actor::AddComponent(Component* _component)
{
	//コンポーネントを追加
	int order = _component->GetOrder();
	auto i = components.begin();
	for (; i != components.end(); ++i)
	{
		if (order < (*i)->GetOrder())
		{
			break;
		}
	}

	components.insert(i, _component);
}

void Actor::RemoveComponent(Component* _component)
{
	//コンポーネントを削除
	auto i = std::find(components.begin(), components.end(), _component);
	if (i != components.end())
	{
		components.erase(i);
	}
}