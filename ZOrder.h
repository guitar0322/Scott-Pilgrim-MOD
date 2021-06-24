#pragma once
#include "GameObject.h"
class ZOrder :
    public Component
{
private:
    float _y;//zorder수행할 기준좌표
    RECT _rc;
public:
    virtual void Init();
    virtual void Render();
    virtual void OnEnable();
    virtual void OnDisable();
    void MoveY(float y) { _y += y; } //기준좌표를 이동
    void SetY(float y) { _y = y; }//기준좌표를 설정
    float GetY() { return _y; }//기준좌표를 반환
};

