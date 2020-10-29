#pragma once
#include "Component.h"
#include <vector>

//���b�V���R���|�[�l���g
class MeshComponent : public Component
{
public:
	MeshComponent(class Actor* _owner, bool _is_skin = false);
	~MeshComponent();

	virtual void Draw(class Shader* _shader);

	//�Q�b�^�[
	bool GetIsSkin() { return is_skin; }
	class Mesh* GetMeshes() { return mesh; }

	//�Z�b�^�[
	virtual void SetMesh(class Mesh* _mesh) { mesh = _mesh; }
	void SetTextureIndex(size_t _tex_index) { tex_index = _tex_index; }

protected:
	class Mesh* mesh;//���b�V��
	size_t tex_index;

	bool is_skin;
};