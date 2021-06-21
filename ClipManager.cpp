#include "stdafx.h"
#include "ClipManager.h"
void ClipManager::Init()
{
}
void ClipManager::Release()
{
}
//map�� ����� Ŭ���� �̸�, �̹��� ���� ���("*.bmp"), �̹��� ����, �̹��� ũ��, �����Ӱ���, �����Ӱ���(���� ��, ex - 0.08f)
//�߰��� AnimationClip�����͸� ��ȯ
AnimationClip* ClipManager::AddClip(string clipName, const char* fileName, int width, int height, int frameNum, float frameTerm)
{
    AnimationClip* clip = FindClip(clipName);

    if (clip != nullptr)
        return clip;

    clip = new AnimationClip();

    clip->Init(fileName, width, height, frameNum, frameTerm);
    _clipMap.insert(pair<string, AnimationClip*>(clipName, clip));

    return clip;
}

//AddClip���� �߰��� clipName���� AnimationClip�� ã����, ã�� ������ ��� nullptr�� ��ȯ
AnimationClip* ClipManager::FindClip(string clipName)
{
    _clipMapIter = _clipMap.find(clipName);

    //ã�Ҵ�!
    if (_clipMapIter != _clipMap.end())
    {
        return _clipMapIter->second;
    }

    return nullptr;
}
