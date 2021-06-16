#pragma once
#include "GameObject.h"
class BoxCollider :
    public Component
{
public:
    BoxCollider();
    ~BoxCollider();
    vector<int> vCol;
    vector<int> prevCol;
    bool isTrigger;
    int width;
    int height;

    virtual void Update();
    virtual void Render();
    bool CheckCollision(float tempX, float tempY);
    bool CheckCollision(float tempX, float tempY, int colIdx);
    void SetWidth(int width) { this->width = width; }
    void SetHeight(int height) { this->height = height; }
    void SetSize(int width, int height) { this->width = width; this->height = height; }
    RECT rc;
    RECT intersectRc;
};

