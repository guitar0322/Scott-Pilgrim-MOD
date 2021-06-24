#pragma once
#include "GameObject.h"
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
    virtual void Init(int startX, int startY, int endX, int endY);
    virtual void Update();
    virtual void Render();

    void SetStartPoint(int startX, int startY);
    void SetEndPoint(int endX, int endY);
    bool IsCross(int startX, int startY, int endX, int endY);
    int CalcUpDown(float x, float y);
    bool IsInLine(float x, float y);
};

