#pragma once

//VAO
class VertexArray
{
public:
	enum Layout
	{
		Mesh,
		SkinMesh,
	};

	VertexArray(
		const void* _vertices, unsigned int _vertex_num,		//���_�o�b�t�@
		const unsigned int* _indices, unsigned int _index_num,	//�C���f�b�N�X�o�b�t�@
		Layout _layout);										//���C�A�E�g
	~VertexArray();

	void SetActive();

	unsigned int GetVertexNum() const { return vertex_num; }
	unsigned int GetIndexNum() const { return index_num; }

private:
	unsigned int vertex_num;
	unsigned int index_num;

	//OpenGL ID
	unsigned int vertex_buffer_ID;
	unsigned int index_buffer_ID;
	unsigned int vertex_array_ID;
};