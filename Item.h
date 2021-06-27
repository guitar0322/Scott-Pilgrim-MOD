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
	float _itemZ;							//item�� z��


public:
    int enterNum;
    int exitNum;
	
	bool _leftThrowItem;					//�������� �������� ��������
	bool _rightThrowItem;					//���������� �������� ��������

	bool _ItemRangeOutLeftCameraX;			//�������� ī�޶��� left X��ǥ�� �������
	bool _ItemRangeOutRightCameraX;			//�������� ī�޶��� right X ��ǥ�� �������
    
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
    
	virtual void OnCollision(GameObject* gameObject);					//�����浹 �߻��Ҷ� ȣ��
    virtual void OnTriggerEnter(GameObject* gameObject);				//������Ʈ�� �ڽ��ݶ��̴��� �������� ���۵ɶ� ȣ��
    virtual void OnTriggerExit(GameObject* gameObject);					//������Ʈ�� �ڽ��ݶ��̴��� �������� ������ ȣ��

	virtual void ItemLeftMove();										//�������� �̵��ϴ� ������ move��
	virtual void ItemRightMove();										//���������� �̵��ϴ� ������ move��

	virtual void ItemRangeOutLeftMove();								//�������� ī�޶� ���� �ʰ��� "left�� �̵�
	virtual void ItemRangeOutRightMove();								//�������� ī�޶� ���� �ʰ��� "rgiht"�� �̵�

};

