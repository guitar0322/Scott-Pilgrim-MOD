#include "stdafx.h"
#include "UIRenderer.h"

UIRenderer::UIRenderer()
{
}

UIRenderer::~UIRenderer()
{
}

void UIRenderer::Init()
{
	HDC hdc = GetDC(_hWnd);
	_width = 100;
	_height = 100;
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	oBit = (HBITMAP)SelectObject(memDC, hBit);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _width, _height);
	SelectObject(alphaMemDC, hBit);

	ReleaseDC(_hWnd, hdc);
	transform->SetX(0);
	transform->SetY(0);
	alpha = 255;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.AlphaFormat = 0;
	blendFunction.SourceConstantAlpha = alpha;
	_isAlpha = false;
}

void UIRenderer::Init(const char* filename, int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->_width = width;
	this->_height = height;
	memDC = CreateCompatibleDC(hdc);
	alphaMemDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)LoadImage(_hInstance, filename, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	oBit = (HBITMAP)SelectObject(memDC, hBit);

	hBit = CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);

	ReleaseDC(_hWnd, hdc);
	transform->SetX(0);
	transform->SetY(0);
	alpha = 255;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.AlphaFormat = 0;
	blendFunction.SourceConstantAlpha = alpha;
	_isAlpha = false;
}

void UIRenderer::Update()
{
}

void UIRenderer::Render()
{
	int startX = SCENEMANAGER->GetCurScene()->mainCam->transform->GetX() + transform->GetX() - _width/2;
	int startY = SCENEMANAGER->GetCurScene()->mainCam->transform->GetY() + transform->GetY() - _height / 2;
	if (_isAlpha == false) {
		BitBlt(alphaMemDC, 0, 0, _width, _height, _backBuffer->getMemDC(), startX, startY, SRCCOPY);
		GdiTransparentBlt(
			alphaMemDC,			//����� ������ DC
			0,					//����� ��ǥ(left)
			0,					//����� ��ǥ(top)
			_width,				//����� ũ�� (����ũ��)
			_height,			//����� ũ�� (����ũ��)
			memDC,				//�����ؿ� DC 
			0, 0,				//�����ؿ� ������ǥ(left, top)
			_width,				//�����ؿ� ����ũ��
			_height,			//�����ؿ� ����ũ��
			RGB(255, 0, 255)	//�����Ҷ� ������ �ȼ���
		);
		AlphaBlend(
			_backBuffer->getMemDC(),	//����� ���� DC
			startX,						//����� DC���� �׸��� ���� ��ǥ x
			startY,						//����� DC���� �׸��� ���� ��ǥ y
			_width,						//����� DC���� �׸��� ���� ����
			_height,					//����� DC���� �׸��� ���� ����
			alphaMemDC,					//�׸��� DC
			0,							//�׸����� �׸��� ������ ��ǥ x
			0,							//�׸����� �׸��� ������ ��ǥ y
			_width,						//�׸����� ���DC�� �׸� �׸��� ���� ����
			_height,					//�׸����� ���DC�� �׸� �׸��� ���� ����
			blendFunction);				//���ĺ��忡���� �ɼǰ�
	}
	else {
		GdiTransparentBlt(
			alphaMemDC,			//����� ������ DC
			startX,				//����� ��ǥ(left)
			startY,				//����� ��ǥ(top)
			_width,				//����� ũ�� (����ũ��)
			_height,			//����� ũ�� (����ũ��)
			memDC,				//�����ؿ� DC 
			0, 0,				//�����ؿ� ������ǥ(left, top)
			_width,				//�����ؿ� ����ũ��
			_height,			//�����ؿ� ����ũ��
			RGB(255, 0, 255)	//�����Ҷ� ������ �ȼ���
		);
	}
}
//�������� ����� ������
void UIRenderer::Resize(int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->_width = width;
	this->_height = height;
	memDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(memDC, oBit);
	oBit = (HBITMAP)SelectObject(memDC, hBit);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);
}

void UIRenderer::SetAlphaMode(bool isAlpha, int alpha)
{
	_isAlpha = isAlpha;
	SetAlpha(alpha);
}

void UIRenderer::SetAlpha(int alpha)
{
	this->alpha = alpha;
	blendFunction.SourceConstantAlpha = this->alpha;
}

//�������� DC������ �ܻ����� ä��
void UIRenderer::FillColor(COLORREF color)
{
	HBRUSH hBrush, oBrush;
	hBrush = CreateSolidBrush(color);
	oBrush = (HBRUSH)SelectObject(memDC, hBrush);
	PatBlt(memDC, 0, 0, _width, _height, PATCOPY);
	SelectObject(memDC, oBrush);
	DeleteObject(hBrush);
}
