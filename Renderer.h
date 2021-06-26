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
    float _scaleX;
    float _scaleY;
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
    void ResizeAlphaMemDC(float newWidth, float newHeight);
    void SetTransColor(COLORREF transColor) { _transColor = transColor; }
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    RECT GetRc() { return rc; }


    void SetScale(float scaleX, float scaleY);

    float GetScaleX() const { return _scaleX; }
    void SetScaleX(float scaleX);

    float GetScaleY() const { return _scaleY; }
    void SetScaleY(float scaleY);
};

