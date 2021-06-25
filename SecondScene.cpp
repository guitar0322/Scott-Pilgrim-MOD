#include "stdafx.h"
#include "SecondScene.h"

SecondScene::SecondScene()
{
}

SecondScene::~SecondScene()
{
}

HRESULT SecondScene::Init()
{
    Scene::Init();
    HDC hdc = GetDC(_hWnd);
    HBITMAP hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);
    backDC = CreateCompatibleDC(hdc);
    SelectObject(backDC, hBit);
    DeleteObject(hBit);
    ReleaseDC(_hWnd, hdc);

    mouseDeltaX = 0;
    mouseInfo.clickedLeft = false;
    mouseInfo.clickedRight = false;
    mouseInfo.deltaX = 0;
    mouseInfo.deltaY = 0;
    mouseInfo.preX = 0;
    mouseInfo.preY = 0;
    
    selectIdx = -1;

    for (int i = 0; i < OBJECT_NUM; i++) 
    {
		object[i].image.transform->SetPosition(714, 84);
        object[i].x = 714;
        object[i].y = 84;
        object[i].type = i;
    }
    object[0].image.renderer->Init("map/snow1.bmp", 108, 44);
    object[0].width = 108;
    object[0].height = 44;
    object[0].rc = RectMakeCenter(object[0].x, object[0].y, object[0].width, object[0].height);
    BackgroundInit();
    CameraInit();
    return S_OK;
}

void SecondScene::Release()
{
}

void SecondScene::Update()
{
    BGMANAGER->Update();
    sprintf_s(debug[0], "%d", selectIdx);
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x <= 650 && _ptMouse.y <= 400)
		{
			mouseInfo.clickedLeft = true;
			mouseInfo.preX = _ptMouse.x;
			mouseInfo.preY = _ptMouse.y;
		}
        else {
            for (int i = 0; i < OBJECT_NUM; i++) {
                if (PtInRect(&object[i].rc, _ptMouse)) {
                    selectIdx = i;
                    selectObject.deltaX = _ptMouse.x - object[i].x;
                    selectObject.deltaY = _ptMouse.y - object[i].y;
                    selectObject.image = &(object[i].image);
                }
            }
        }
	}
    if (KEYMANAGER->isStayKeyDown(VK_LBUTTON) && selectIdx != -1) {

    }
    if (mouseInfo.clickedLeft == true) 
    {
        mouseInfo.deltaX = _ptMouse.x - mouseInfo.preX;
        if (KEYMANAGER->isStayKeyDown(VK_CONTROL)) 
        {
            MainCam->transform->MoveX(-(mouseInfo.deltaX * 3));
        }
        else
        {
			MainCam->transform->MoveX(-mouseInfo.deltaX);
        }
        mouseInfo.preX = _ptMouse.x;
    }
    if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON)) {
        mouseInfo.clickedLeft = false;
        if (selectIdx != -1)
            selectIdx = -1;
    }
}

void SecondScene::Render()
{
    PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
    BGMANAGER->Render();
    MainCam->Render(backDC);
    for (int i = 0; i < OBJECT_NUM; i++)
    {
		GdiTransparentBlt(backDC, 
            object[i].x - object[i].width / 2, object[i].y - object[i].height / 2, 
            object[i].width, object[i].height, 
            object[i].image.renderer->memDC,
            0, 0, 
            object[i].width, object[i].height,
            RGB(255, 0, 255));
    }
    if (selectIdx != -1)
    {
        GdiTransparentBlt(backDC,
            _ptMouse.x - selectObject.deltaX - selectObject.image->renderer->GetWidth() / 2,
            _ptMouse.y - selectObject.deltaY - selectObject.image->renderer->GetHeight() / 2,
            selectObject.image->renderer->GetWidth(),
            selectObject.image->renderer->GetHeight(),
            selectObject.image->renderer->memDC,
            0, 0,
            selectObject.image->renderer->GetWidth(),
            selectObject.image->renderer->GetHeight(),
            RGB(255, 0, 255));
    }
    TextOut(backDC, 20, 20, debug[0], strlen(debug[0]));
    BitBlt(_hdc, 0, 0, WINSIZEX, WINSIZEY, backDC, 0, 0, SRCCOPY);
}

void SecondScene::BackgroundInit()
{
    for (int i = 0; i < BG_NUM; i++) {
        char fileName[64];
        sprintf_s(fileName, "map/background%d.bmp", i + 1);
        background[i] = new ImageObject();
        background[i]->renderer->Init(fileName, 922, 680);
        background[i]->transform->SetPosition(922 * i + 922 / 2, 680 / 2);
        background[i]->name = "background";
        BGMANAGER->AddBackground(background[i]);
    }
    BGMANAGER->SetMargin(30);
    BGMANAGER->SetBackgroundWidth(922);
    BGMANAGER->SetPlayer(MainCam->transform);
}

void SecondScene::CameraInit()
{
    _mapWidth = 21206;
    _mapHeight = 680;
    MainCam->SetMapSize(_mapWidth, _mapHeight);
    MainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    MainCam->SetRenderHeight(568);
    MainCam->SetMapSize(21206, 680);
    MainCam->SetScreenSize(650, 400);
    SetBackBufferSize(_mapWidth, _mapHeight);
}

