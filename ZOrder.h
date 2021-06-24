#pragma once
#include "GameObject.h"
class ZOrder :
    public Component
{
private:
    float _y;//zorder������ ������ǥ
    RECT _rc;
public:
    virtual void Init();
    virtual void Render();
    virtual void OnEnable();
    virtual void OnDisable();
    void MoveY(float y) { _y += y; } //������ǥ�� �̵�
    void SetY(float y) { _y = y; }//������ǥ�� ����
    float GetY() { return _y; }//������ǥ�� ��ȯ
};

