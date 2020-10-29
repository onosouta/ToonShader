#include "VertexArray.h"
#include "glew.h"

VertexArray::VertexArray(
	const void* _vertices, unsigned int _vertex_num,
	const unsigned int* _indices, unsigned int _index_num,
	Layout _layout)
	:vertex_num(_vertex_num)
	,index_num(_index_num)
{
	//頂点配列オブジェクト
	glGenVertexArrays(1, &vertex_array_ID);
	glBindVertexArray(vertex_array_ID);

	unsigned vertex_size = 8 * sizeof(float);
	if (_layout == SkinMesh)
	{
		vertex_size = 8 * sizeof(float) + 8 * sizeof(char);
	}

	//頂点バッファ
	glGenBuffers(1, &vertex_buffer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_ID);
	glBufferData(GL_ARRAY_BUFFER, _vertex_num * vertex_size, _vertices, GL_STATIC_DRAW);

	//インデックスバッファ
	glGenBuffers(1, &index_buffer_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _index_num * sizeof(unsigned int), _indices, GL_STATIC_DRAW);

	//頂点レイアウト

	if (_layout == Mesh)
	{
		//x, y, z
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, 0);
		//x, y, z 法線
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size, reinterpret_cast<void*>(sizeof(float) * 3));
		//u, v
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_size, reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (_layout == SkinMesh)
	{
		//x, y, z
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertex_size, 0);
		//x, y, z 法線
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertex_size, reinterpret_cast<void*>(sizeof(float) * 3));

		//ボーン
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertex_size, reinterpret_cast<void*>(sizeof(float) * 6));
		//ウェイト
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertex_size, reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));

		//u, v
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertex_size, reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertex_buffer_ID);
	glDeleteBuffers(1, &index_buffer_ID);
	glDeleteVertexArrays(1, &vertex_array_ID);
}

void VertexArray::SetActive()
{
	glBindVertexArray(vertex_array_ID);
}