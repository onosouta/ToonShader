#include "CarCamera.h"
#include "Actor.h"

CarCamera::CarCamera(Actor* _owner)
	:CameraComponent(_owner)
	,horizontal(400.0f)
	,vertical(150.0f)
	,spring_constant(128.0f)
{}

void CarCamera::Initialize()
{
	/*real = CameraPosition();

	velocity = Vector3::Zero;

	Vector3 target_position = owner->GetPosition() + owner->GetFront() * target;
	Matrix4 view = Matrix4::CreateLookAt(
		real,
		target_position,
		Vector3::UnitZ);*/
	Matrix4 view = Matrix4::CreateLookAt(
		Vector3(0, 0, 100.0f),
		Vector3::Zero,
		Vector3::UnitZ);
	SetView(view);
}

void CarCamera::Update(float _delta_time)
{
	//CameraComponent::Update(_delta_time);

	//float delay = 2.0f * Math::Sqrt(spring_constant);//ばね定数から計算

	//Vector3 ideal = CameraPosition();//理想
	//Vector3 difference = real - ideal;
	////加速度
	//Vector3 acceleration = -spring_constant * difference - delay * velocity;
	////速度
	//velocity += acceleration * _delta_time;

	//real += velocity * _delta_time;

	//Vector3 target_position = owner->GetPosition();// +owner->GetFront() * target;
	Matrix4 view = Matrix4::CreateLookAt(
		Vector3(500.0f, 500.0f, 250.0f),
		Vector3::Zero,
		Vector3::UnitZ);
	SetView(view);//ビューを設定
}

Vector3 CarCamera::CameraPosition() const
{
	Vector3 camera_position = owner->GetPosition();
	camera_position -= owner->GetFront() * horizontal;	//水平
	camera_position += Vector3::UnitZ * vertical;		//垂直
	return camera_position;
}