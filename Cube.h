#pragma once
#include "Actor.h"

class Cube : public Actor
{
public:
	Cube(class Game* _game);

	class MeshComponent* GetMesh() { return mesh; }
	class BoxComponent* GetBox() { return box; }

private:
	class MeshComponent* mesh;
	class BoxComponent* box;
};

