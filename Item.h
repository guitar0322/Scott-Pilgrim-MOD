#pragma once
#include "Component.h"

class Item :
    public Component
{
private:
	Animator* _animator;
	ZOrder* _zorder;

	int _frictionCount;						//������ī��Ʈ
	int _throwTime;							//throw�� �ð�

	float _itemSpeed;						//�������� �ӵ�
	float _gravity;							//�߷�
	float _angle;							//����
	float _friction;						//������

	float _moveX;
	float _moveY;

	bool _dir;								//���Ⱚ false�� right   /// true�� left

public:
	
	float itemZ;							//item�� z��
	
	bool throwDir;							//�������� ���� �������ֱ� ���� bool��
	
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
   
	void Throw(bool dir);					//�������� ���� ���� �Լ�
};

