#pragma once
#include <string>
#include <unordered_map>
#include "Math.h"
#include "SDL.h"

//平行光源
struct DirectionalLight
{
	Vector3 direction;
	Vector3 diffuse_color;
	Vector3 specular_color;
};

//レンダラー
class Renderer
{
public:
	Renderer(class Game* _game);
	~Renderer();

	bool Initialize(float _screen_width, float _screen_height);
	void Shutdown();

	void Unload();

	void Draw();

	//スプライト
	void AddSprite(class SpriteComponent* _sprite);
	void RemoveSprite(class SpriteComponent* _sprite);

	//メッシュ
	void AddMeshComponent(class MeshComponent* _mesh_component);
	void RemoveMeshComponent(class MeshComponent* _mesh_component);

	//ゲッター
	//SDL_Texture* GetTexture(const std::string& _name);
	class Texture* GetTexture(const std::string& _name);
	//class Mesh* GetMesh(const std::string& _name);
	class Mesh* GetMesh(const char* _name);
	class Skeleton* GetSkeleton(const std::string& _name);
	class Animation* GetAnimation(const std::string& _name);

	//セッター
	void SetView(const Matrix4& _view) { view = _view; }
	void SetAmbient(const Vector3& _ambient) { ambient = _ambient; }
	void SetDirectionalLight(const DirectionalLight& _directional_light) { directional_light = _directional_light; }

private:
	bool LoadShader();
	void CreateSpriteVertex();
	void SetLightUniform(class Shader* _shader);

	class Game* game;

	float screen_width;
	float screen_height;

	SDL_Window* window;		//ウィンドウ
	SDL_GLContext context;	//OpenGLコンテクスト
	//SDL_Renderer* renderer;

	std::vector<class SpriteComponent*> sprites;
	std::vector<class MeshComponent*> mesh_components;
	std::vector<class SkinMeshComponent*> skin_components;

	//std::unordered_map<std::string, SDL_Texture*> textures;
	std::unordered_map<std::string, class Texture*> textures;
	std::unordered_map<std::string, class Mesh*> meshes;
	std::unordered_map<std::string, class Skeleton*> skeletons;
	std::unordered_map<std::string, class Animation*> animations;

	class Shader* sprite_shader;
	class Shader* mesh_shader;
	class Shader* skin_shader;
	class Shader* toon_shader;
	class VertexArray* sprite_vertex;

	Matrix4 view;		//ビュー行列
	Matrix4 projection;	//射影行列

	Vector3 ambient;					//環境光
	DirectionalLight directional_light;	//平行光源
};