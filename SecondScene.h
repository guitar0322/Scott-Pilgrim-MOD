#pragma once
#include "Scene.h"
#include "SceneInfoLoader.h"

#define BG_NUM 23
#define SNOW1 0
#define TYPE_NUM 2
#define NAME_STARTX 700
#define NAME_STARTY 50
#define NAME_WIDTH 150
#define NAME_HEIGHT 20

#define OBJECT_MENU_STARTX 100
#define OBJECT_MENU_STARTY 460
#define OBJECT_MENU_TERM 100
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
    typedef struct tagObjectMenu {
        RECT rc;
        int left;
        int top;
        int width;
        int height;
        int type;
        image* img;
    }OBJECTMENU;
    typedef struct tagSelectObject {
        RECT rc;
        int deltaX;
        int deltaY;
        int width;
        int height;
        int x;
        int y;
        image* img;
    }SELECTOBJECT;

    typedef struct tagObjectNameButton {
        RECT rc;
        string name;
    }OBJECTNAME;

    typedef struct tagButton {
        RECT rc;
        image* img;
    }BUTTON;
private:
    float _worldEditorRatio;
    float _editorWidth;
    float _editorHeight;
    SceneInfoLoader _sceneInfoLoader;
    vector<GameObject*> _objectV[TYPE_NUM];
    vector<OBJECTNAME> _objectNameV[TYPE_NUM];
    string typeNameArr[TYPE_NUM];
    GameObject _outline;
    BUTTON nextButton, beforeButton;
public:
    ImageObject* background[BG_NUM];
    OBJECTMENU objectMenu[TYPE_NUM];
    SELECTOBJECT selectObject;
    MOUSEINFO mouseInfo;
    float mouseDeltaX;
    int selectIdxType;
    int selectIdxObject;
    int selectIdxObjectType;
    int selectIdxName;
    int selectIdxNameType;
    bool clickScreen;
    RECT selectNameRect;
public:
    SecondScene();
    ~SecondScene();
    virtual HRESULT Init();
    virtual void Release();
    virtual void Update();
    virtual void Render();

    void BackgroundInit();
    void CameraInit();
    RECT WorldToScreen(RECT rc);
    RECT ScreenToWorld(RECT rc);
    POINT WorldToScreen(long x, long y);
    POINT ScreenToWorld(long x, long y);

    void InitObjectMenu();
    void InitTypeName();
    void InitButton();
    void MoveScreen();
    void DrawSelectRect();
    void ClickObjectName(int idx);
    void OutlineInit();
    void SetOutline(GameObject* targetObject);
    void RemoveObject(int objectType, int objectIdx);
};

