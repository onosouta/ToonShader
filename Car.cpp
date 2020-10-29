#include "Car.h"
#include "BoxComponent.h"
#include "CarCamera.h"
#include "Cube.h"
#include "Collision.h"
#include "Game.h"
#include "Math.h"
#include "Mesh.h"
#include "MoveComponent.h"
#include "Physics.h"
#include "Renderer.h"
#include "SkinMeshComponent.h"

Car::Car(Game* _game)
	:Actor(_game)
	,angle(0.0f)
{
	MeshComponent* smc = new MeshComponent(this);
	Mesh* mesh = _game->GetRenderer()->GetMesh("Texture/car.gpmesh");
	smc->SetMesh(mesh);
	box = new BoxComponent(this);
	box->SetBox(mesh->GetAABB());
	box->SetIsRotate(true);

	move = new MoveComponent(this);
	CarCamera* cc = new CarCamera(this);
	cc->Initialize();

	SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	Quaternion q = Quaternion(Vector3::UnitY, Math::ToRadians(angle));
	SetRotation(q);
}

void Car::ActorInput(const Uint8* _key)
{
	//ˆÚ“®
	//float front_speed = 0.0f;

	//bool input = false;
	//if (_key[SDL_SCANCODE_Z])
	//{
	//	acceleration = Math::Min(acceleration + 10.0f, 3000.0f);
	//	input = true;
	//}
	//if (_key[SDL_SCANCODE_X])
	//{
	//	if (acceleration >= 0)
	//		acceleration = Math::Max(acceleration - 20.0f, -1000.0f);
	//	if (acceleration <= 0)
	//		acceleration = Math::Max(acceleration - 5.0f, -1000.0f);
	//	input = true;
	//}

	//if (!input)
	//{
	//	if (acceleration < 0)
	//		acceleration = Math::Min(acceleration + 5.0f, 0.0f);
	//	if (acceleration > 0)
	//		acceleration = Math::Max(acceleration - 5.0f, 0.0f);
	//}

	//front_speed += acceleration;
	//front_speed = Math::Max(front_speed, -1000.0f);
	//front_speed = Math::Min(front_speed, 3000.0f);

	//move->SetFrontSpeed(front_speed);


	////‰ñ“]
	//float angle_speed = 0.0f;

	//if (front_speed != 0)
	//{
	//	if (_key[SDL_SCANCODE_LEFT])
	//	{
	//		angle_speed -= front_speed / 3000.0f;
	//	}
	//	if (_key[SDL_SCANCODE_RIGHT])
	//	{
	//		angle_speed += front_speed / 3000.0f;
	//	}
	//}

	//move->SetAngleSpeed(angle_speed);
}

void Car::ActorUpdate(float _delta_time)
{
	WorldTransform();

	const AABB& aabb = box->GetWorldBox();
	Vector3 pos = GetPosition();

	std::vector<Cube*> cubes = GetGame()->GetCube();
	for (auto cube : cubes)
	{
		const AABB& cube_box = cube->GetBox()->GetWorldBox();

		if (Intersect(aabb, cube_box))
		{
			float dx1 = cube_box.min.x - aabb.max.x;
			float dx2 = cube_box.max.x - aabb.min.x;
			float dy1 = cube_box.min.y - aabb.max.y;
			float dy2 = cube_box.max.y - aabb.min.y;
			float dz1 = cube_box.min.z - aabb.max.z;
			float dz2 = cube_box.max.z - aabb.min.z;

			float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
			float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
			float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

			if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
			{
				pos.x += dx;

				if (acceleration >  500) acceleration = Math::Max(acceleration - 20.0f,  500.0f);
				if (acceleration < -500) acceleration = Math::Min(acceleration + 20.0f, -500.0f);
			}
			else if (Math::Abs(dy) <= Math::Abs(dy) && Math::Abs(dy) <= Math::Abs(dz))
			{
				pos.y += dy;

				if (acceleration >  500) acceleration = Math::Max(acceleration - 20.0f,  500.0f);
				if (acceleration < -500) acceleration = Math::Min(acceleration + 20.0f, -500.0f);
			}
			else
			{
				pos.z += dz;
			}

			SetPosition(pos);
			box->UpdateWorldTransform();
		}
	}

	angle += 0.25f;
	Quaternion q = Quaternion(Vector3::UnitZ, Math::ToRadians(angle));
	SetRotation(q);
}