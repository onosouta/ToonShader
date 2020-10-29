#include "Physics.h"
#include <algorithm>
#include "BoxComponent.h"
#include "Game.h"

Physics::Physics(Game* _game)
	:game(_game)
{}

bool Physics::LineIntersect(const Line& _line, Information& _information)
{
	bool is_collision = false;//Õ“Ë‚µ‚Ä‚¢‚é‚©

	float min = Math::infinity;
	Vector3 normal;
	for (auto b : boxes)
	{
		float t;
		if (Intersect(_line, b->GetWorldBox(), t, normal))//”»’è
		{
			if (t < min)
			{
				_information.point = _line.Point(t);
				_information.normal = normal;
				_information.box = b;
				_information.actor = b->GetOwner();
				is_collision = true;
			}
		}
	}

	return is_collision;
}

void Physics::Pairwaise(std::function<void(class Actor*, class Actor*)> _f)
{
	for (size_t i = 0; i < boxes.size(); i++)
	{
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxComponent* a = boxes[i];
			BoxComponent* b = boxes[j];
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				_f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void Physics::SweepAndPrune(std::function<void(class Actor*, class Actor*)> _f)
{
	std::sort(boxes.begin(), boxes.end(), [](
		BoxComponent* a,
		BoxComponent* b)
	{
		return a->GetWorldBox().min.x < b->GetWorldBox().min.x;
	});

	for (size_t i = 0; i < boxes.size(); i++)
	{
		BoxComponent* a = boxes[i];

		float max = a->GetWorldBox().max.x;
		for (size_t j = i + 1; j < boxes.size(); j++)
		{
			BoxComponent* b = boxes[j];
			if (b->GetWorldBox().min.x > max)
			{
				break;
			}
			else if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				_f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void Physics::AddBox(BoxComponent* _box)
{
	boxes.emplace_back(_box);
}

void Physics::RemoveBox(BoxComponent* _box)
{
	auto i = std::find(boxes.begin(), boxes.end(), _box);
	if (i != boxes.end())
	{
		std::iter_swap(i, boxes.end() - 1);
		boxes.pop_back();
	}
}