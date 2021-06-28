#pragma once
#include "Component.h"


class Item :
    public Component
{
private:
	Animator* _animator;
	ZOrder* _zorder;
;
	float _itemSpeed;						//�������� �ӵ�
	float _gravity;							//�߷�
	float _angle;							//����			

	float _moveX;
	float _moveY;


public:
    int enterNum;
    int exitNum;
	
	float itemZ;							//item�� z��
	
	bool throwDir;							//�������� ���� �������ֱ� ���� bool��
	
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
    
	virtual void OnCollision(GameObject* gameObject);					//�����浹 �߻��Ҷ� ȣ��
    virtual void OnTriggerEnter(GameObject* gameObject);				//������Ʈ�� �ڽ��ݶ��̴��� �������� ���۵ɶ� ȣ��
    virtual void OnTriggerExit(GameObject* gameObject);					//������Ʈ�� �ڽ��ݶ��̴��� �������� ������ ȣ��

	void Throw(bool dir);					//�������� ���� ���� �Լ�
};

