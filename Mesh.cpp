#include "Mesh.h"
#include <algorithm>
#include "document.h"
#include <fstream>
#include "Game.h"
#include "Math.h"
#include "Renderer.h"
#include <sstream>
#include <stdio.h>
#include "VertexArray.h"

//���_
union Vertex
{
	float f;
	Uint8 u[4];
};

Mesh::Mesh()
	:radius(0.0f)
	,aabb(Vector3::Infinity, -Vector3::Infinity)
{}

Mesh::~Mesh()
{}

//���b�V����ǂݍ���
bool Mesh::Load(const std::string& _name, Renderer* _renderer)
{
	std::ifstream mesh_file(_name);
	if (!mesh_file.is_open())
	{
		SDL_Log("%s file not found", _name.c_str());
		return false;
	}

	std::stringstream s_stream;
	s_stream << mesh_file.rdbuf();
	std::string contents = s_stream.str();

	//RapidJSON
	rapidjson::StringStream string_stream(contents.c_str());
	rapidjson::Document document;
	document.ParseStream(string_stream);

	std::string json_layout = document["vertexformat"].GetString();//���_���C�A�E�g

#pragma region ���_���C�A�E�g�����[�h

	VertexArray::Layout layout = VertexArray::Mesh;
	size_t vertex_size = 8;

	if (json_layout == "PosNormSkinTex")
	{
		layout = VertexArray::SkinMesh;
		vertex_size = 10;
	}

#pragma endregion

	rapidjson::Value& json_texture = document["textures"];//�e�N�X�`��
	rapidjson::Value& json_vertex = document["vertices"];//���_�o�b�t�@
	rapidjson::Value& json_index = document["indices"];//�C���f�b�N�X�o�b�t�@

#pragma region �e�N�X�`�������[�h

	for (rapidjson::SizeType i = 0; i < json_texture.Size(); i++)
	{
		Texture* tex = _renderer->GetTexture(json_texture[i].GetString());
		if (tex == nullptr)
		{
			tex = _renderer->GetTexture("Texture/none.png");//�f�t�H���g
		}

		//�ǉ�
		textures.emplace_back(tex);
	}

#pragma endregion

#pragma region ���_�o�b�t�@�����[�h

	std::vector<Vertex> vertices;//���_�o�b�t�@
	vertices.reserve(json_vertex.Size() * vertex_size);

	for (rapidjson::SizeType i = 0; i < json_vertex.Size(); i++)
	{
		const rapidjson::Value& vertex = json_vertex[i];

		Vector3 pos(
			vertex[0].GetFloat(),	//x
			vertex[1].GetFloat(),	//y
			vertex[2].GetFloat());	//z

		radius = Math::Max(radius, pos.LengthSqare());//���a
		aabb.Update(pos);

		if (layout == VertexArray::Mesh)
		{
			Vertex _vertex;

			//�ǉ�
			for (rapidjson::SizeType j = 0; j < vertex.Size(); j++)
			{
				_vertex.f = static_cast<float>(vertex[j].GetDouble());
				vertices.emplace_back(_vertex);
			}
		}
		else
		{
			Vertex _vertex;

			//x, y, z, x, y, z �@��
			for (rapidjson::SizeType j = 0; j < 6; j++)
			{
				_vertex.f = static_cast<float>(vertex[j].GetDouble());
				vertices.emplace_back(_vertex);
			}

			//bone, weight
			for (rapidjson::SizeType j = 6; j < 14; j += 4)
			{
				_vertex.u[0] = vertex[j].GetUint();
				_vertex.u[1] = vertex[j + 1].GetUint();
				_vertex.u[2] = vertex[j + 2].GetUint();
				_vertex.u[3] = vertex[j + 3].GetUint();
				vertices.emplace_back(_vertex);
			}

			//u, v
			for (rapidjson::SizeType j = 14; j < vertex.Size(); j++)
			{
				_vertex.f = vertex[j].GetDouble();
				vertices.emplace_back(_vertex);
			}
		}
	}

#pragma endregion

#pragma region �C���f�b�N�X�o�b�t�@�����[�h

	std::vector<unsigned int> indices;//�C���f�b�N�X�o�b�t�@
	indices.reserve(json_index.Size() * 3);

	for (rapidjson::SizeType i = 0; i < json_index.Size(); i++)
	{
		rapidjson::Value& index = json_index[i];

		//�ǉ�
		indices.emplace_back(index[0].GetUint());//1
		indices.emplace_back(index[1].GetUint());//2
		indices.emplace_back(index[2].GetUint());//3
	}

#pragma endregion

	shader_name = document["shader"].GetString();//�V�F�[�_�[��

	//���_�z��I�u�W�F�N�g����
	vertex_array = new VertexArray(
		vertices.data(),
		static_cast<unsigned>(vertices.size()) / vertex_size,
		indices.data(),
		static_cast<unsigned>(indices.size()),
		layout);

	//���a
	radius = Math::Sqrt(radius);

	return true;
}

void Mesh::Unload()
{
	delete vertex_array;
	vertex_array = nullptr;
}

Texture* Mesh::GetTexture(size_t _i)
{
	if (_i < textures.size())
	{
		return textures[_i];
	}
	else
	{
		return nullptr;
	}
}