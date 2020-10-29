#pragma once
#include <vector>
#include "SDL.h"
#include "Math.h"

//アクター
class Actor
{
public:
	enum State
	{
		Active,
		Pause,
		Dead,
	};

	Actor(class Game* _game);
	virtual ~Actor();

	void Input(const Uint8* _key);
	void Update(float _delta_time);

	void WorldTransform();

	//コンポーネント
	void UpdateComponent(float _delta_time);
	void AddComponent(class Component* _component);
	void RemoveComponent(class Component* _component);

	//オーバーライド
	virtual void ActorInput(const Uint8* _key) {}
	virtual void ActorUpdate(float _delta_time) {}

	//ゲッター
	State GetState() const { return state; }
	const Matrix4& GetWorld() const { return world; }
	const Vector3& GetScale() const { return scale; }
	const Quaternion& GetRotation() const { return rotation; }
	const Vector3& GetPosition() const { return position; }
	class Game* GetGame() { return game; }

	//前方ベクトル
	Vector3 GetFront() const { return Vector3::Transform(Vector3::UnitX, rotation); }

	//セッター
	void SetState(State _state) { state = _state; }
	void SetScale(const Vector3& _scale) { scale = _scale; is_recalculate = true; }
	void SetRotation(const Quaternion& _rotation) { rotation = _rotation; is_recalculate = true; }
	void SetPosition(const Vector3& _position) { position = _position; is_recalculate = true; }

private:
	State state;

	bool is_recalculate;
	Matrix4 world;//ワールド行列

	Vector3 scale;
	Quaternion rotation;
	Vector3 position;

	std::vector<class Component*> components;//コンポーネント
	class Game* game;
};