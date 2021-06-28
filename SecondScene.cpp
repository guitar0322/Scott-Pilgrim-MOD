#include "stdafx.h"
#include "SecondScene.h"
#include <string>

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
    
    selectIdxUI = -1; 
    selectIdxObject = -1;

    _objectUITermX = 100;
    _objectUIPositionStartX = 100;
    _objectUIPositionY = 460;
    for (int i = 0; i < OBJECT_NUM; i++) 
    {
		object[i].image.transform->SetPosition(_objectUIPositionStartX + _objectUITermX * i, _objectUIPositionY);
        object[i].x = _objectUIPositionStartX + _objectUITermX * i;
        object[i].y = _objectUIPositionY;
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
    sprintf_s(debug[0], "%d", selectIdxUI);
    for (int i = 0; i < _placedObjectV.size(); i++)
    {
        _placedObjectV[i].image.Update();
    }
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
        mouseInfo.clickedLeft = true;
        mouseInfo.preX = _ptMouse.x;
        mouseInfo.preY = _ptMouse.y;
		if (_ptMouse.x <= 650 && _ptMouse.y <= 400)
		{
            selectIdxObject = -1;
            POINT worldPtMouse = ScreenToWorld(_ptMouse.x, _ptMouse.y);
            for (int i = 0; i < _placedObjectV.size(); i++) {
                if (PtInRect(&_placedObjectV[i].image.renderer->GetRc(), worldPtMouse)) {
                    selectIdxObject = i;
                    break;
                }
            }
		}
        else
        {
            selectIdxObject = -1;
            for (int i = 0; i < OBJECT_NUM; i++) 
            {
                if (PtInRect(&object[i].rc, _ptMouse))
                {
                    selectIdxUI = i;
                    selectObject.deltaX = _ptMouse.x - object[i].x;
                    selectObject.deltaY = _ptMouse.y - object[i].y;
                    selectObject.width = object[i].width * _worldEditorRatio;
                    selectObject.height = object[i].height * _worldEditorRatio;
                    selectObject.image = &(object[i].image);
                }
            }
        }
	}
    if (mouseInfo.clickedLeft == true) 
    {
        mouseInfo.deltaX = _ptMouse.x - mouseInfo.preX;
        mouseInfo.deltaY = _ptMouse.y - mouseInfo.preY;
        if (selectIdxUI == -1 && selectIdxObject == -1)
        {
			if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
			{
				MainCam->transform->MoveX(-(mouseInfo.deltaX * 3));
			}
			else
			{
				MainCam->transform->MoveX(-mouseInfo.deltaX);
			}
            if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
                MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
        }
        else if (selectIdxObject != -1)
        {
            _placedObjectV[selectIdxObject].image.transform->Move(mouseInfo.deltaX / _worldEditorRatio, mouseInfo.deltaY / _worldEditorRatio);
            _placedObjectV[selectIdxObject].rc = WorldToScreen(_placedObjectV[selectIdxObject].image.renderer->GetRc());
        }
        else 
        {
            selectObject.x = _ptMouse.x - selectObject.deltaX;
            selectObject.y = _ptMouse.y - selectObject.deltaY;
            selectObject.rc = RectMakeCenter(selectObject.x, selectObject.y, selectObject.width, selectObject.height);
        }
        mouseInfo.preX = _ptMouse.x;
        mouseInfo.preY = _ptMouse.y;
    }
    if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
    {
        mouseInfo.clickedLeft = false;
        if (selectIdxUI != -1 && _ptMouse.x <= 650 && _ptMouse.y <= 400) 
        {
			OBJECTINFO newObject;
            newObject.image.renderer->Resize
            (
                object[selectIdxUI].image.renderer->GetWidth(),
                object[selectIdxUI].image.renderer->GetHeight()
            );
            BitBlt
            (
                newObject.image.renderer->memDC, 0, 0,
                object[selectIdxUI].image.renderer->GetWidth(),
                object[selectIdxUI].image.renderer->GetHeight(),
                object[selectIdxUI].image.renderer->memDC, 0, 0,
                SRCCOPY
            );
            newObject.image.transform->SetPosition
            (
                MainCam->transform->GetX() - (WINSIZEX / 2 - selectObject.x / _worldEditorRatio),
                MainCam->transform->GetY() - (WINSIZEY / 2 - selectObject.y / _worldEditorRatio)
            );
			newObject.type = selectIdxUI;
            newObject.x = selectObject.x;
            newObject.y = selectObject.y;
            newObject.width = selectObject.width;
            newObject.height = selectObject.height;
            newObject.rc = RectMakeCenter(newObject.x, newObject.y, newObject.width, newObject.height);
			_placedObjectV.push_back(newObject);
        }
		selectIdxUI = -1;
    }
    if (KEYMANAGER->isOnceKeyDown('S'))
    {
		vector<string> objectStringInfo;
        for (int i = 0; i < _placedObjectV.size(); i++)
        {
            objectStringInfo.push_back(to_string(_placedObjectV[i].image.transform->GetX()));
            objectStringInfo.push_back(to_string(_placedObjectV[i].image.transform->GetY()));
            objectStringInfo.push_back(to_string(_placedObjectV[i].type));
        }
		TXTDATAMANAGER->txtSave("scene_info.txt", objectStringInfo);
    }
}

void SecondScene::Render()
{
    PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
    BGMANAGER->Render();
    for (int i = 0; i < _placedObjectV.size(); i++)
    {
        _placedObjectV[i].image.Render();
    }
    MainCam->Render(backDC);
    //if (KEYMANAGER->isToggleKey(VK_TAB))
    //{
    //    for (int i = 0; i < _placedObjectV.size(); i++)
    //    {
    //        Rectangle(backDC, _placedObjectV[i].rc);
    //    }
    //}
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
    
    if (selectIdxUI != -1)
    {
        GdiTransparentBlt(backDC,
            selectObject.rc.left,
            selectObject.rc.top,
            selectObject.width,
            selectObject.height,
            selectObject.image->renderer->memDC,
            0, 0,
            selectObject.image->renderer->GetWidth(),
            selectObject.image->renderer->GetHeight(),
            RGB(255, 0, 255));
    }

    sprintf_s(debug[1], "%.1f, %.1f", _ptMouse.x / _worldEditorRatio, _ptMouse.y / _worldEditorRatio);
    if (!KEYMANAGER->isToggleKey(VK_TAB))
    {
		TextOut(backDC, 20, 20, debug[0], strlen(debug[0]));
		TextOut(backDC, _ptMouse.x, _ptMouse.y - 20, debug[1], strlen(debug[1]));
    }
    BitBlt(_hdc, 0, 0, WINSIZEX, WINSIZEY, backDC, 0, 0, SRCCOPY);
}

void SecondScene::BackgroundInit()
{
    for (int i = 0; i < BG_NUM; i++) 
    {
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
    _worldEditorRatio = 0.75f;
    _editorWidth = WINSIZEX * _worldEditorRatio;
    _editorHeight = WINSIZEY * _worldEditorRatio;
    MainCam->SetMapSize(_mapWidth, _mapHeight);
    MainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    MainCam->SetRenderHeight(568);
    MainCam->SetMapSize(21206, 680);
    MainCam->SetScreenSize(_editorWidth, _editorHeight);
    SetBackBufferSize(_mapWidth, _mapHeight);
}

RECT SecondScene::WorldToScreen(RECT rc)
{
    //실제 월드의 렉트를 에디터 스크린상의 렉트로 전환.
    //left,top을 구해서 width , height로 RectMake하기
    POINT leftTop = WorldToScreen(rc.left, rc.top);
    RECT result = RectMake(leftTop.x, leftTop.y, (rc.right - rc.left) * _worldEditorRatio, (rc.bottom - rc.top) * _worldEditorRatio);
    return result;
}

RECT SecondScene::ScreenToWorld(RECT rc)
{
    POINT leftTop = ScreenToWorld(rc.left, rc.top);
    RECT result = RectMake(leftTop.x, leftTop.y, rc.right - rc.left, rc.bottom - rc.top);
    return result;
}

POINT SecondScene::WorldToScreen(long x, long y)
{
    //월드좌표를 에디터상 화면 좌표로 변환
    long resultX = (x - (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2)) * _worldEditorRatio;
    long resultY = y * _worldEditorRatio;

    return { resultX, resultY };
}

POINT SecondScene::ScreenToWorld(long x, long y)
{
    //에디터상의 좌표를 월드좌표로 변환
    //드래그되는 오브젝트의 실제 월드좌표 공식 = camera.x - (WINSIZEX/2 - ptMouse.x / ratio)
    long resultX = MainCam->transform->GetX() - (WINSIZEX / 2 - x / _worldEditorRatio);
    long resultY = y / _worldEditorRatio;
    return{ resultX ,resultY };
}

