#pragma once
#include "GameObject.h"
class RockMan :
    public GameObject
{
public:
    Renderer* renderer;
    BoxCollider* collider;
    Animator* animator;
    PlayerControler* controler;
    AnimationClip* idleRight;
    AnimationClip* idleLeft;
    AnimationClip* runRight;
    AnimationClip* runLeft;
    AnimationClip* jumpRight;
    AnimationClip* jumpLeft;
    AnimationClip* wallRight;
    AnimationClip* wallLeft;
    AnimationClip* groundRight;
    AnimationClip* groundLeft;
    AnimationClip* fallRight;
    AnimationClip* fallLeft;
    AnimationClip* intro;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    void InitClip();
};

