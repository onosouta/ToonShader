#pragma once
#include <vector>
#include "SpriteComponent.h"

//�A�j���[�V�����R���|�[�l���g
class AnimationComponent : public SpriteComponent
{
public:
	AnimationComponent(class Actor* _owner, int  _order = 100);

	void Update(float _delta_time) override;

	//void SetTextures(const std::vector<SDL_Texture*>& _textures);
	void SetTextures(const std::vector<class Texture*>& _textures);

	float GetFPS() const { return fps; }
	void SetFPS(float _fps) { fps = _fps; }

private:
	//std::vector<SDL_Texture*> textures;
	std::vector<class Texture*> textures;//�e�N�X�`��
	float frame;	//�t���[����
	float fps;		//�t���[�����[�g
};