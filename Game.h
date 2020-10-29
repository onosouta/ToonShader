#pragma once
#include <unordered_map>
#include <vector>
#include "SDL.h"

//ÉQÅ[ÉÄ
class Game
{
public:
	Game();
	bool Initialize();
	void GameLoop();
	void Shutdown();

	void AddActor(class Actor* _actor);
	void RemoveActor(class Actor* _actor);

	//ÉQÉbÉ^Å[
	float GetScreenWidth() const { return screen_width; }
	float GetScreenHeight() const { return screen_height; }

	class Renderer* GetRenderer() { return renderer; }
	class Physics* GetPhysics() { return physics; }

	class std::vector<class Cube*> GetCube() { return cube; }

private:
	void Input();
	void Update();
	void Output();
	void Load();
	void Unload();

	bool is_running;
	Uint32 tick_count;

	float screen_width;
	float screen_height;

	bool is_updating;
	std::vector<class Actor*> actors;
	std::vector<class Actor*> add_actors;

	class Renderer* renderer;
	class Physics* physics;

	std::vector<class Cube*> cube;
};