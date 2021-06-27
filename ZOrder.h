#pragma once
#include "Component.h"

class ZOrder :
    public Component
{
private:
    float _z;//zorder������ ������ǥ
    float _x;
    RECT _rc;
public:
    virtual void Init();
    virtual void Render();
    virtual void OnEnable();
    virtual void OnDisable();
    void MoveZ(float z);//������ǥ�� �̵�
    void SetZ(float z) { _z = z; }//������ǥ�� ����
    float GetZ() { return _z; }//������ǥ�� ��ȯ
};

