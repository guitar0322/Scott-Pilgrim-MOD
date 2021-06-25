#pragma once
#include "Component.h"
class Wall :
    public Component
{
private:
    float _startX;      //���� ������
    float _startY;
    float _endX;        //���� ����
    float _endY;
    float _gradient;    //���� ����
    float _interceptY;  //���� y����
public:
    virtual void Init(float startX, float startY, float endX, float endY);
    virtual void Update();
    virtual void Render();

    void SetStartPoint(float startX, float startY);
    void SetEndPoint(float endX, float endY);
    bool IsCross(float startX, float startY, float endX, float endY);
    int CalcUpDown(float x, float y);
    bool IsInLine(float x, float y);
};

