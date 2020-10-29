#pragma once
#include "Component.h"
#include "Math.h"

//カメラコンポーネント
class CameraComponent : public Component
{
public:
	CameraComponent(class Actor* _owner, int order = 200);

protected:
	void SetView(const Matrix4& _view);//ビューを設定
};