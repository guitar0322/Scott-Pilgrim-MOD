#include "stdafx.h"
#include "ClipManager.h"
void ClipManager::Init()
{
}
void ClipManager::Release()
{
}
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

AnimationClip* ClipManager::FindClip(string clipName)
{
    _clipMapIter = _clipMap.find(clipName);

    //Ã£¾Ò´Ù!
    if (_clipMapIter != _clipMap.end())
    {
        return _clipMapIter->second;
    }

    return nullptr;
}
