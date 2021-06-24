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
    void SetAlphaMode(bool isAlpha) { _isAlpha = isAlpha; }//알파블렌드 여부를 설정
    void SetAlphaMode(bool isAlpha, int alpha);//알파모드와 알파값을 동시에 설정
    void SetAlpha(int alpha) { this->_alpha = alpha; blendFunc.SourceConstantAlpha = alpha;}//알파값 설정
    void Resize(int objWidth, int objHeight);//렌더러 DC영역 크기를 재조정
    void SetTransColor(COLORREF transColor) { _transColor = transColor; }
    RECT GetRc() { return rc; }
};

