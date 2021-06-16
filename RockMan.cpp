#include "stdafx.h"
#include "RockMan.h"

void RockMan::Init()
{
    renderer = (Renderer*)(AddComponent(new Renderer()));
    renderer->Init();
    collider = (BoxCollider*)(AddComponent(new BoxCollider()));
    collider->Init();
    collider->SetSize(74, 90);
    animator = (Animator*)(AddComponent(new Animator()));
    animator->Init();
    controler = (PlayerControler*)AddComponent(new PlayerControler());
    controler->Init();
    tag = TAGMANAGER->GetTag("player");
    InitClip();
}

void RockMan::Update()
{
    GameObject::Update();
}

void RockMan::Render()
{
    GameObject::Render();
}

void RockMan::InitClip()
{
    idleRight = new AnimationClip();
    idleRight->Init("idle_right.bmp", 740, 90, 10, 0.3f);

    idleLeft = new AnimationClip();
    idleLeft->Init("idle_left.bmp", 740, 90, 10, 0.3f);

    runRight = new AnimationClip();
    runRight->Init("run_right.bmp", 1358, 94, 14, 0.10f);

    runLeft = new AnimationClip();
    runLeft->Init("run_left.bmp", 1358, 94, 14, 0.10f);

    jumpRight = new AnimationClip();
    jumpRight->Init("jump_right.bmp", 272, 114, 4, 0.13f);
    jumpRight->isLoop = false;

    jumpLeft = new AnimationClip();
    jumpLeft->Init("jump_left.bmp", 272, 114, 4, 0.13f);
    jumpLeft->isLoop = false;

    wallRight = new AnimationClip();
    wallRight->Init("wall_right.bmp", 272, 116, 4, 0.10f);
    wallRight->isLoop = false;

    wallLeft = new AnimationClip();
    wallLeft->Init("wall_left.bmp", 272, 116, 4, 0.10f);
    wallLeft->isLoop = false;

    groundRight = new AnimationClip();
    groundRight->Init("ground_right.bmp", 192, 102, 3, 0.10f);
    groundRight->isLoop = false;

    groundLeft = new AnimationClip();
    groundLeft->Init("ground_left.bmp", 192, 102, 3, 0.10f);
    groundLeft->isLoop = false;
    
    fallRight = new AnimationClip();
    fallRight->Init("fall_right.bmp", 272, 114, 4, 0.10f);
    fallRight->isLoop = false;

    fallLeft = new AnimationClip();
    fallLeft->Init("fall_left.bmp", 272, 114, 4, 0.10f);
    fallLeft->isLoop = false;
    
    intro = new AnimationClip();
    intro->Init("intro.bmp", 1920, 144, 15, 0.10f);
    intro->isLoop = false;

    animator->AddClip("idle_right", idleRight);
    animator->AddClip("idle_left", idleLeft);
    animator->AddClip("run_right", runRight);
    animator->AddClip("run_left", runLeft);
    animator->AddClip("jump_right", jumpRight);
    animator->AddClip("jump_left", jumpLeft);
    animator->AddClip("wall_right", wallRight);
    animator->AddClip("wall_left", wallLeft);
    animator->AddClip("ground_right", groundRight);
    animator->AddClip("ground_left", groundLeft);
    animator->AddClip("fall_right", fallRight);
    animator->AddClip("fall_left", fallLeft);
    animator->AddClip("intro", intro);

    animator->AddTransaction("ground_idle_right", groundRight, idleRight);
    animator->AddTransaction("ground_idle_left", groundLeft, idleLeft);

    animator->SetClip(animator->GetClip("idle_right"));
}
