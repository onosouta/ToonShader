#pragma once
#include "Collision.h"
#include <functional>
#include <vector>

//物理クラス
class Physics
{
public:
	Physics(class Game* _game);

	//衝突情報
	struct Information
	{
		Vector3 point;				//座標
		Vector3 normal;				//法線
		class BoxComponent* box;	//衝突コンポーネント
		class Actor* actor;			//↑の所有者
	};

	//線分の判定
	bool LineIntersect(const Line& _line, Information& _information);

	//AABB同士
	void Pairwaise(std::function<void(class Actor*, class Actor*)> _f);
	void SweepAndPrune(std::function<void(class Actor*, class Actor*)> _f);

	void AddBox(class BoxComponent* _box);		//Boxを追加
	void RemoveBox(class BoxComponent* _box);	//Boxを削除

private:
	Game* game;
	std::vector<class BoxComponent*> boxes;//Box
};