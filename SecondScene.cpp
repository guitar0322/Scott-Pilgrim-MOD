#include "stdafx.h"
#include "SecondScene.h"
#include "Outline.h"
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

    for (int i = 0; i < TYPE_NUM; i++)
    {
		_sceneInfoLoader.SetLinkObjectVAddress(&_objectV[i]);
		_sceneInfoLoader.LoadObjectInfo(i);
    }
    for (int i = 0; i < TYPE_NUM; i++)
    {
		for (int j = 0; j < _objectV[i].size(); j++)
		{
			OBJECTNAME objectName;
			objectName.name = _objectV[i][j]->name;
			objectName.rc = RectMake(NAME_STARTX, NAME_STARTY + NAME_HEIGHT * j, NAME_WIDTH, NAME_HEIGHT);
			_objectNameV[i].push_back(objectName);
		}
    }
    mouseDeltaX = 0;
    mouseInfo.clickedLeft = false;
    mouseInfo.clickedRight = false;
    mouseInfo.deltaX = 0;
    mouseInfo.deltaY = 0;
    mouseInfo.preX = 0;
    mouseInfo.preY = 0;
    
    selectIdxType = -1; 
    selectIdxObject = -1;
    selectIdxName = 0;
    selectIdxNameType = 0;
    clickScreen = false;

    InitTypeName();
    InitObjectMenu();
    InitButton();
    OutlineInit();
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
    ZORDER->Update();
    if (!KEYMANAGER->isToggleKey(VK_SHIFT))
        _outline.SetActive(false);
    else
        _outline.SetActive(true);
    _outline.Update();
    sprintf_s(debug[0], "%d", selectIdxName);
    for (int i = 0; i < TYPE_NUM; i++)
    {
		for (int j = 0; j < _objectV[i].size(); j++)
		{
			_objectV[i][j]->Update();
		}
    }
    selectNameRect = RectMake(NAME_STARTX, NAME_STARTY + NAME_HEIGHT * selectIdxName, NAME_WIDTH, NAME_HEIGHT);
    //���콺�� Ŭ�������� ����
    //1.���带 Ŭ������ ���
    //2.��ġ�� ������Ʈ�� Ŭ������ ���
    //3.������Ʈ �޴��� Ŭ������ ���
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
        mouseInfo.clickedLeft = true;
        clickScreen = false;
        selectIdxObject = -1;
        selectIdxObjectType = -1;
        selectIdxType = -1;
        mouseInfo.preX = _ptMouse.x;
        mouseInfo.preY = _ptMouse.y;
		if (_ptMouse.x <= 650 && _ptMouse.y <= 400)
		{
            clickScreen = true;
            POINT worldPtMouse = ScreenToWorld(_ptMouse.x, _ptMouse.y);

            //��ġ�� ������Ʈ�� Ŭ������ ��
            for (int i = 0; i < TYPE_NUM; i++)
            {
				for (int j = 0; j < _objectV[i].size(); j++) {
					if (PtInRect(&(_objectV[i][j]->GetComponent<Renderer>()->GetRc()), worldPtMouse)) {
                        if (KEYMANAGER->isStayKeyDown(VK_MENU))
                        {
                            RemoveObject(i, j);
                        }
                        else
                        {
							clickScreen = false;
							selectIdxObjectType = i;
							selectIdxNameType = i;
							selectIdxObject = j;
							selectIdxName = j;
							SetOutline(_objectV[i][j]);
							break;
                        }
					}
				}
            }
		}
        else
        {
            //������Ʈ �޴��� Ŭ��������
            for (int i = 0; i < TYPE_NUM; i++) 
            {
                if (PtInRect(&objectMenu[i].rc, _ptMouse))
                {
                    selectIdxType = i;
                    selectObject.deltaX = _ptMouse.x - (objectMenu[i].left * 2 + objectMenu[i].width) / 2;
                    selectObject.deltaY = _ptMouse.y - (objectMenu[i].top * 2 + objectMenu[i].height) / 2;
                    selectObject.width = objectMenu[i].img->getWidth() * _worldEditorRatio;
                    selectObject.height = objectMenu[i].img->getHeight() * _worldEditorRatio;
                    selectObject.img = objectMenu[i].img;
                    break;
                }
            }
            //������Ʈ �̸��� Ŭ������ ��
			for (int j = 0; j < _objectNameV[selectIdxNameType].size(); j++)
			{
				if (PtInRect(&_objectNameV[selectIdxNameType][j].rc, _ptMouse))
				{
					ClickObjectName(j);
					SetOutline(_objectV[selectIdxNameType][j]);
					break;
				}
			}

            //�̸� Ÿ�� �׺���̼� ��ư�� ������ ��
            if (PtInRect(&beforeButton.rc, _ptMouse) && selectIdxNameType != 0)
            {
                selectIdxNameType--;
                if (_objectV[selectIdxNameType].empty() == false)
                {
                    SetOutline(_objectV[selectIdxNameType][0]);
                    ClickObjectName(0);
                }
                else
                    selectIdxName = -1;
            }
            if (PtInRect(&nextButton.rc, _ptMouse) && selectIdxNameType != TYPE_NUM - 1)
            {
                selectIdxNameType++;
                if (_objectV[selectIdxNameType].empty() == false)
                {
					SetOutline(_objectV[selectIdxNameType][0]);
					ClickObjectName(0);
                }
                else
                    selectIdxName = -1;

            }
        }
	}

    //���콺�� Ŭ����ä�� �����϶� ����
    if (mouseInfo.clickedLeft == true) 
    {
        mouseInfo.deltaX = _ptMouse.x - mouseInfo.preX;
        mouseInfo.deltaY = _ptMouse.y - mouseInfo.preY;
        if (clickScreen == true)
        {
            MoveScreen();
        }
        else if (selectIdxObject != -1)
        {
            _objectV[selectIdxObjectType][selectIdxObject]->transform->MoveX(mouseInfo.deltaX / _worldEditorRatio);
            _objectV[selectIdxObjectType][selectIdxObject]->GetComponent<ZOrder>()->MoveZ(mouseInfo.deltaY / _worldEditorRatio);
            _outline.transform->MoveX(mouseInfo.deltaX / _worldEditorRatio);
            _outline.GetComponent<ZOrder>()->MoveZ(mouseInfo.deltaY / _worldEditorRatio);
        }
        else if(selectIdxType != -1)
        {
            selectObject.x = _ptMouse.x - selectObject.deltaX;
            selectObject.y = _ptMouse.y - selectObject.deltaY;
            selectObject.rc = RectMakeCenter(selectObject.x, selectObject.y, selectObject.width, selectObject.height);
        }
        mouseInfo.preX = _ptMouse.x;
        mouseInfo.preY = _ptMouse.y;
    }

    //���콺�� ������ ����
    //Ŭ������ �� ������ Ŭ���ߴ��Ŀ� ���� �ٸ��� ����
    if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
    {
        mouseInfo.clickedLeft = false;
        //������Ʈ �޴��� Ŭ������ ��� ���콺�� ���� �� ��ġ�� ������Ʈ ���Ϳ� ������Ʈ �߰�
        if (selectIdxType != -1 && _ptMouse.x <= 650 && _ptMouse.y <= 400) 
        {
            GameObject* newObject;
            OBJECTNAME newObjectName;
			POINT worldPoint = ScreenToWorld(selectObject.x, selectObject.y);
            switch (selectIdxType) {
            case 0:
                newObject = _sceneInfoLoader.MakeSnow1(worldPoint.x, worldPoint.y);
                break;
            case 1:
                newObject = _sceneInfoLoader.MakeSnow2(worldPoint.x, worldPoint.y);
                break;
            }
            _objectV[selectIdxType].push_back(newObject);
            newObjectName.name = newObject->name;
            newObjectName.rc = RectMake(NAME_STARTX, NAME_STARTY + 20 * _objectNameV[selectIdxType].size(), NAME_WIDTH, NAME_HEIGHT);
            _objectNameV[selectIdxType].push_back(newObjectName);
            selectIdxNameType = selectIdxType;
            selectIdxName = _objectV[selectIdxType].size() - 1;
            SetOutline(newObject);
        }
		selectIdxType = -1;
    }

    //��ġ�� ������Ʈ �������� �ؽ�Ʈ �����ͷ� ����
    if (KEYMANAGER->isOnceKeyDown('S'))
    {
		vector<string> objectStringInfo;
        for (int i = 0; i < TYPE_NUM; i++)
        {
			for (int j = 0; j < _objectV[i].size(); j++)
			{
				objectStringInfo.push_back(to_string(_objectV[i][j]->transform->GetX()));
				objectStringInfo.push_back(to_string(_objectV[i][j]->transform->GetY()));
				objectStringInfo.push_back(to_string(i));
			}
        }
		TXTDATAMANAGER->txtSave("scene_info.txt", objectStringInfo);
    }
}

void SecondScene::Render()
{
    PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
    BGMANAGER->Render();
    ZORDER->Render();
    MainCam->Render(backDC);

    //������Ʈ �޴� ������
    for (int i = 0; i < TYPE_NUM; i++)
    {
		GdiTransparentBlt(backDC, 
            objectMenu[i].left, objectMenu[i].top, 
            objectMenu[i].width, objectMenu[i].height, 
            objectMenu[i].img->getMemDC(),
            0, 0, 
            objectMenu[i].img->getWidth(),
            objectMenu[i].img->getHeight(),
            RGB(255, 0, 255));
    }
    
    DrawSelectRect();
    SetBkMode(backDC, TRANSPARENT);
    TextOut
    (
        backDC, NAME_STARTX, NAME_STARTY - 20, 
        typeNameArr[selectIdxNameType].c_str(), 
        strlen(typeNameArr[selectIdxNameType].c_str())
    );
    for (int i = 0; i < _objectNameV[selectIdxNameType].size(); i++)
    {
        TextOut
        (
            backDC, NAME_STARTX, NAME_STARTY + NAME_HEIGHT * i,
            _objectNameV[selectIdxNameType][i].name.c_str(), 
            strlen(_objectNameV[selectIdxNameType][i].name.c_str())
        );
    }
    if (selectIdxType != -1)
    {
        GdiTransparentBlt(backDC,
            selectObject.rc.left,
            selectObject.rc.top,
            selectObject.width,
            selectObject.height,
            selectObject.img->getMemDC(),
            0, 0,
            selectObject.img->getWidth(),
            selectObject.img->getHeight(),
            RGB(255, 0, 255));
    }

    {
        if(selectIdxNameType != 0)
            beforeButton.img->render(backDC, beforeButton.rc.left, beforeButton.rc.top);
        if(selectIdxNameType != TYPE_NUM - 1)
            nextButton.img->render(backDC, nextButton.rc.left, nextButton.rc.top);
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
    //���� ������ ��Ʈ�� ������ ��ũ������ ��Ʈ�� ��ȯ.
    //left,top�� ���ؼ� width , height�� RectMake�ϱ�
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
    //������ǥ�� �����ͻ� ȭ�� ��ǥ�� ��ȯ
    long resultX = (x - (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2)) * _worldEditorRatio;
    long resultY = y * _worldEditorRatio;

    return { resultX, resultY };
}

POINT SecondScene::ScreenToWorld(long x, long y)
{
    //�����ͻ��� ��ǥ�� ������ǥ�� ��ȯ
    //�巡�׵Ǵ� ������Ʈ�� ���� ������ǥ ���� = camera.x - (WINSIZEX/2 - ptMouse.x / ratio)
    long resultX = MainCam->transform->GetX() - (WINSIZEX / 2 - x / _worldEditorRatio);
    long resultY = y / _worldEditorRatio;
    return{ resultX ,resultY };
}

void SecondScene::InitObjectMenu()
{
    for (int i = 0; i < TYPE_NUM; i++)
    {
        objectMenu[i].img = new image();
        objectMenu[i].left = OBJECT_MENU_STARTX + OBJECT_MENU_TERM * i;
        objectMenu[i].top = OBJECT_MENU_STARTY;
        objectMenu[i].type = i;
    }

    objectMenu[0].img->init("map/snow1.bmp", 108, 44, true, RGB(255, 0, 255));
    objectMenu[0].width = 80;
    objectMenu[0].height = 44;
    objectMenu[0].rc = RectMake(objectMenu[0].left, objectMenu[0].top, objectMenu[0].width, objectMenu[0].height);

    objectMenu[1].img->init("map/snow2.bmp", 164, 62, true, RGB(255, 0, 255));
    objectMenu[1].width = 80;
    objectMenu[1].height = 50;
    objectMenu[1].rc = RectMake(objectMenu[1].left, objectMenu[1].top, objectMenu[1].width, objectMenu[1].height);
}

void SecondScene::InitTypeName()
{
    typeNameArr[0] = "Snow1";
    typeNameArr[1] = "Snow2";
}

void SecondScene::InitButton()
{
    nextButton.img = new image();
    nextButton.img->init("ui/next.bmp", 25, 25, true, RGB(255, 0, 255));
    nextButton.rc = RectMakeCenter(NAME_STARTX + NAME_WIDTH + 13, NAME_STARTY - 10, 26, 26);

    beforeButton.img = new image();
    beforeButton.img->init("ui/before.bmp", 25, 25, true, RGB(255, 0, 255));
    beforeButton.rc = RectMakeCenter(NAME_STARTX - 13, NAME_STARTY - 10, 26, 26);
}

void SecondScene::MoveScreen()
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

void SecondScene::DrawSelectRect()
{
    if (selectIdxName == -1) return;
    HBRUSH hBit, oBit;
    hBit = CreateSolidBrush(RGB(100, 100, 255));
    oBit = (HBRUSH)SelectObject(backDC, hBit);
    Rectangle(backDC, selectNameRect);
    SelectObject(backDC, oBit);
    DeleteObject(hBit);
}

void SecondScene::ClickObjectName(int idx)
{
    selectIdxName = idx;
    MainCam->transform->SetX(_objectV[selectIdxNameType][selectIdxName]->transform->GetX());
    if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
        MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
}

void SecondScene::OutlineInit()
{
    _outline.Init();
    _outline.AddComponent(new Renderer());
    _outline.GetComponent<Renderer>()->Init();
    _outline.AddComponent(new Outline());
    _outline.GetComponent<Outline>()->Init();
    _outline.AddComponent(new ZOrder());
    _outline.GetComponent<ZOrder>()->Init();

    if (_objectV[0].size() != 0)
    {
        SetOutline(_objectV[0][0]);
    }
}

void SecondScene::SetOutline(GameObject* targetObject)
{
    _outline.transform->SetPosition(targetObject->transform->GetX(), targetObject->transform->GetY());
    _outline.GetComponent<Outline>()->SetTargetObject(targetObject);
    _outline.GetComponent<ZOrder>()->SetZ(targetObject->GetComponent<ZOrder>()->GetZ() - 1);
}

void SecondScene::RemoveObject(int objectType, int objectIdx)
{
    _objectV[objectType][objectIdx]->SetActive(false);
    SAFE_DELETE(_objectV[objectType][objectIdx]);
    _objectV[objectType].erase(_objectV[objectType].begin() + objectIdx);
    _objectNameV[objectType].erase(_objectNameV[objectType].begin() + objectIdx);
    for (int i = objectIdx; i < _objectNameV[objectType].size(); i++)
    {
        _objectNameV[objectType][i].rc = RectMake(NAME_STARTX, NAME_STARTY + NAME_HEIGHT * i, NAME_WIDTH, NAME_HEIGHT);
    }
    if (_objectV[objectType].empty() == true)
    {
        if (objectType != 0)
            selectIdxNameType = objectType - 1;
        else
            selectIdxNameType = TYPE_NUM - 1;
		selectIdxName = 0;
    }
    else
    {
        if(objectIdx != 0)
            selectIdxName = objectIdx - 1;
        else
        {
            selectIdxName = _objectV[objectType].size() - 1;
        }
    }
    ClickObjectName(selectIdxName);
    SetOutline(_objectV[selectIdxNameType][selectIdxName]);
}

