#pragma once
#include "GameObject.h"
class Item :
    public Component
{
public:
    int enterNum;
    int stayNum;
    int exitNum;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnCollision(GameObject* gameObject);//�����浹 �߻��Ҷ� ȣ��
    virtual void OnTriggerEnter(GameObject* gameObject);//������Ʈ�� �ڽ��ݶ��̴��� �������� ���۵ɶ� ȣ��
    virtual void OnTriggerStay(GameObject* gameObject);//������Ʈ�� �ڽ��ݶ��̴��� �������� ���ӵɶ� ȣ��
    virtual void OnTriggerExit(GameObject* gameObject);//������Ʈ�� �ڽ��ݶ��̴��� �������� ������ ȣ��
};

