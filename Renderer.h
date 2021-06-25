#pragma once
#include "Component.h"
#include "image.h"
class Renderer :
    public Component
{
private:
    BLENDFUNCTION blendFunc;
    int _alpha;
    int _width;
    int _height;
    bool _isAlpha;
    RECT rc;
    COLORREF _transColor;
public:
    Renderer();
    ~Renderer();
    HDC memDC, alphaMemDC;
    HBITMAP oBit, hBit;
    virtual void Init(const char* filename, int width, int height);
    virtual void Init();
    virtual void Render();
    virtual void Update();
    virtual void Release();
    virtual void OnEnable();
    virtual void OnDisable();
    void SetAlphaMode(bool isAlpha) { _isAlpha = isAlpha; }//���ĺ��� ���θ� ����
    void SetAlphaMode(bool isAlpha, int alpha);//���ĸ��� ���İ��� ���ÿ� ����
    void SetAlpha(int alpha) { this->_alpha = alpha; blendFunc.SourceConstantAlpha = alpha;}//���İ� ����
    void Resize(int objWidth, int objHeight);//������ DC���� ũ�⸦ ������
    void SetTransColor(COLORREF transColor) { _transColor = transColor; }
    RECT GetRc() { return rc; }
};

