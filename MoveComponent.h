#pragma once
#include "Component.h"

//移動コンポーネント
class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* _owner, int _order = 10);

	void Update(float _delta_time) override;

	//ゲッター
	float GetAngleSpeed() const { return angle_speed; }
	float GetFrontSpeed() const { return front_speed; }
	//セッター
	void SetAngleSpeed(float _angle_speed) { angle_speed = _angle_speed; }
	void SetFrontSpeed(float _front_speed) { front_speed = _front_speed; }

private:
	float angle_speed;
	float front_speed;
};