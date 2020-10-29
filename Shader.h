#pragma once
#include <string>
#include "glew.h"
#include "Math.h"

//�V�F�[�_�[
class Shader
{
public:
	Shader();
	~Shader();

	bool Load(
		const std::string& _vertex_name,	//���_�V�F�[�_�[
		const std::string& _fragment_name);	//�t���O�����g�V�F�[�_�[
	void Unload();

	void SetActive();

	void SetMatrixUniform(const char* _name, const Matrix4& _m);
	void SetMatrixUniform(const char* _name, const Matrix4& _m, float _size);
	void SetVectorUniform(const char* _name, const Vector3& _v);
	void SetFloat4Uniform(const char* _name, const float* _f);
	void SetBoolUniform(const char* _name, const bool _b);
	void SetTextureUniform(const char* _name, const unsigned int _ui);

private:
	bool CompileShader(const std::string& _name, GLenum _shader_type, GLuint& _shader);

	bool IsCompiled(GLuint _shader);	//�R���p�C��
	bool IsLinked();					//�����N

	//ID
	GLuint vertex_shader_ID;
	GLuint fragment_shader_ID;
	GLuint shader_ID;
};