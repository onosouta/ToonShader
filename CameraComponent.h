#pragma once
#include "Component.h"
#include "Math.h"

//�J�����R���|�[�l���g
class CameraComponent : public Component
{
public:
	CameraComponent(class Actor* _owner, int order = 200);

protected:
	void SetView(const Matrix4& _view);//�r���[��ݒ�
};