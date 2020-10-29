#pragma once
#include "Bone.h"
#include "Collision.h"
#include "Math.h"
#include <string>
#include <vector>
#include "VertexArray.h"

//���b�V��
class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& _name, class Renderer* _renderer);
	void Unload();

	class Texture* GetTexture(size_t _i);

	//�Q�b�^�[
	const std::string& GetShaderName() const { return shader_name; }
	const std::vector<class Texture*>& GetTextures() const { return textures; }
	class VertexArray* GetVertexArray() const { return vertex_array; }
	const AABB& GetAABB() const { return aabb; }
	const Matrix4& GetWolrd() const { return world; }

	//�Z�b�^�[
	void SetTextures(const std::vector<class Texture*>& _textures) { textures = _textures; }
	void SetVertexArray(class VertexArray* _vertex_array) { vertex_array = _vertex_array; }
	void SetWorld(const Matrix4& _world) { world = _world; }

private:
	std::string shader_name;				//�V�F�[�_�[
	std::vector<class Texture*> textures;	//�e�N�X�`��

	class VertexArray* vertex_array;

	AABB aabb;

	Matrix4 world;
	float radius;//���a
};