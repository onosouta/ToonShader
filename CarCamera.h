#pragma once
#include "CameraComponent.h"

//車のカメラ
class CarCamera : public CameraComponent
{
public:
	CarCamera(class Actor* _owner);

	void Initialize();

	void Update(float _delta_time) override;

	void SetHorizontal(float _horizontal) { horizontal = _horizontal; }
	void SetVertical(float _vertical) { vertical = _vertical; }
	void SetTarget(float _target) { target = _target; }
	void SetSpringConstant(float _spring_constant) { spring_constant = _spring_constant; }

private:
	Vector3 CameraPosition() const;

	float horizontal;	//水平
	float vertical;		//垂直
	float target;

	float spring_constant;//ばね定数
	Vector3 real;//実際
	Vector3 velocity;
};

