﻿#pragma once
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <iostream>
#include <typeinfo>
#include <vector>
#include "commonMacroFunction.h"
#include "randomFunction.h"
#include "keyManager.h"
#include "ColliderManager.h"
#include "ImageManager.h"
#include "CameraManager.h"
#include "TagManager.h"
#include "TextDataManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "utils.h"

using namespace std;
using namespace HDY_UTIL;

//==================================
// ## 매크로 처리 ## 21.04.23 ##
//==================================

#define WINNAME (LPTSTR)(TEXT("28기 API"))
#define WINSTARTX 200	//윈도우 창 시작좌표 (left)
#define WINSTARTY 50	//윈도우 창 시작좌표 (top)
#define WINSIZEX 640	//윈도우 가로크기
#define WINSIZEY 480	//윈도우 세로크기
#define WINSTYLE WS_CAPTION | WS_SYSMENU
#define MAPSIZEX 4023
#define MAPSIZEY 3024

#define RND randomFunction::getSingleton()
#define KEYMANAGER keyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define COLLIDERMANAGER ColliderManager::getSingleton()
#define CAMERAMANAGER CameraManager::getSingleton()
#define TAGMANAGER TagManager::getSingleton()
#define DATAMANAGER TextDataManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()

#define SAFE_DELETE(p) {if(p) {delete(p); (p) = nullptr;}}

static image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", MAPSIZEX, MAPSIZEY);

//==================================
// ## extern ## 21.04.28 ##
//==================================
extern HINSTANCE _hInstance;
extern HWND _hWnd;
extern POINT _ptMouse;
extern char debug[3][128];
extern char error[128];
extern HDC _hdc;