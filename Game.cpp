#include "Game.h"
#include "Actor.h"
#include "Bone.h"
#include "BoxComponent.h"
#include "Car.h"
#include "CameraActor.h"
#include "Cube.h"
//#include "FBX.h"
#include "glew.h"
//#include "InputComponent.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Physics.h"
#include "Renderer.h"
#include "Skeleton.h"
#include "SkinMeshComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include <vector>

Game::Game()
	:is_running(true)
	,is_updating(false)
{}

bool Game::Initialize()
{
	//SDLを初期化
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		SDL_Log("failed to SDL initialize : %s", SDL_GetError());
		return false;
	}

	screen_width = 1500.0f;
	screen_height = 800.0f;

	//レンダラーを初期化
	renderer = new Renderer(this);
	if (!renderer->Initialize(screen_width, screen_height))
	{
		SDL_Log("failed to initialize renderer");
		delete renderer;
		renderer = nullptr;
		return false;
	}

	physics = new Physics(this);

	Load();

	tick_count = SDL_GetTicks();

	return true;
}

void Game::GameLoop()
{
	while (is_running)
	{
		Input();
		Update();
		Output();
	}
}

void Game::Shutdown()
{
	Unload();
	if (renderer)
	{
		renderer->Shutdown();
	}
	SDL_Quit();
}

void Game::AddActor(Actor* _actor)
{
	if (is_updating)
	{
		add_actors.emplace_back(_actor);
	}
	else
	{
		actors.emplace_back(_actor);
	}
}

void Game::RemoveActor(Actor* _actor)
{
	//add_actor
	auto i = std::find(add_actors.begin(), add_actors.end(), _actor);
	if (i != add_actors.end())
	{
		std::iter_swap(i, add_actors.end() - 1);
		add_actors.pop_back();
	}

	//actor
	i = std::find(actors.begin(), actors.end(), _actor);
	if (i != actors.end())
	{
		std::iter_swap(i, actors.end() - 1);
		actors.pop_back();
	}
}

void Game::Input()
{
	//イベント
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			is_running = false;
			break;
		}
	}

	const Uint8* key = SDL_GetKeyboardState(NULL);

	//エスケープキー
	if (key[SDL_SCANCODE_ESCAPE])
	{
		is_running = false;
	}

	is_updating = true;

	for (auto a : actors)
	{
		a->Input(key);
	}

	is_updating = false;
}

void Game::Update()
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), tick_count + 16))//16ms
		;

	//デルタタイム
	float delta_time = (SDL_GetTicks() - tick_count) / 1000.0f;
	if (delta_time > 0.05f)
	{
		delta_time = 0.05f;
	}
	tick_count = SDL_GetTicks();

	is_updating = true;

	for (auto a : actors)
	{
		a->Update(delta_time);
	}

	is_updating = false;

	for (auto a : add_actors)
	{
		a->WorldTransform();
		actors.emplace_back(a);
	}
	add_actors.clear();

	std::vector<Actor*> remove_actor;
	for (auto a : actors)
	{
		if (a->GetState() == Actor::Dead)
		{
			remove_actor.emplace_back(a);
		}
	}

	for (auto a : remove_actor)
	{
		delete a;
	}
}

void Game::Output()
{
	renderer->Draw();
}

void Game::Load()
{
	/*Actor* a = new Actor(this);
	SpriteComponent* sc = new SpriteComponent(a);
	sc->SetTexture(renderer->GetTexture("Texture/test.bmp"));
	InputComponent* ic = new InputComponent(a);
	ic->SetKey1(SDL_SCANCODE_W);
	ic->SetKey2(SDL_SCANCODE_S);
	ic->SetKey3(SDL_SCANCODE_A);
	ic->SetKey4(SDL_SCANCODE_D);
	a->SetPosition(Vector2::Zero);
	a->SetRotation(Math::ToRadians(90.0f));*/

	//球
	/*Actor* a = new Actor(this);
	a->SetScale(10.0f);
	a->SetRotation(Quaternion(Vector3::UnitZ, Math::ToRadians(90.0f)));
	a->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	MeshComponent* mc = new MeshComponent(a);
	mc->SetMesh(renderer->GetMesh("Texture/test1.mesh"));*/

	//モデル
	//Actor* a = new Actor(this);
	//a->SetScale(Vector3(1.0f, 1.0f, 1.0f));
	//a->SetRotation(Quaternion::Concatenate(
	//	Quaternion(Vector3::UnitX, Math::ToRadians(-90.0f)),
	//	Quaternion(Vector3::UnitY, Math::ToRadians(-90.0f))));
	//a->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	///*SkinMeshComponent* sc = new SkinMeshComponent(a);
	//sc->SetMesh(renderer->GetMesh("Texture/test.gpmesh"));
	//sc->SetSkeleton(renderer->GetSkeleton("Texture/test.gpskel"));
	//sc->PlayAnimation(renderer->GetAnimation("Texture/test.gpanim"));*/
	//MeshComponent* mc = new MeshComponent(a);
	//mc->SetMesh(renderer->GetMesh("Texture/car.gpmesh"));

	//カメラ
	/*a = new CameraActor(this);
	a->SetPosition(Vector3(-1000.0f, 100.0f, 0.0f));*/

	Actor* a = new Car(this);
	a = new Actor(this);
	MeshComponent* mesh = new MeshComponent(a);
	mesh->SetMesh(renderer->GetMesh("Texture/table.gpmesh"));

	/*Cube* c;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			c = new Cube(this);
			c->SetPosition(Vector3(i * 100, j * 1000, 0.0f));
			cube.emplace_back(c);
		}
	}*/

	//ライト
	Vector3 ambient = Vector3(0.4f, 0.4f, 0.4f);
	DirectionalLight direcional_light;
	direcional_light.direction = Vector3(0.5f, -0.5f, -0.5f);
	direcional_light.diffuse_color = Vector3(0.7f, 0.7f, 0.7f);
	direcional_light.specular_color = Vector3(0.8f, 0.8f, 0.8f);
	renderer->SetAmbient(ambient);
	renderer->SetDirectionalLight(direcional_light);
}

void Game::Unload()
{
	while (!actors.empty())
	{
		delete actors.back();
	}

	if (renderer)
	{
		renderer->Unload();
	}
}