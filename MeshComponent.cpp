#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "Renderer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(Actor* _owner, bool _is_skin)
	:Component(_owner)
	, mesh(nullptr)
	, tex_index(0)
	, is_skin(_is_skin)
{
	owner->GetGame()->GetRenderer()->AddMeshComponent(this);
}

MeshComponent::~MeshComponent()
{
	owner->GetGame()->GetRenderer()->RemoveMeshComponent(this);
}

void MeshComponent::Draw(Shader* _shader)
{
	if (mesh)
	{
		glFrontFace(GL_CCW);
		glEnable(GL_CULL_FACE);

		glCullFace(GL_FRONT);

		//ワールド座標
		_shader->SetMatrixUniform(
			"world_transform",
			mesh->GetWolrd() * owner->GetWorld());

		float f1[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		_shader->SetFloat4Uniform("edge_color", f1);
		_shader->SetBoolUniform("edge", true);

		//テクスチャ
		glActiveTexture(GL_TEXTURE0);
		Texture* toon_tex = owner->GetGame()->GetRenderer()->GetTexture("Texture/toon.png");
		toon_tex->SetActive();
		_shader->SetTextureUniform("toon_tex", 0);
		glActiveTexture(GL_TEXTURE1);
		Texture* texture = mesh->GetTexture(tex_index);
		texture->SetActive();
		_shader->SetTextureUniform("tex", 1);

		//頂点配列オブジェクト
		VertexArray* vertex_array = mesh->GetVertexArray();
		vertex_array->SetActive();

		//描画
		glDrawElements(GL_TRIANGLES, vertex_array->GetIndexNum(), GL_UNSIGNED_INT, nullptr);



		glCullFace(GL_BACK);

		//ワールド座標
		_shader->SetMatrixUniform(
			"world_transform",
			mesh->GetWolrd() * owner->GetWorld());

		float f2[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
		_shader->SetFloat4Uniform("edge_color", f2);
		_shader->SetBoolUniform("edge", false);

		//テクスチャ
		glActiveTexture(GL_TEXTURE0);
		toon_tex->SetActive();
		_shader->SetTextureUniform("toon_tex", 0);
		glActiveTexture(GL_TEXTURE1);
		texture->SetActive();
		_shader->SetTextureUniform("tex", 1);

		//頂点配列オブジェクト
		vertex_array = mesh->GetVertexArray();
		vertex_array->SetActive();

		//描画
		glDrawElements(GL_TRIANGLES, vertex_array->GetIndexNum(), GL_UNSIGNED_INT, nullptr);
	}
}