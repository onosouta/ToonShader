#include "Shader.h"
#include <fstream>
#include <sstream>
#include "SDL.h"

Shader::Shader()
	:vertex_shader_ID(0)
	,fragment_shader_ID(0)
	,shader_ID(0)
{}

Shader::~Shader()
{}

bool Shader::Load(
	const std::string& _vertex_name,
	const std::string& _fragment_name)
{
	//コンパイル
	if (!CompileShader(_vertex_name, GL_VERTEX_SHADER, vertex_shader_ID) ||
		!CompileShader(_fragment_name, GL_FRAGMENT_SHADER, fragment_shader_ID))
	{
		return false;
	}

	//シェーダープログラムを作成
	shader_ID = glCreateProgram();
	glAttachShader(shader_ID, vertex_shader_ID);
	glAttachShader(shader_ID, fragment_shader_ID);
	//リンク
	glLinkProgram(shader_ID);

	if (!IsLinked())
	{
		return false;
	}

	return true;
}

void Shader::Unload()
{
	glDeleteProgram(shader_ID);
	glDeleteShader(vertex_shader_ID);
	glDeleteShader(fragment_shader_ID);
}

void Shader::SetActive()
{
	glUseProgram(shader_ID);
}

void Shader::SetMatrixUniform(const char* _name, const Matrix4& _m)
{
	GLuint location = glGetUniformLocation(shader_ID, _name);
	glUniformMatrix4fv(location, 1, GL_TRUE, _m.GetPointer());
}

void Shader::SetMatrixUniform(const char* _name, const Matrix4& _m, float _size)
{
	GLuint location = glGetUniformLocation(shader_ID, _name);
	glUniformMatrix4fv(location, _size, GL_TRUE, _m.GetPointer());
}

void Shader::SetVectorUniform(const char* _name, const Vector3& _v)
{
	GLuint location = glGetUniformLocation(shader_ID, _name);
	glUniform3fv(location, 1, _v.GetPointer());
}

void Shader::SetFloat4Uniform(const char* _name, const float* _f)
{
	GLuint location = glGetUniformLocation(shader_ID, _name);
	glUniform4fv(location, 1, _f);
}

void Shader::SetBoolUniform(const char* _name, const bool _b)
{
	GLuint location = glGetUniformLocation(shader_ID, _name);
	glUniform1i(location, _b);
}

void Shader::SetTextureUniform(const char* _name, const unsigned int _ui)
{
	GLuint location = glGetUniformLocation(shader_ID, _name);
	glUniform1i(location, _ui);
}

bool Shader::CompileShader(const std::string& _file_name, GLenum _shader_type, GLuint& _shader)
{
	//ファイルを開く
	std::ifstream shader_file(_file_name);

	if (shader_file.is_open())
	{
		std::stringstream s_stream;
		s_stream << shader_file.rdbuf();
		std::string contents = s_stream.str();
		const char* contents_char = contents.c_str();

		_shader = glCreateShader(_shader_type);
		glShaderSource(_shader, 1, &(contents_char), nullptr);
		glCompileShader(_shader);//コンパイル

		if (!IsCompiled(_shader))
		{
			SDL_Log("failed to compile shader : %s", _file_name.c_str());
			return false;
		}
	}
	else
	{
		SDL_Log("shader file not found : %s", _file_name.c_str());
		return false;
	}

	return true;
}

bool Shader::IsCompiled(GLuint _shader)
{
	GLint is_compiled;//コンパイル状態
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &is_compiled);

	if (is_compiled != GL_TRUE)
	{
		char buffer[512];//文字列
		memset(buffer, 0, 512);
		glGetShaderInfoLog(_shader, 511, nullptr, buffer);

		SDL_Log("GLSL compilation failed : \n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsLinked()
{
	GLint is_linked;//リンク状態
	glGetProgramiv(shader_ID, GL_LINK_STATUS, &is_linked);

	if (is_linked != GL_TRUE)
	{
		char buffer[512];//文字列
		memset(buffer, 0, 512);
		glGetProgramInfoLog(shader_ID, 511, nullptr, buffer);

		SDL_Log("GLSL link failed : %s", buffer);
		return false;
	}

	return true;
}