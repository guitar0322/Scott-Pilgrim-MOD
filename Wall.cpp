#include "stdafx.h"
#include "Wall.h"

void Wall::Init(int startX, int startY, int endX, int endY)
{
	_startX = startX;
	_startY = startY;
	_endX = endX;
	_endY = endY;

	//y = ax + b;
	//����� a(_gradient)�� y�� ��ȭ�� / x�� ��ȭ��
	_gradient = (_endY - _startY) / (_endX - _startX);
	//y����(_interceptY)�� y - ax
	_interceptY = _startY - (_gradient * _startX);

	WALLMANAGER->AddWall(this);
}

void Wall::Update()
{
}

void Wall::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB)) 
	{
		LineMake(_backBuffer->getMemDC(), _startX, _startY, _endX, _endY);
	}
}

void Wall::SetStartPoint(int startX, int startY)
{
	_startX = startX;
	_startY = startY;

	_gradient = (_endY - _startY) / (_endX - _startX);
	_interceptY = _startY - (_gradient * _startX);
}

void Wall::SetEndPoint(int endX, int endY)
{
	_endX = endX;
	_endY = endY;

	_gradient = (_endY - _startY) / (_endX - _startX);
	_interceptY = _startY - (_gradient * _startX);
}

bool Wall::IsCross(int startX, int startY, int endX, int endY)
{
	//������Ʈ�� �̵��Ҷ� �������� ������ 1�� �ε���� ��ȣ�� �ٸ����
	//���� �Ѵ°����� �Ǵ�
	int start = CalcUpDown(startX, startY);//�������� ��ȣ
	int end = CalcUpDown(endX, endY);//���������� ��ȣ
	//������Ʈ�� ���� ���� �ȿ� ���� ��츸 �Ǵ�
	if (IsInLine(startX, startY) == false)
		return false;
	//�������� ���������� ��ȣ�� �ٸ� ��� ���� �Ѵ°�
	if (start != end)
		return true;

	return false;
}

int Wall::CalcUpDown(float x, float y)
{
	//1�� �Լ����� �����Ͽ� y��ǥ�� ������ ���� �ִ��� �Ʒ� �ִ��� �Ǵ�
	if (y <= _gradient * x + _interceptY)
		return -1;
	else
		return 1;
}

bool Wall::IsInLine(float x, float y)
{
	float bigX = (_startX > _endX) ? _startX : _endX;
	float smallX = (_startX < _endX) ? _startX : _endX;
	float bigY = (_startY > _endY) ? _startY : _endY;
	float smallY = (_startY < _endY) ? _startY : _endY;

	if (_startY == _endY) 
	{
		if (x > smallX && x < bigX)
			return true;
	}
	if (_startX == _endX) 
	{
		if (y > smallY && y < bigY)
			return true;
	}

	if (x > smallX && x < bigX && y > smallY && y < bigY)
		return true;

	return false;
}
