#pragma once
#include "Component.h"

class Player;
class Item :
    public Component
{
private:
	Animator* _animator;
	//ZOrder*  _zOrder;
	float _itemSpeed;						//�������� �ӵ�
	float _gravity;							//�߷�


public:
    int enterNum;
    int exitNum;
	
	Player* player;
	
	float _itemZ;							//item�� z��
	
	bool _throwDir;
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

	void Throw(bool dir);
};

