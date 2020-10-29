#pragma once
#include <string>

//テクスチャ
class Texture
{
public:
	Texture();
	~Texture();

	bool Load(const std::string& _name);
	void Unload();

	void SetActive();

	//ゲッター
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	int GetID() const { return texture_ID; }

private:
	int width;
	int height;

	//ID
	unsigned int texture_ID;
};