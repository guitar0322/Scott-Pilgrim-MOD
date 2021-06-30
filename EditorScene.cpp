#include "stdafx.h"
#include "EditorScene.h"
#include "Outline.h"
#include <string>

EditorScene::EditorScene()
{
}

EditorScene::~EditorScene()
{
}

HRESULT EditorScene::Init()
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
    _mouseDeltaX = 0;
    _mouseInfo.clickedLeft = false;
    _mouseInfo.clickedRight = false;
    _mouseInfo.deltaX = 0;
    _mouseInfo.deltaY = 0;
    _mouseInfo.preX = 0;
    _mouseInfo.preY = 0;
    
    _selectIdxType = -1; 
    _selectIdxObject = -1;
    _selectIdxName = 0;
    _selectIdxNameType = 0;
    _clickScreen = false;

    InitTypeName();
    InitObjectMenu();
    InitButton();
    OutlineInit();
    BackgroundInit();
    CameraInit();
    return S_OK;
}

void EditorScene::Release()
{
}

void EditorScene::Update()
{
    BGMANAGER->Update();
    ZORDER->Update();
    if (!KEYMANAGER->isToggleKey(VK_SHIFT))
        _outline.SetActive(false);
    else
        _outline.SetActive(true);
    _outline.Update();
    sprintf_s(debug[0], "%d", _selectIdxName);
    for (int i = 0; i < TYPE_NUM; i++)
    {
		for (int j = 0; j < _objectV[i].size(); j++)
		{
			_objectV[i][j]->Update();
		}
    }
    _selectNameRect = RectMake(NAME_STARTX, NAME_STARTY + NAME_HEIGHT * _selectIdxName, NAME_WIDTH, NAME_HEIGHT);
    //마우스를 클릭했을때 동작
    //1.월드를 클릭했을 경우
    //2.배치된 오브젝트를 클릭했을 경우
    //3.오브젝트 메뉴를 클릭했을 경우
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
        _mouseInfo.clickedLeft = true;
        _clickScreen = false;
        _selectIdxObject = -1;
        _selectIdxObjectType = -1;
        _selectIdxType = -1;
        _mouseInfo.preX = _ptMouse.x;
        _mouseInfo.preY = _ptMouse.y;
		if (_ptMouse.x <= 650 && _ptMouse.y <= 400)
		{
            _clickScreen = true;
            POINT worldPtMouse = ScreenToWorld(_ptMouse.x, _ptMouse.y);

            //배치된 오브젝트를 클릭했을 때
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
							_clickScreen = false;
							_selectIdxObjectType = i;
							_selectIdxNameType = i;
							_selectIdxObject = j;
							_selectIdxName = j;
							SetOutline(_objectV[i][j]);
							break;
                        }
					}
				}
            }
		}
        else
        {
            //오브젝트 메뉴를 클릭했을때
            for (int i = 0; i < TYPE_NUM; i++) 
            {
                if (PtInRect(&_objectMenu[i].rc, _ptMouse))
                {
                    _selectIdxType = i;
                    _selectObject.deltaX = _ptMouse.x - (_objectMenu[i].left * 2 + _objectMenu[i].width) / 2;
                    _selectObject.deltaY = _ptMouse.y - (_objectMenu[i].top * 2 + _objectMenu[i].height) / 2;
                    _selectObject.width = _objectMenu[i].img->getWidth() * _worldEditorRatio;
                    _selectObject.height = _objectMenu[i].img->getHeight() * _worldEditorRatio;
                    _selectObject.img = _objectMenu[i].img;
                    break;
                }
            }
            //오브젝트 이름을 클릭했을 때
			for (int j = 0; j < _objectNameV[_selectIdxNameType].size(); j++)
			{
				if (PtInRect(&_objectNameV[_selectIdxNameType][j].rc, _ptMouse))
				{
					ClickObjectName(j);
					SetOutline(_objectV[_selectIdxNameType][j]);
					break;
				}
			}

            //이름 타입 네비게이션 버튼을 눌렀을 때
            if (PtInRect(&_beforeButton.rc, _ptMouse) && _selectIdxNameType != 0)
            {
                _selectIdxNameType--;
                if (_objectV[_selectIdxNameType].empty() == false)
                {
                    SetOutline(_objectV[_selectIdxNameType][0]);
                    ClickObjectName(0);
                }
                else
                    _selectIdxName = -1;
            }
            if (PtInRect(&_nextButton.rc, _ptMouse) && _selectIdxNameType != TYPE_NUM - 1)
            {
                _selectIdxNameType++;
                if (_objectV[_selectIdxNameType].empty() == false)
                {
					SetOutline(_objectV[_selectIdxNameType][0]);
					ClickObjectName(0);
                }
                else
                    _selectIdxName = -1;

            }
        }
	}

    //마우스가 클릭된채로 움직일때 동작
    if (_mouseInfo.clickedLeft == true) 
    {
        _mouseInfo.deltaX = _ptMouse.x - _mouseInfo.preX;
        _mouseInfo.deltaY = _ptMouse.y - _mouseInfo.preY;
        if (_clickScreen == true)
        {
            MoveScreen();
        }
        else if (_selectIdxObject != -1)
        {
            _objectV[_selectIdxObjectType][_selectIdxObject]->transform->MoveX(_mouseInfo.deltaX / _worldEditorRatio);
            _objectV[_selectIdxObjectType][_selectIdxObject]->GetComponent<ZOrder>()->MoveZ(_mouseInfo.deltaY / _worldEditorRatio);
            _outline.transform->MoveX(_mouseInfo.deltaX / _worldEditorRatio);
            _outline.GetComponent<ZOrder>()->MoveZ(_mouseInfo.deltaY / _worldEditorRatio);
        }
        else if(_selectIdxType != -1)
        {
            _selectObject.x = _ptMouse.x - _selectObject.deltaX;
            _selectObject.y = _ptMouse.y - _selectObject.deltaY;
            _selectObject.rc = RectMakeCenter(_selectObject.x, _selectObject.y, _selectObject.width, _selectObject.height);
        }
        _mouseInfo.preX = _ptMouse.x;
        _mouseInfo.preY = _ptMouse.y;
    }

    //마우스를 뗐을때 동작
    //클릭했을 때 무엇을 클릭했느냐에 따라 다르게 동작
    if (KEYMANAGER->isOnceKeyUp(VK_LBUTTON))
    {
        _mouseInfo.clickedLeft = false;
        //오브젝트 메뉴를 클릭했을 경우 마우스를 뗐을 때 배치된 오브젝트 벡터에 오브젝트 추가
        if (_selectIdxType != -1 && _ptMouse.x <= 650 && _ptMouse.y <= 400) 
        {
            GameObject* newObject;
            OBJECTNAME newObjectName;
			POINT worldPoint = ScreenToWorld(_selectObject.x, _selectObject.y);
            switch (_selectIdxType) {
            case 0:
                newObject = _sceneInfoLoader.MakeSnow1(worldPoint.x, worldPoint.y);
                break;
            case 1:
                newObject = _sceneInfoLoader.MakeSnow2(worldPoint.x, worldPoint.y);
                break;
            case 2:
                newObject = _sceneInfoLoader.MakeFencePillar(worldPoint.x, worldPoint.y);
                break;
            case 3:
                newObject = _sceneInfoLoader.MakeFencePillar2(worldPoint.x, worldPoint.y);
                break;
            case 4:
                newObject = _sceneInfoLoader.MakeLeeEditor(worldPoint.x, worldPoint.y);
                break;
            }
            _objectV[_selectIdxType].push_back(newObject);
            newObjectName.name = newObject->name;
            newObjectName.rc = RectMake(NAME_STARTX, NAME_STARTY + 20 * _objectNameV[_selectIdxType].size(), NAME_WIDTH, NAME_HEIGHT);
            _objectNameV[_selectIdxType].push_back(newObjectName);
            _selectIdxNameType = _selectIdxType;
            _selectIdxName = _objectV[_selectIdxType].size() - 1;
            SetOutline(newObject);
        }
		_selectIdxType = -1;
    }

    //배치된 오브젝트 정보들을 텍스트 데이터로 저장
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

void EditorScene::Render()
{
    PatBlt(backDC, 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
    BGMANAGER->Render();
    ZORDER->Render();
    MainCam->Render(backDC);

    //오브젝트 메뉴 렌더링
    for (int i = 0; i < TYPE_NUM; i++)
    {
		GdiTransparentBlt(backDC, 
            _objectMenu[i].left, _objectMenu[i].top, 
            _objectMenu[i].width, _objectMenu[i].height, 
            _objectMenu[i].img->getMemDC(),
            0, 0, 
            _objectMenu[i].img->getWidth(),
            _objectMenu[i].img->getHeight(),
            RGB(255, 0, 255));
    }
    
    DrawSelectRect();
    SetBkMode(backDC, TRANSPARENT);
    TextOut
    (
        backDC, NAME_STARTX, NAME_STARTY - 20, 
        _typeNameArr[_selectIdxNameType].c_str(), 
        strlen(_typeNameArr[_selectIdxNameType].c_str())
    );
    for (int i = 0; i < _objectNameV[_selectIdxNameType].size(); i++)
    {
        TextOut
        (
            backDC, NAME_STARTX, NAME_STARTY + NAME_HEIGHT * i,
            _objectNameV[_selectIdxNameType][i].name.c_str(), 
            strlen(_objectNameV[_selectIdxNameType][i].name.c_str())
        );
    }
    if (_selectIdxType != -1)
    {
        GdiTransparentBlt(backDC,
            _selectObject.rc.left,
            _selectObject.rc.top,
            _selectObject.width,
            _selectObject.height,
            _selectObject.img->getMemDC(),
            0, 0,
            _selectObject.img->getWidth(),
            _selectObject.img->getHeight(),
            RGB(255, 0, 255));
    }

    {
        if(_selectIdxNameType != 0)
            _beforeButton.img->render(backDC, _beforeButton.rc.left, _beforeButton.rc.top);
        if(_selectIdxNameType != TYPE_NUM - 1)
            _nextButton.img->render(backDC, _nextButton.rc.left, _nextButton.rc.top);
    }
    sprintf_s(debug[1], "%.1f, %.1f", _ptMouse.x / _worldEditorRatio, _ptMouse.y / _worldEditorRatio);
    if (!KEYMANAGER->isToggleKey(VK_TAB))
    {
		TextOut(backDC, 20, 20, debug[0], strlen(debug[0]));
		TextOut(backDC, _ptMouse.x, _ptMouse.y - 20, debug[1], strlen(debug[1]));
    }
    BitBlt(_hdc, 0, 0, WINSIZEX, WINSIZEY, backDC, 0, 0, SRCCOPY);
}

void EditorScene::BackgroundInit()
{
    for (int i = 0; i < BG_NUM; i++) 
    {
        char fileName[64];
        sprintf_s(fileName, "map/background%d.bmp", i + 1);
        _background[i] = new ImageObject();
        _background[i]->renderer->Init(fileName, 922, 680);
        _background[i]->transform->SetPosition(922 * i + 922 / 2, 680 / 2);
        _background[i]->name = "background";
        BGMANAGER->AddBackground(_background[i]);
    }
    BGMANAGER->SetMargin(30);
    BGMANAGER->SetBackgroundWidth(922);
    BGMANAGER->SetPlayer(MainCam->transform);
}

void EditorScene::CameraInit()
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

RECT EditorScene::WorldToScreen(RECT rc)
{
    //실제 월드의 렉트를 에디터 스크린상의 렉트로 전환.
    //left,top을 구해서 width , height로 RectMake하기
    POINT leftTop = WorldToScreen(rc.left, rc.top);
    RECT result = RectMake(leftTop.x, leftTop.y, (rc.right - rc.left) * _worldEditorRatio, (rc.bottom - rc.top) * _worldEditorRatio);
    return result;
}

RECT EditorScene::ScreenToWorld(RECT rc)
{
    POINT leftTop = ScreenToWorld(rc.left, rc.top);
    RECT result = RectMake(leftTop.x, leftTop.y, rc.right - rc.left, rc.bottom - rc.top);
    return result;
}

POINT EditorScene::WorldToScreen(long x, long y)
{
    //월드좌표를 에디터상 화면 좌표로 변환
    long resultX = (x - (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2)) * _worldEditorRatio;
    long resultY = y * _worldEditorRatio;

    return { resultX, resultY };
}

POINT EditorScene::ScreenToWorld(long x, long y)
{
    //에디터상의 좌표를 월드좌표로 변환
    //드래그되는 오브젝트의 실제 월드좌표 공식 = camera.x - (WINSIZEX/2 - ptMouse.x / ratio)
    long resultX = MainCam->transform->GetX() - (WINSIZEX / 2 - x / _worldEditorRatio);
    long resultY = y / _worldEditorRatio;
    return{ resultX ,resultY };
}

void EditorScene::InitObjectMenu()
{
    for (int i = 0; i < TYPE_NUM; i++)
    {
        _objectMenu[i].img = new image();
        _objectMenu[i].left = OBJECT_MENU_STARTX + OBJECT_MENU_TERM * i;
        _objectMenu[i].top = OBJECT_MENU_STARTY;
        _objectMenu[i].type = i;
    }

    _objectMenu[0].img->init("map/snow1.bmp", 108, 44, true, RGB(255, 0, 255));
    _objectMenu[0].width = 80;
    _objectMenu[0].height = 44;
    _objectMenu[0].rc = RectMake(_objectMenu[0].left, _objectMenu[0].top, _objectMenu[0].width, _objectMenu[0].height);

    _objectMenu[1].img->init("map/snow2.bmp", 164, 62, true, RGB(255, 0, 255));
    _objectMenu[1].width = 80;
    _objectMenu[1].height = 50;
    _objectMenu[1].rc = RectMake(_objectMenu[1].left, _objectMenu[1].top, _objectMenu[1].width, _objectMenu[1].height);

    _objectMenu[2].img->init("map/fence_pillar.bmp", 114, 168, true, RGB(255, 0, 255));
    _objectMenu[2].width = 80;
    _objectMenu[2].height = 100;
    _objectMenu[2].rc = RectMake(_objectMenu[2].left, _objectMenu[2].top, _objectMenu[2].width, _objectMenu[2].height);

    _objectMenu[3].img->init("map/fence_pillar2.bmp", 114, 156, true, RGB(255, 0, 255));
    _objectMenu[3].width = 80;
    _objectMenu[3].height = 100;
    _objectMenu[3].rc = RectMake(_objectMenu[3].left, _objectMenu[3].top, _objectMenu[3].width, _objectMenu[3].height);

    _objectMenu[4].img->init("lee/lee_block_left.bmp", 88, 132, true, RGB(255, 0, 255));
    _objectMenu[4].width = 80;
    _objectMenu[4].height = 100;
    _objectMenu[4].rc = RectMake(_objectMenu[4].left, _objectMenu[4].top, _objectMenu[4].width, _objectMenu[4].height);
}

void EditorScene::InitTypeName()
{
    _typeNameArr[0] = "Snow1";
    _typeNameArr[1] = "Snow2";
    _typeNameArr[2] = "fencePillar1";
    _typeNameArr[3] = "fencePillar2";
    _typeNameArr[4] = "Lee";
}

void EditorScene::InitButton()
{
    _nextButton.img = new image();
    _nextButton.img->init("ui/next.bmp", 25, 25, true, RGB(255, 0, 255));
    _nextButton.rc = RectMakeCenter(NAME_STARTX + NAME_WIDTH + 13, NAME_STARTY - 10, 26, 26);

    _beforeButton.img = new image();
    _beforeButton.img->init("ui/before.bmp", 25, 25, true, RGB(255, 0, 255));
    _beforeButton.rc = RectMakeCenter(NAME_STARTX - 13, NAME_STARTY - 10, 26, 26);
}

void EditorScene::MoveScreen()
{
    if (KEYMANAGER->isStayKeyDown(VK_CONTROL))
    {
        MainCam->transform->MoveX(-(_mouseInfo.deltaX * 3));
    }
    else
    {
        MainCam->transform->MoveX(-_mouseInfo.deltaX);
    }
    if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
        MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
}

void EditorScene::DrawSelectRect()
{
    if (_selectIdxName == -1) return;
    HBRUSH hBit, oBit;
    hBit = CreateSolidBrush(RGB(100, 100, 255));
    oBit = (HBRUSH)SelectObject(backDC, hBit);
    Rectangle(backDC, _selectNameRect);
    SelectObject(backDC, oBit);
    DeleteObject(hBit);
}

void EditorScene::ClickObjectName(int idx)
{
    _selectIdxName = idx;
    MainCam->transform->SetX(_objectV[_selectIdxNameType][_selectIdxName]->transform->GetX());
    if (MainCam->transform->GetX() <= MainCam->GetRenderWidth() / 2)
        MainCam->transform->SetX(MainCam->GetRenderWidth() / 2);
}

void EditorScene::OutlineInit()
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

void EditorScene::SetOutline(GameObject* targetObject)
{
    _outline.transform->SetPosition(targetObject->transform->GetX(), targetObject->transform->GetY());
    _outline.GetComponent<Outline>()->SetTargetObject(targetObject);
    _outline.GetComponent<ZOrder>()->SetZ(targetObject->GetComponent<ZOrder>()->GetZ() - 1);
}

void EditorScene::RemoveObject(int objectType, int objectIdx)
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
            _selectIdxNameType = objectType - 1;
        else
            _selectIdxNameType = TYPE_NUM - 1;
		_selectIdxName = 0;
    }
    else
    {
        if(objectIdx != 0)
            _selectIdxName = objectIdx - 1;
        else
        {
            _selectIdxName = _objectV[objectType].size() - 1;
        }
    }
    ClickObjectName(_selectIdxName);
    SetOutline(_objectV[_selectIdxNameType][_selectIdxName]);
}

