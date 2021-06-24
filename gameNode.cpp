#include "stdafx.h"
#include "gameNode.h"

gameNode::gameNode()
{
}


gameNode::~gameNode()
{
}

HRESULT gameNode::init()
{
	//_hdc = GetDC(_hWnd);

	SetTimer(_hWnd, 1, 10, NULL);

	return S_OK;
}

HRESULT gameNode::init(bool managerInit)
{
	//_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (_managerInit)
	{
		SetTimer(_hWnd, 1, 10, NULL);
		KEYMANAGER->init();
		IMAGEMANAGER->init();
		TAGMANAGER->init();
		TIMEMANAGER->init();
		SCENEMANAGER->Init();
		COLLIDERMANAGER->Init();
		GROUNDMANAGER->Init();
		SOUNDMANAGER->init();
		TXTDATAMANAGER->Init();
		CLIPMANAGER->Init();
		BGMANAGER->Init();
		WALLMANAGER->Init();
		EFFECTMANAGER->Init();
	}

	return S_OK;
}

void gameNode::release()
{
	KillTimer(_hWnd, 1);
	KEYMANAGER->release();
	KEYMANAGER->releaseSingleton();

	COLLIDERMANAGER->Release();
	COLLIDERMANAGER->releaseSingleton();

	TAGMANAGER->release();
	TAGMANAGER->releaseSingleton();

	TIMEMANAGER->release();
	TIMEMANAGER->releaseSingleton();

	SCENEMANAGER->Release();
	SCENEMANAGER->releaseSingleton();

	GROUNDMANAGER->Release();
	GROUNDMANAGER->releaseSingleton();

	SOUNDMANAGER->release();
	SOUNDMANAGER->releaseSingleton();

	TXTDATAMANAGER->release();
	TXTDATAMANAGER->releaseSingleton();

	CLIPMANAGER->Release();
	CLIPMANAGER->releaseSingleton();

	BGMANAGER->Release();
	BGMANAGER->releaseSingleton();

	WALLMANAGER->Release();
	WALLMANAGER->releaseSingleton();

	EFFECTMANAGER->Release();
	EFFECTMANAGER->releaseSingleton();
}

void gameNode::update()
{
	InvalidateRect(_hWnd, NULL, false);
}

void gameNode::render(HDC hdc)
{
	// 위에 건들지마라
	//================제발 이 사이에 좀 그립시다==========================

	//==================================================
	//여기도 건들지마라
}

LRESULT gameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC         hdc; //얘 찐 중요합니...


	switch (iMessage)
	{
		case WM_TIMER:
			this->update();
		break;
	
		case WM_PAINT:
		{
			hdc = BeginPaint(hWnd, &ps);

			this->render(hdc);

			EndPaint(hWnd, &ps);
			break;
		}
		break;
		//마우스 움직이면 여기서 메세지 발생
		case WM_MOUSEMOVE:
			_ptMouse.x = static_cast<float>(LOWORD(lParam));
			_ptMouse.y = static_cast<float>(HIWORD(lParam));

		break;
			//마우스 왼쪽 클릭(눌려지고 있을때 여기)

		case WM_KEYDOWN:

			switch (wParam)
			{
			case VK_ESCAPE:
				PostQuitMessage(0);
				break;
			}
			break;


			//윈도우 창 부쉬는(?) 
		case WM_DESTROY:
		//윈도우 종료함수
			PostQuitMessage(0);
		return 0;
	}


	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
	
}
