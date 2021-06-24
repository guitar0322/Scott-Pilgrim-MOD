#include "stdafx.h"
#include "TimeManager.h"


TimeManager::TimeManager()
	: _timer(NULL)
{
}


TimeManager::~TimeManager()
{
}

HRESULT TimeManager::init()
{
	_timer = new Timer;
	_timer->init();

	return S_OK;
}

void TimeManager::release()
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
	}
}

//FPS ���������� �����ϴ� ��
void TimeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}

}

void TimeManager::render(HDC hdc)
{
	char str[256];
	string strFrame;

	//���� �����
	SetBkMode(hdc, TRANSPARENT);

	SetTextColor(hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	{
		if (_timer != nullptr)
		{
			//������ ���
			wsprintf(str, "framePerSec : %d", _timer->getFrameRate());
			TextOut(hdc, 0, 0, str, strlen(str));

			//���� Ÿ�� (����ð�)
			sprintf_s(str, "worldTime : %f", _timer->getWorldTime());
			TextOut(hdc, 0, 20, str, strlen(str));

			//���� tick
			sprintf_s(str, "elapsedTime : %f", _timer->getElapsedTime());
			TextOut(hdc, 0, 40, str, strlen(str));
		}
	}
#else
	{
		if (_timer != nullptr)
		{
			//������ ���
			wsprintf(str, "framePerSec : %d", _timer->getFrameRate());
			TextOut(hdc, 0, 0, str, strlen(str));
		}
	}
#endif
}
