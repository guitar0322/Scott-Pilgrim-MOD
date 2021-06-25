#pragma once
#include "Scene.h"
#define BG_NUM 23
#define SNOW1 0
#define OBJECT_NUM 1
class SecondScene :
    public Scene
{
private:
    HDC backDC;
    typedef struct tagMouseInfo {
        float deltaX;
        float deltaY;
        bool clickedLeft;
        bool clickedRight;
        float preX;
        float preY;
    }MOUSEINFO;
    typedef struct tagObjectInfo {
        RECT rc;
        int x;
        int y;
        int width;
        int height;
        int type;
        ImageObject image;
    }OBJECTINFO;
    typedef struct tagSelectObject {
        int deltaX;
        int deltaY;
        int width;
        int height;
        ImageObject* image;
    }SELECTOBJECT;

private:
    float _worldEditorRatio;
    float _editorWidth;
    float _editorHeight;
    int _objectUIPositionY;
    int _objectUIPositionStartX;
    int _objectUITermX;
    vector<OBJECTINFO> _placedObjectV;
    vector<OBJECTINFO>::iterator _placedObjectIter;
public:
    ImageObject* background[BG_NUM];
    OBJECTINFO object[OBJECT_NUM];
    MOUSEINFO mouseInfo;
    SELECTOBJECT selectObject;
    float mouseDeltaX;
    int selectIdx;
public:
    SecondScene();
    ~SecondScene();
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void BackgroundInit();
    void CameraInit();
};

