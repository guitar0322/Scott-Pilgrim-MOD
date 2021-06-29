#pragma once
#include "Component.h"

class Item :
    public Component
{
private:
	Animator* _animator;
	ZOrder* _zorder;

	float _itemSpeed;						//�������� �ӵ�
	float _gravity;							//�߷�
	float _angle;							//����

	float _friction;						//������
	float _dashSpeed;						//�̵��� ���� �� �ӵ�

	float _speedX;
	float _speedY;

	bool _dir;								//���Ⱚ false�� right   /// true�� left
	bool _onGround;							//���� ���� �߳�?

public:
	
	float itemZ;							//item�� z��
	
	bool throwDir;							//�������� ���� �������ֱ� ���� bool��
	
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
   
	void Throw(bool dir);					//�������� ���� ���� �Լ�
};

