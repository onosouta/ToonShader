#include "Cube.h"
#include "BoxComponent.h"
#include "Game.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Renderer.h"

Cube::Cube(Game* _game)
	:Actor(_game)
{
	mesh = new MeshComponent(this);
	Mesh* m = GetGame()->GetRenderer()->GetMesh("Texture/building1.gpmesh");
	mesh->SetMesh(m);
	box = new BoxComponent(this);
	box->SetBox(m->GetAABB());
	box->SetIsRotate(true);
	Quaternion q = Quaternion(Vector3::UnitZ, Math::ToRadians(90.0f));
	SetRotation(q);
}