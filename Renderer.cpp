#include "Renderer.h"
#include "Animation.h"
#include "glew.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Shader.h"
#include "Skeleton.h"
#include "SkinMeshComponent.h"
#include "SpriteComponent.h"
#include "Texture.h"
#include "VertexArray.h"

Renderer::Renderer(Game* _game)
	:game(_game)
{}

Renderer::~Renderer()
{}

bool Renderer::Initialize(float _screen_width, float _screen_height)
{
	screen_width = _screen_width;
	screen_height = _screen_height;

	//コアプロファイル
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	//バージョン 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	//チャンネル 8ビット
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);	//R
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);	//G
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);	//B
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);	//A
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);	//デプスバッファ
	//ダブルバッファ
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//ハードウェアアクセラレーション
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	//ウィンドウ
	window = SDL_CreateWindow(
		"TOON SHADER",							//title
		100,								//x
		100,								//y
		static_cast<int>(screen_width),		//w
		static_cast<int>(screen_height),	//h
		SDL_WINDOW_OPENGL);					//flags

	if (!window)
	{
		SDL_Log("failed to create window : %s", SDL_GetError());
		return false;
	}

	//コンテクスト
	context = SDL_GL_CreateContext(window);

	//GLEWを初期化
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("failed to GLEW initialize");
		return false;
	}
	glGetError();

	//シェーダーをロード
	if (!LoadShader())
	{
		SDL_Log("failed to load shader");
		return false;
	}

	//頂点を作成
	CreateSpriteVertex();

	//レンダラー
	//renderer = SDL_CreateRenderer(
	//	window,													//window
	//	-1,														//index
	//	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);	//flags

	//if (!renderer)
	//{
	//	SDL_Log("failed to create renderer : %s", SDL_GetError());
	//	return false;
	//}

	//if (IMG_Init(IMG_INIT_PNG) == 0)//png
	//{
	//	SDL_Log("cannnot initialize SDL_image : %s", SDL_GetError());
	//	return false;
	//}

	return true;
}

void Renderer::Shutdown()
{
	//IMG_Quit();

	delete sprite_vertex;
	sprite_shader->Unload();
	delete sprite_shader;

	//SDL_DestroyRenderer(renderer);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
}

void Renderer::Unload()
{
	for (auto t : textures)
	{
		//SDL_DestroyTexture(t.second);
		t.second->Unload();
		delete t.second;
	}
	textures.clear();

	for (auto m : meshes)
	{
		m.second->Unload();
		delete m.second;
	}
	meshes.clear();
}

void Renderer::Draw()
{
	/*SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
	SDL_RenderClear(renderer);

	for (auto s : sprites)
	{
		s->Draw(renderer);
	}

	SDL_RenderPresent(renderer);*/

	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);//深度テスト

	//メッシュ
	//mesh_shader->SetActive();
	//mesh_shader->SetMatrixUniform("view_projection", view * projection);
	//SetLightUniform(mesh_shader);//ライティング
	toon_shader->SetActive();
	toon_shader->SetMatrixUniform("view_projection", view * projection);
	SetLightUniform(toon_shader);
	for (auto m : mesh_components)
	{
		m->Draw(toon_shader);
	}

	//スキン
	skin_shader->SetActive();
	skin_shader->SetMatrixUniform("view_projection", view * projection);
	SetLightUniform(skin_shader);//ライティング
	for (auto s : skin_components)
	{
		s->Draw(skin_shader);
	}

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);//アルファブレンド

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//スプライト
	sprite_shader->SetActive();
	sprite_vertex->SetActive();
	for (auto s : sprites)
	{
		s->Draw(sprite_shader);
	}

	SDL_GL_SwapWindow(window);
}

void Renderer::AddSprite(SpriteComponent* _sprite)
{
	int order = _sprite->GetOrder();
	auto i = sprites.begin();
	for (; i != sprites.end(); ++i)
	{
		if (order < (*i)->GetOrder())
		{
			break;
		}
	}

	sprites.insert(i, _sprite);
}

void Renderer::RemoveSprite(SpriteComponent* _sprite)
{
	auto i = std::find(sprites.begin(), sprites.end(), _sprite);
	sprites.erase(i);
}

void Renderer::AddMeshComponent(MeshComponent* _mesh_component)
{
	if (_mesh_component->GetIsSkin())
	{
		SkinMeshComponent* sc = static_cast<SkinMeshComponent*>(_mesh_component);
		skin_components.emplace_back(sc);
	}
	else
	{
		mesh_components.emplace_back(_mesh_component);
	}
}

void Renderer::RemoveMeshComponent(MeshComponent* _mesh_component)
{
	if (_mesh_component->GetIsSkin())
	{
		SkinMeshComponent* sc = static_cast<SkinMeshComponent*>(_mesh_component);
		auto i = std::find(skin_components.begin(), skin_components.end(), sc);
		skin_components.erase(i);
	}
	else
	{
		auto i = std::find(mesh_components.begin(), mesh_components.end(), _mesh_component);
		mesh_components.erase(i);
	}
}

bool Renderer::LoadShader()
{
	//スプライト
	sprite_shader = new Shader();
	if (!sprite_shader->Load("Sprite.v", "Sprite.f"))
	{
		return false;
	}
	sprite_shader->SetActive();
	sprite_shader->SetMatrixUniform("view_projection", Matrix4::ViewProjection(screen_width, screen_height));

	//メッシュ
	mesh_shader = new Shader();
	if (!mesh_shader->Load("Phong.v", "Phong.f"))
	{
		return false;
	}
	mesh_shader->SetActive();

	//スキン
	skin_shader = new Shader();
	if (!skin_shader->Load("Skin.v", "Phong.f"))
	{
		return false;
	}
	skin_shader->SetActive();

	toon_shader = new Shader();
	if (!toon_shader->Load("Toon.v", "Toon.f"))
	{
		return false;
	}
	toon_shader->SetActive();

	//ビュー
	view = Matrix4::CreateLookAt(
		Vector3::Zero,
		Vector3::Zero,
		Vector3::UnitY);

	//プロジェクション
	projection = Matrix4::CreatePerspective(
		Math::ToRadians(45.0f),
		screen_width,
		screen_height,
		5.0f,
		50000.0f);

	mesh_shader->SetMatrixUniform("view_projection", view * projection);
	skin_shader->SetMatrixUniform("view_projection", view * projection);
	toon_shader->SetMatrixUniform("view_projection", view * projection);

	return true;
}

Texture* Renderer::GetTexture(const std::string& _name)
{
	Texture* t = nullptr;

	auto i = textures.find(_name);
	if (i != textures.end())
	{
		t = i->second;
	}
	else
	{
		t = new Texture();
		if (t->Load(_name))
		{
			textures.emplace(_name, t);
		}
		else
		{
			delete t;
			t = nullptr;
		}
	}

	return t;
}

//Mesh* Renderer::GetMesh(const std::string& _name)
Mesh* Renderer::GetMesh(const char* _name)
{
	Mesh* m = nullptr;

	auto i = meshes.find(_name);
	if (i != meshes.end())
	{
		m = i->second;
	}
	else
	{
		m = new Mesh();
		if (m->Load(_name, this))
		{
			meshes.emplace(_name, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}

	return m;
}

Skeleton* Renderer::GetSkeleton(const std::string& _name)
{
	Skeleton* s = nullptr;

	auto i = skeletons.find(_name);
	if (i != skeletons.end())
	{
		s = i->second;
	}
	else
	{
		s = new Skeleton();
		if (s->Load(_name))
		{
			skeletons.emplace(_name, s);
		}
		else
		{
			delete s;
			s = nullptr;
		}
	}

	return s;
}

Animation* Renderer::GetAnimation(const std::string& _name)
{
	Animation* a = nullptr;

	auto i = animations.find(_name);
	if (i != animations.end())
	{
		a = i->second;
	}
	else
	{
		a = new Animation();
		if (a->Load(_name))
		{
			animations.emplace(_name, a);
		}
		else
		{
			delete a;
			a = nullptr;
		}
	}

	return a;
}

void Renderer::CreateSpriteVertex()
{
	//頂点バッファ
	float vertices[] =
	{
		//x     y     z     x     y     z     u     v
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,//左上
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,//右上
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,//右下
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,//左下
	};

	//インデックスバッファ
	unsigned int indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};

	sprite_vertex = new VertexArray(vertices, 4, indices, 6, VertexArray::Mesh);
}

void Renderer::SetLightUniform(Shader* _shader)
{
	//カメラ
	Matrix4 camera_view = view;
	camera_view.Invert();//反転
	_shader->SetVectorUniform("camera_pos", camera_view.GetTranslation());
	//環境光
	_shader->SetVectorUniform("ambient", ambient);
	//平行光源
	_shader->SetVectorUniform("directional_light.direction", directional_light.direction);
	_shader->SetVectorUniform("directional_light.diffuse_color", directional_light.diffuse_color);
	_shader->SetVectorUniform("directional_light.specular_color", directional_light.specular_color);
}

//SDL_Texture* Game::GetTexture(const std::string& _name)
//{
//	SDL_Texture* t = nullptr;
//
//	auto i = textures.find(_name);
//	if (i != textures.end())
//	{
//		t = i->second;
//	}
//	else
//	{
//		SDL_Surface* surface = IMG_Load(_name.c_str());
//		if (!surface)
//		{
//			SDL_Log("failed to load texture file : %s", _name.c_str());
//			return nullptr;
//		}
//
//		t = SDL_CreateTextureFromSurface(renderer, surface);
//		SDL_FreeSurface(surface);
//		if (!t)
//		{
//			SDL_Log("failed to convert texture : %s", _name.c_str());
//			return nullptr;
//		}
//
//		textures.emplace(_name.c_str(), t);
//	}
//
//	return t;
//}