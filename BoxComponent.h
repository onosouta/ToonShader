#pragma once
#include "Component.h"
#include "Collision.h"

//ボックスコンポーネント
class BoxComponent : public Component
{
public:
	BoxComponent(class Actor* _owner, int _order = 100);
	~BoxComponent();

	void UpdateWorldTransform() override;

	//ゲッター
	const AABB& GetWorldBox() const { return world_box; }

	//セッター
	void SetBox(const AABB& _box) { box = _box; }
	void SetIsRotate(bool _is_rotate) { is_rotate = _is_rotate; }

private:
	AABB box;
	AABB world_box;

	bool is_rotate;//回転するか
};