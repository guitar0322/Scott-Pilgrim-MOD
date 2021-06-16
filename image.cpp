#include "stdafx.h"
#include "image.h"

#pragma comment(lib, "msimg32.lib")

//��� �̴ϼȶ�����
image::image()
	: _imageInfo(NULL),
	_fileName(NULL),
	_trans(false),
	_transColor(RGB(0,0,0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc); //�� DC���� ��������
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	//���� �ʱ�ȭ�� ������ߴµ� �� �ȵƴٸ�?
	if (_imageInfo == nullptr)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	//DC�� ������ ����Ҷ� GetDC()
	HDC hdc = GetDC(_hWnd);

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, _fileName, IMAGE_BITMAP, _imageInfo->width, _imageInfo->height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);



	//���࿡ �̹��� �ʱ�ȭ�� �����ϸ�
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}


	//DC�� �����ͼ� ����ϰ� ���� �������ش�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	//DC�� ������ ����Ҷ� GetDC()
	HDC hdc = GetDC(_hWnd);

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, _fileName, IMAGE_BITMAP, _imageInfo->width, _imageInfo->height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;


	//���࿡ �̹��� �ʱ�ȭ�� �����ϸ�
	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}


	//DC�� �����ͼ� ����ϰ� ���� �������ش�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor)
{
	if (_imageInfo != NULL) release();

	//DC�� ������ ����Ҷ� GetDC()
	HDC hdc = GetDC(_hWnd);

	int len = strlen(fileName);
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	_trans = trans;
	_transColor = transColor;

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, _fileName, IMAGE_BITMAP, _imageInfo->width, _imageInfo->height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	//���࿡ �̹��� �ʱ�ȭ�� �����ϸ�
	if (_imageInfo->hBit == NULL)
	{
		release();
		return E_FAIL;
	}

	//DC�� �����ͼ� ����ϰ� ���� �������ش�
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::ScaleImage(float ratio)
{
	HDC hdc = GetDC(_hWnd);

	HDC tempMemDC = CreateCompatibleDC(hdc);
	HBITMAP newHbit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width * ratio, _imageInfo->height * ratio);
	SelectObject(tempMemDC, newHbit);
	StretchBlt(tempMemDC,
		0, 0,
		_imageInfo->width * ratio,
		_imageInfo->height * ratio,
		_imageInfo->hMemDC,
		0, 0,
		_imageInfo->width,
		_imageInfo->height,
		SRCCOPY
	);
	SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
	newHbit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width * ratio, _imageInfo->height * ratio);
	_imageInfo->hBit = newHbit;
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, newHbit);
	BitBlt(_imageInfo->hMemDC, 0, 0, _imageInfo->width * ratio, _imageInfo->height * ratio, tempMemDC, 0, 0, SRCCOPY);
	_imageInfo->width *= ratio;
	_imageInfo->height *= ratio;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);

		_trans = false;
		_transColor = RGB(0, 0, 0);
	}


}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}


void image::render(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//����� ������ DC
			destX,				//����� ��ǥ(left)
			destY,				//����� ��ǥ(top)
			_imageInfo->width,	//����� ũ�� (����ũ��)
			_imageInfo->height,	//����� ũ�� (����ũ��)
			_imageInfo->hMemDC,	//�����ؿ� DC 
			0, 0,				//�����ؿ� ������ǥ(left, top)
			_imageInfo->width,	//�����ؿ� ����ũ��
			_imageInfo->height,	//�����ؿ� ����ũ��
			_transColor			//�����Ҷ� ������ �ȼ���
		);
	}
	else
	{
		//DC�������� ��Ӻ���
		BitBlt(
			hdc,					//������ DC	
			destX,					//������ ��ǥ(left)
			destY,					//������ ��ǥ(top)
			_imageInfo->width,		//������ ����ũ��
			_imageInfo->height,	//������ ����ũ��
			_imageInfo->hMemDC,	//����� DC
			0, 0,					//����� ������ǥ(left, top)
			SRCCOPY);				//�����Ҷ� ��������Ű�������~
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,				//����� ������ DC
			destX,				//����� ��ǥ(left)
			destY,				//����� ��ǥ(top)
			sourWidth,			//����� ũ�� (����ũ��)
			sourHeight,			//����� ũ�� (����ũ��)
			_imageInfo->hMemDC,	//�����ؿ� DC 
			sourX, sourY,		//�����ؿ� ������ǥ(left, top)
			sourWidth,			//�����ؿ� ����ũ��
			sourHeight,			//�����ؿ� ����ũ��
			_transColor			//�����Ҷ� ������ �ȼ���
		);
	}
	else
	{
		//DC�������� ��Ӻ���
		BitBlt(
			hdc,					//������ DC	
			destX,					//������ ��ǥ(left)
			destY,					//������ ��ǥ(top)
			sourWidth,				//������ ����ũ��
			sourHeight,				//������ ����ũ��
			_imageInfo->hMemDC,		//����� DC
			sourX, sourY,			//����� ������ǥ(left, top)
			SRCCOPY);				//�����Ҷ� ��������Ű�������~

	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//����� ������ DC
			destX,						//����� ��ǥ(left)
			destY,						//����� ��ǥ(top)
			_imageInfo->frameWidth,		//����� ũ�� (����ũ��)
			_imageInfo->frameHeight,	//����� ũ�� (����ũ��)
			_imageInfo->hMemDC,			//�����ؿ� DC 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,				//�����ؿ� ������ǥ(left, top)
			_imageInfo->frameWidth,		//�����ؿ� ����ũ��
			_imageInfo->frameHeight,	//�����ؿ� ����ũ��
			_transColor					//�����Ҷ� ������ �ȼ���
		);
	}
	else
	{
		//DC�������� ��Ӻ���
		BitBlt(
			hdc,					//������ DC	
			destX,					//������ ��ǥ(left)
			destY,					//������ ��ǥ(top)
			_imageInfo->frameWidth,	//������ ����ũ��
			_imageInfo->frameHeight,//������ ����ũ��
			_imageInfo->hMemDC,		//����� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//����� ������ǥ(left, top)
			SRCCOPY);				//�����Ҷ� ��������Ű�������~

	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		GdiTransparentBlt(
			hdc,						//����� ������ DC
			destX,						//����� ��ǥ(left)
			destY,						//����� ��ǥ(top)
			_imageInfo->frameWidth,		//����� ũ�� (����ũ��)
			_imageInfo->frameHeight,	//����� ũ�� (����ũ��)
			_imageInfo->hMemDC,			//�����ؿ� DC 
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,				//�����ؿ� ������ǥ(left, top)
			_imageInfo->frameWidth,		//�����ؿ� ����ũ��
			_imageInfo->frameHeight,	//�����ؿ� ����ũ��
			_transColor					//�����Ҷ� ������ �ȼ���
		);
	}
	else
	{
		//DC�������� ��Ӻ���
		BitBlt(
			hdc,					//������ DC	
			destX,					//������ ��ǥ(left)
			destY,					//������ ��ǥ(top)
			_imageInfo->frameWidth,	//������ ����ũ��
			_imageInfo->frameHeight,//������ ����ũ��
			_imageInfo->hMemDC,		//����� DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//����� ������ǥ(left, top)
			SRCCOPY);				//�����Ҷ� ��������Ű�������~

	}
}

