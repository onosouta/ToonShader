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
		const void* _vertices, unsigned int _vertex_num,		//頂点バッファ
		const unsigned int* _indices, unsigned int _index_num,	//インデックスバッファ
		Layout _layout);										//レイアウト
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