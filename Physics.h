#pragma once
#include "Collision.h"
#include <functional>
#include <vector>

//�����N���X
class Physics
{
public:
	Physics(class Game* _game);

	//�Փˏ��
	struct Information
	{
		Vector3 point;				//���W
		Vector3 normal;				//�@��
		class BoxComponent* box;	//�Փ˃R���|�[�l���g
		class Actor* actor;			//���̏��L��
	};

	//�����̔���
	bool LineIntersect(const Line& _line, Information& _information);

	//AABB���m
	void Pairwaise(std::function<void(class Actor*, class Actor*)> _f);
	void SweepAndPrune(std::function<void(class Actor*, class Actor*)> _f);

	void AddBox(class BoxComponent* _box);		//Box��ǉ�
	void RemoveBox(class BoxComponent* _box);	//Box���폜

private:
	Game* game;
	std::vector<class BoxComponent*> boxes;//Box
};