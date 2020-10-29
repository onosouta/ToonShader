#pragma once
#include "CameraComponent.h"

//Ô‚ÌƒJƒƒ‰
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

	float horizontal;	//…•½
	float vertical;		//‚’¼
	float target;

	float spring_constant;//‚Î‚Ë’è”
	Vector3 real;//ÀÛ
	Vector3 velocity;
};

