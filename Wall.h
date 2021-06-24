#pragma once
#include "GameObject.h"
class Wall :
    public Component
{
private:
    float _startX;      //벽의 시작점
    float _startY;
    float _endX;        //벽의 끝점
    float _endY;
    float _gradient;    //벽의 기울기
    float _interceptY;  //벽의 y절편
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

