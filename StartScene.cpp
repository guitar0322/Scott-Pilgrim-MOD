#include "stdafx.h"
#include "StartScene.h"
#include "Item.h"
#include "Player.h"
#include "WallObj.h"
#include "Wall.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

HRESULT StartScene::Init()
{
    Scene::Init();
    CameraInit();
    //sceneInfoLoader.SetLinkObjectVAddress(&_objectV);
    //sceneInfoLoader.LoadObjectInfo();
    //_objectV[0]->GetComponent<Renderer>()->SetAlphaMode(true, 125);
    //_objectV[0]->GetComponent<Renderer>()->SetScale(3.f, 3.f);

    //위에는 건들지 마시오
    //=============미리 만들어져 있는 예시 오브젝트============
    //AddComponent 및 GetComponent()->Init을 하는것이 번거롭기 때문에 필요한 컴포넌트를
    //미리 붙여 Init을 해놓는 GameObject클래스의 자식 클래스를 생성해놓았다.

    //1.ImageObject
    //Renderer컴포넌트가 미리 추가되어있는 오브젝트
    //imageObj->renderer 로 접근이 가능
    imageObj = new ImageObject();
	
    //2.Box
    //Renderer, BoxCollider가 미리 추가되어있는 오브젝트
    //->renderer,  ->collider 로 접근이 가능
    box = new Box();

    //3.Character
    //Renderer, BoxCollider, Animator, ZOrder, Ground 컴포넌트가 추가되어있는 오브젝트
    //->renderer, ->collider, ->animator, ->zOrder, ->ground로 접근 가능하다

	CLIPMANAGER->AddClip("trashbox", "item/trashbox.bmp", 100, 76, 1, 1);
	CLIPMANAGER->AddClip("chair", "item/chair.bmp", 41, 48, 1, 1);

    character = new Character();
    character->name = "character";
    character->zOrder->SetZ(character->transform->GetY() + 52);
	character->AddComponent(new Player);
	character->GetComponent<Player>()->Init();
	character->zOrder->Init();
	character->zOrder->SetZ(568 / 2 + 52);
	character->collider->isTrigger = true;
    character->AddComponent(new DebugText());
    character->GetComponent<DebugText>()->Init();
	//character->renderer->SetScale(3.f, 3.f);

    wall[0] = new WallObj();
    wall[0]->Init(0, 300, 1000, 300);
    wall[1] = new WallObj();
    wall[1]->Init(0, WINSIZEY, 1000, WINSIZEY);
    wall[2] = new WallObj();
    wall[2]->Init(800, 200, 1000, 300);

    testGround = new GameObject();
    testGround->transform->SetPosition(500, 350);
    testGround->AddComponent(new ZOrder());
    testGround->GetComponent<ZOrder>()->Init();
    testGround->AddComponent(new Ground());
    testGround->GetComponent<Ground>()->Init(100, 10, 0, 0);

	trashBox = new ItemObject();
	trashBox->Init();
	trashBox->item->SetItemImage("trashbox");
	trashBox->transform->SetPosition(640, 300);
	trashBox->zorder->Init();
	trashBox->zorder->SetZ(trashBox->transform->GetY() + 10);

	/* LUKE CLIP MANAGER  */
	CLIPMANAGER->AddClip("luke_idle_right", "luke/luke_idle_right.bmp", 320, 132, 4, 0.20f);
	CLIPMANAGER->AddClip("luke_idle_left", "luke/luke_idle_left.bmp", 320, 132, 4, 0.20f);
	CLIPMANAGER->AddClip("luke_run_right", "luke/luke_run_right.bmp", 1188, 134, 11, 0.20f);
	CLIPMANAGER->AddClip("luke_run_left", "luke/luke_run_left.bmp", 1188, 134, 11, 0.20f);
	CLIPMANAGER->AddClip("luke_attack_right", "luke/luke_attack_right.bmp", 585, 64, 9, 0.20f);
	CLIPMANAGER->AddClip("luke_attack_left", "luke/luke_attack_left.bmp", 585, 64, 9, 0.20f);

	// 210627 시영 추가 (Enemy Update)
    enemy = new Luke();
	enemy->transform->SetPosition(400, 300);
	enemy->ground->enable = false;
	enemy->enemyAI->SetPlayer(character);
	enemy->zOrder->SetZ(enemy->transform->GetY() + 132 / 2);
	enemy->enemyinfo->SetSpeed(30.f);

	
    
    BackgroundInit();
    WallInit();

    return S_OK;
}

void StartScene::Release()
{
}

void StartScene::Update()
{

    //if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) {
    //    character->transform->MoveX(15);
    //}
    for (int i = 0; i < _objectV.size(); i++) {
        _objectV[i]->Update();
    }
    mainCam->transform->SetPosition(character->transform->GetX(), mainCam->transform->GetY());
    testGround->Update();
	trashBox->Update();
    character->Update();
    BGMANAGER->Update();
    EFFECTMANAGER->Update();
    ZORDER->Update();
    mainCam->Update();

    // 210627 시영 추가 (Enemy Update)
    enemy->Update();
}

void StartScene::Render()
{
    BGMANAGER->Render();
    for (int i = 0; i < _objectV.size(); i++) {
        _objectV[i]->Render();
    }
    ZORDER->Render();
    for (int i = 0; i < WALL_NUM; i++) {
		wall[i]->Render();
    }
    testGround->Render();
	trashBox->Render();
    EFFECTMANAGER->Render();

    // 210627 시영 추가 (Enemy Update)
    //enemy->Render();

    sprintf_s(debug[0], "Player X : %f ", character->transform->GetX());
    sprintf_s(debug[1], "FPS : %d ", TIMEMANAGER->getFPS());
    TextOut(BackBuffer, mainCam->transform->GetX() - 300, 20, debug[0], strlen(debug[0]));
    TextOut(BackBuffer, mainCam->transform->GetX() - 300, 40, debug[1], strlen(debug[1]));
    TextOut(BackBuffer, mainCam->transform->GetX() - 300, 60, debug[2], strlen(debug[2]));
    mainCam->camera->Render(_hdc);


}

void StartScene::BackgroundInit()
{
    for (int i = 0; i < BG_NUM; i++) {
        char fileName[64];
        sprintf_s(fileName, "map/background%d.bmp", i + 1);
		background[i] = new ImageObject();
		background[i]->renderer->Init(fileName, 922, 680);
		background[i]->transform->SetPosition(922 * i + 922 /2, 680 /2);
		background[i]->name = "background";
        BGMANAGER->AddBackground(background[i]);
    }
	BGMANAGER->SetMargin(30);
	BGMANAGER->SetBackgroundWidth(922);
    BGMANAGER->SetPlayer(character->transform);
}

void StartScene::CameraInit()
{
    _mapWidth = 21206;
    _mapHeight = 680;
    MainCam->SetMapSize(_mapWidth, _mapHeight);
    MainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    MainCam->SetRenderHeight(568);
    MainCam->SetMapSize(21206, 680);
    SetBackBufferSize(_mapWidth, _mapHeight);
}

void StartScene::WallInit()
{
    wall[0] = new WallObj();
    wall[0]->Init(0, 300, 1000, 300);

    wall[1] = new WallObj();
    wall[1]->Init(0, WINSIZEY, 1000, WINSIZEY);

    wall[2] = new WallObj();
    wall[2]->Init(800, 200, 1000, 300);
}
