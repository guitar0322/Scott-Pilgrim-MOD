#include "stdafx.h"
#include "EffectManager.h"

EffectManager::EffectManager()
{
}

EffectManager::~EffectManager()
{
}

void EffectManager::Init()
{
	for (int i = 0; i < EFFECT_MIN; i++)
	{
		EFFECTINFO effectInfo;
		ZeroMemory(&effectInfo, sizeof(EFFECTINFO));
		_effectV.push_back(effectInfo);
	}
}

void EffectManager::Update()
{
	for (_effectIter = _effectV.begin(); _effectIter != _effectV.end();) 
	{
		if (_effectIter->active == false)
		{
			_effectIter++;
			continue;
		}
		//����Ʈ�� �ִ��������� �ȵǸ� ���ͷ����͸� ������Ű�鼭 ����
		if (_effectIter->curFrame != _effectIter->maxFrame)
		{
			_effectIter->time += TIMEMANAGER->getElapsedTime();
			if (_effectIter->time >= _effectIter->frameTerm) {//������ �ð��� ���ݺ��� Ŀ����
				_effectIter->curFrame++;//���� ���������� �̵�
				_effectIter->time = 0;//������ �ð� �ʱ�ȭ
			}
			_effectIter++;//����Ʈ�� ����Ȱ��� �ƴϸ� ���ͷ����͸� ����
		}
		//����Ʈ�� �ִ��������� ���� ���
		else if(_effectV.size() > EFFECT_MIN)
			//����Ʈ�� ������ �ּҰ������� ���ٸ� ����Ʈ�� ���Ϳ��� erase
			_effectIter = _effectV.erase(_effectIter);
		else
			//����Ʈ ������ �ּҰ������� ���ٸ� erase���� �ʰ� active�� �ʱ�ȭ
			_effectIter->active = false;
	}
}

void EffectManager::Render()
{
	for (int i = 0; i < _effectV.size(); i++) {
		if (_effectV[i].active == false) continue;
		AnimationClip* curClip = CLIPMANAGER->FindClip(_effectV[i].clipName);
		GdiTransparentBlt(_backBuffer->getMemDC(),
			_effectV[i].x, _effectV[i].y,
			curClip->frameWidth, curClip->frameHeight,
			curClip->wholeDC,
			curClip->frameWidth * _effectV[i].curFrame, 0,
			curClip->frameWidth, curClip->frameHeight,
			RGB(255, 0, 255));
	}
}

void EffectManager::Release()
{
	_effectV.clear();
}

void EffectManager::EmissionEffect(string effectClipName, int x, int y)
{
	AnimationClip targetClip = *CLIPMANAGER->FindClip(effectClipName);
	if (GetActiveNum() == EFFECT_MIN) 
	{
		EFFECTINFO effectInfo;
		effectInfo.x = x - targetClip.frameWidth / 2;
		effectInfo.y = y - targetClip.frameHeight / 2;
		effectInfo.active = true;
		effectInfo.time = 0;
		effectInfo.curFrame = 0;
		effectInfo.maxFrame = targetClip.frameNum;
		effectInfo.frameTerm = targetClip.frameTerm;
		effectInfo.clipName = effectClipName;
		_effectV.push_back(effectInfo);
	}
	else
	{
		for (int i = 0; i < EFFECT_MIN; i++)
		{
			if (_effectV[i].active == true) continue;
			_effectV[i].x = x - targetClip.frameWidth / 2;
			_effectV[i].y = y - targetClip.frameHeight / 2;
			_effectV[i].active = true;
			_effectV[i].time = 0;
			_effectV[i].curFrame = 0;
			_effectV[i].maxFrame = targetClip.frameNum;
			_effectV[i].frameTerm = targetClip.frameTerm;
			_effectV[i].clipName = effectClipName;
			break;
		}
	}
}

int EffectManager::GetActiveNum()
{
	int result = 0;
	for (int i = 0; i < EFFECT_MIN; i++) {
		if (_effectV[i].active == true)
			result++;
	}
	return result;
}
