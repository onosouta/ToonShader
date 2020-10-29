#pragma once
#include "CameraComponent.h"

//�Ԃ̃J����
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

	float horizontal;	//����
	float vertical;		//����
	float target;

	float spring_constant;//�΂˒萔
	Vector3 real;//����
	Vector3 velocity;
};

