#pragma once
#include "Component.h"
#include <vector>

//メッシュコンポーネント
class MeshComponent : public Component
{
public:
	MeshComponent(class Actor* _owner, bool _is_skin = false);
	~MeshComponent();

	virtual void Draw(class Shader* _shader);

	//ゲッター
	bool GetIsSkin() { return is_skin; }
	class Mesh* GetMeshes() { return mesh; }

	//セッター
	virtual void SetMesh(class Mesh* _mesh) { mesh = _mesh; }
	void SetTextureIndex(size_t _tex_index) { tex_index = _tex_index; }

protected:
	class Mesh* mesh;//メッシュ
	size_t tex_index;

	bool is_skin;
};