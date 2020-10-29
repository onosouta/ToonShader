#pragma once
#include <string>
#include <unordered_map>
#include "Math.h"
#include "SDL.h"

//���s����
struct DirectionalLight
{
	Vector3 direction;
	Vector3 diffuse_color;
	Vector3 specular_color;
};

//�����_���[
class Renderer
{
public:
	Renderer(class Game* _game);
	~Renderer();

	bool Initialize(float _screen_width, float _screen_height);
	void Shutdown();

	void Unload();

	void Draw();

	//�X�v���C�g
	void AddSprite(class SpriteComponent* _sprite);
	void RemoveSprite(class SpriteComponent* _sprite);

	//���b�V��
	void AddMeshComponent(class MeshComponent* _mesh_component);
	void RemoveMeshComponent(class MeshComponent* _mesh_component);

	//�Q�b�^�[
	//SDL_Texture* GetTexture(const std::string& _name);
	class Texture* GetTexture(const std::string& _name);
	//class Mesh* GetMesh(const std::string& _name);
	class Mesh* GetMesh(const char* _name);
	class Skeleton* GetSkeleton(const std::string& _name);
	class Animation* GetAnimation(const std::string& _name);

	//�Z�b�^�[
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

	SDL_Window* window;		//�E�B���h�E
	SDL_GLContext context;	//OpenGL�R���e�N�X�g
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

	Matrix4 view;		//�r���[�s��
	Matrix4 projection;	//�ˉe�s��

	Vector3 ambient;					//����
	DirectionalLight directional_light;	//���s����
};