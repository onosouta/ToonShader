#pragma once
#include <string>

//�e�N�X�`��
class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& _name);
	void Unload();

	void SetActive();

	//�Q�b�^�[
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetID() const { return texture_ID; }

private:
	int width;
	int height;

	//ID
	unsigned int texture_ID;
};