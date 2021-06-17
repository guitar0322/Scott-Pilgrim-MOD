#pragma once
#include "GameObject.h"
class AnimObject :
    public GameObject
{
public:
    AnimObject();
    ~AnimObject();
    Renderer* renderer;
    Animator* animator;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    void AddAnimationClip(string clipName, AnimationClip* newClip);
};

