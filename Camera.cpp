#include "stdafx.h"
#include "Camera.h"

Camera::Camera()
{
	CAMERAMANAGER->AddCamera(this);
}

Camera::~Camera()
{
}

void Camera::ResizeScreen(int screenWidth, int screenHeight)
{
	HDC hdc = GetDC(_hWnd);
	hBit = CreateCompatibleBitmap(hdc, WINSIZEX, WINSIZEY);

	oBit = (HBITMAP)SelectObject(screenDC, hBit);
	SetStretchBltMode(screenDC, COLORONCOLOR);

	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	ReleaseDC(_hWnd, hdc);
}

void Camera::Init()
{
	HDC hdc = GetDC(_hWnd);
	screenDC = CreateCompatibleDC(hdc);
	ResizeScreen(WINSIZEX, WINSIZEY);
	_maxX = MAPSIZEX;
	_maxY = MAPSIZEY;
	_renderWidth = _screenWidth;
	_renderHeight = _screenHeight;
	_screenStartX = 0;
	_screenStartY = 0;
	_isShake = false;
	_shakeWeight = 0;
	_shakeNum = 0;
	_shakeMode = 0;
	_shakeAngle = 0;
	_shakeDir = 1;
	ReleaseDC(_hWnd, hdc);
}

void Camera::Render(HDC frontDC)
{
	int startX = transform->GetX() - _renderWidth / 2;
	int startY = transform->GetY() - _renderHeight / 2;
	if (startX < 0) {
		startX = 0;
	}
	if (transform->GetX() + _renderWidth / 2 > _maxX) {
		startX = _maxX - _renderWidth;
	}
	if (startY < 0) {
		startY = 0;
	}
	if (transform->GetY() + _renderHeight / 2 > _maxY) {
		startY = _maxY - _renderHeight;
	}
	StretchBlt(screenDC, 0, 0, _screenWidth, _screenHeight,
		_backBuffer->getMemDC(), startX, startY, _renderWidth, _renderHeight, SRCCOPY);

	BitBlt(
		frontDC,		//������ DC	
		_screenStartX,	//������ ��ǥ(left)
		_screenStartY,	//������ ��ǥ(top)
		_screenWidth,	//������ ����ũ��
		_screenHeight,	//������ ����ũ��
		screenDC,		//����� DC
		0,
		0,
		SRCCOPY);	//�����Ҷ� ��������Ű�������~
}

void Camera::Update()
{
	if (_isShake == true) {
		int nextX = _shakeStart.first;
		int nextY = _shakeStart.second;
		switch (_shakeMode) {
		case 0:
			nextX += _shakeWeight * _shakeDir;
			break;
		case 1:
			nextY += _shakeWeight * _shakeDir;
			break;
		case 2:
			_shakeAngle = RND->getFloat(PI2);
			nextX += _shakeWeight * cosf(_shakeAngle);
			nextY += _shakeWeight * sinf(_shakeAngle);
			break;
		}
		transform->position.x = nextX;
		transform->position.y = nextY;
		_shakeDir *= -1;
	}
}

void Camera::Shake(int weight, int mode)
{
	_shakeWeight = weight;
	_isShake = true;
	_shakeNum = 0;
	_shakeMode = mode;
	_shakeStart = { transform->GetX(), transform->GetY() };
	_shakeDir = 1;
}

void Camera::ShakeOff()
{
	_isShake = false;
	transform->position.x = _shakeStart.first;
	transform->position.y = _shakeStart.second;
}

