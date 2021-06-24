#pragma once
class Timer
{
private:
	float		_timeScale;				//�ð� �����
	float		_timeElapsed;			//ƽ �ð�
	__int64		_curTime;				//���� �ð�
	__int64		_lastTime;				//������ �ð�
	__int64		_periodFrequency;		//�ֱ�

	unsigned long _frameRate;			//������ ��
	unsigned long _FPSframeCount;		//������ ��Ű��
	float _FPSTimeElapsed;				//�� ������ �� �����
	float _worldTime;					//�۵� �ð� �ѷ�

public:
	Timer();
	~Timer();

	HRESULT init();
	void tick(float lockFPS = 0.0f);
	unsigned long getFrameRate(char* str = NULL) const;
	inline float getElapsedTime() const { 
		return _timeElapsed; 
	}
	inline float getWorldTime() const { return _worldTime; }
};

