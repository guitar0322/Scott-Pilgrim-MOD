#include "stdafx.h"
#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Init(const char* filename, int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->width = width;
	this->height = height;
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);

	hBit = (HBITMAP)LoadImage(_hInstance, filename, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	oBit = (HBITMAP)SelectObject(memDC, hBit);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);

	ReleaseDC(_hWnd, hdc);
	alpha = 255;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = alpha;
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
}

void Renderer::Init()
{
	HDC hdc = GetDC(_hWnd);
	width = transform->GetWidth();
	height = transform->GetHeight();
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	oBit = (HBITMAP)SelectObject(memDC, hBit);
	SelectObject(alphaMemDC, hBit);
	alpha = 255;
	blendFunc.BlendOp = AC_SRC_OVER;
	blendFunc.BlendFlags = 0;
	blendFunc.AlphaFormat = 0;
	blendFunc.SourceConstantAlpha = alpha;
	rc = RectMakeCenter(this->transform->GetX(), transform->GetY(),
		width, height);
	ReleaseDC(_hWnd, hdc);
}

void Renderer::Render()
{
	if(!KEYMANAGER->isToggleKey(VK_TAB))
		Rectangle(_backBuffer->getMemDC(), rc);
	BitBlt(alphaMemDC, 0, 0, width, height, _backBuffer->getMemDC(), rc.left, rc.top, SRCCOPY);
	GdiTransparentBlt(
		alphaMemDC,					//����� ������ DC
		0,				//����� ��ǥ(left)
		0,					//����� ��ǥ(top)
		width,					//����� ũ�� (����ũ��)
		height,					//����� ũ�� (����ũ��)
		memDC,					//�����ؿ� DC 
		0, 0,					//�����ؿ� ������ǥ(left, top)
		width,					//�����ؿ� ����ũ��
		height,					//�����ؿ� ����ũ��
		RGB(255, 0, 255)		//�����Ҷ� ������ �ȼ���
	);
	AlphaBlend(
		_backBuffer->getMemDC(),					//����� ������ DC
		rc.left,				//����� ��ǥ(left)
		rc.top,					//����� ��ǥ(top)
		width,					//����� ũ�� (����ũ��)
		height,					//����� ũ�� (����ũ��)
		alphaMemDC,					//�����ؿ� DC 
		0, 0,					//�����ؿ� ������ǥ(left, top)
		width,					//�����ؿ� ����ũ��
		height,					//�����ؿ� ����ũ��
		blendFunc		//�����Ҷ� ������ �ȼ���
	);
}

void Renderer::Update()
{
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		width,
		height);
}

void Renderer::Resize(int newWidth, int newHeight)
{
	HDC hdc = GetDC(_hWnd);
	HDC temp;

	HBITMAP scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);
	SelectObject(memDC, oBit);
	oBit = (HBITMAP)SelectObject(memDC, scaleBitmap);

	scaleBitmap = CreateCompatibleBitmap(hdc, newWidth, newHeight);
	SelectObject(alphaMemDC, scaleBitmap);

	ReleaseDC(_hWnd, hdc);
	rc = RectMakeCenter(this->gameObject->transform->position.x,
		this->gameObject->transform->position.y,
		newWidth,
		newHeight);

	width = newWidth;
	height = newHeight;
}


