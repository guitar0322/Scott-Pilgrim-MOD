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
	width = 100;
	height = 100;
	memDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	oBit = (HBITMAP)SelectObject(memDC, hBit);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);

	ReleaseDC(_hWnd, hdc);
	transform->SetX(0);
	transform->SetY(0);
	alpha = 255;
	blendFunction.BlendOp = AC_SRC_OVER;
	blendFunction.BlendFlags = 0;
	blendFunction.AlphaFormat = 0;
	blendFunction.SourceConstantAlpha = alpha;
}

void UIRenderer::Init(const char* filename, int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->width = width;
	this->height = height;
	memDC = CreateCompatibleDC(hdc);
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
}

void UIRenderer::Update()
{
}

void UIRenderer::Render()
{
	int startX = CAMERAMANAGER->mainCam->transform->GetX() + transform->GetX() - width/2;
	int startY = CAMERAMANAGER->mainCam->transform->GetY() + transform->GetY() - height / 2;
	BitBlt(alphaMemDC, 0, 0, width, height, _backBuffer->getMemDC(), startX, startY, SRCCOPY);
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
	AlphaBlend(_backBuffer->getMemDC(),			//����� ���� DC
		startX,					//����� DC���� �׸��� ���� ��ǥ x
		startY,					//����� DC���� �׸��� ���� ��ǥ y
		width,		//����� DC���� �׸��� ���� ����
		height,		//����� DC���� �׸��� ���� ����
		memDC,			//�׸��� DC
		0,					//�׸����� �׸��� ������ ��ǥ x
		0,					//�׸����� �׸��� ������ ��ǥ y
		width,		//�׸����� ���DC�� �׸� �׸��� ���� ����
		height,		//�׸����� ���DC�� �׸� �׸��� ���� ����
		blendFunction);	//���ĺ��忡���� �ɼǰ�
}

void UIRenderer::Resize(int width, int height)
{
	HDC hdc = GetDC(_hWnd);
	this->width = width;
	this->height = height;
	memDC = CreateCompatibleDC(hdc);
	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(memDC, oBit);
	oBit = (HBITMAP)SelectObject(memDC, hBit);

	hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	SelectObject(alphaMemDC, hBit);

}

void UIRenderer::SetAlpha(int alpha)
{
	this->alpha = alpha;
	blendFunction.SourceConstantAlpha = this->alpha;
}
