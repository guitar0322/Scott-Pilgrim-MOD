#pragma once
#include "Component.h"

class Item :
    public Component
{
private:
	ZOrder* _zorder;

	float _itemSpeed;						//�������� �ӵ�
	float _gravity;							//�߷�
	float _angle;							//����
	float _friction;						//������

	float _speedX;
	float _speedY;
	float _itemZ;							// player�� z���� ��������

	bool _throwDir;							//�������� ���� ����
	bool _isGround;							//���� ���� �ߴ°�?
public:
	Animator* animator;
	GameObject* enemy;

	bool itemAttack;						//���������� ���� �ߴ°�?
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
	void ItemAttack();
   
	void Throw(bool dir);					//�������� ���� ���� �Լ�
	void ChangeClip(string clipName, bool isInitFrame);

	float GetItemZ() const { return _itemZ; }		//player.cpp�� (putItem�Լ����� ���)
	void SetItemZ(float itemZ) { _itemZ = itemZ; }	//player�� z���� ��� ����
	bool GetItemAttack() const { return itemAttack; }
	Transform* GetEnemyTransform() const { return enemy->transform; }
};