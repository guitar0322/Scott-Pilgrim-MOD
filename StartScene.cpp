#include "stdafx.h"
#include "StartScene.h"
#include "Item.h"
#include "Player.h"
#include "WallObj.h"
#include "Wall.h"
#include "Doberman.h"
#include "Matthew.h"
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
    sceneInfoLoader.SetLinkObjectVAddress(&_objectV);
    sceneInfoLoader.LoadObjectInfo();

    //������ �ǵ��� ���ÿ�
    //=============�̸� ������� �ִ� ���� ������Ʈ============
    //AddComponent �� GetComponent()->Init�� �ϴ°��� ���ŷӱ� ������ �ʿ��� ������Ʈ��
    //�̸� �ٿ� Init�� �س��� GameObjectŬ������ �ڽ� Ŭ������ �����س��Ҵ�.

    //1.ImageObject
    //Renderer������Ʈ�� �̸� �߰��Ǿ��ִ� ������Ʈ
    //imageObj->renderer �� ������ ����
    imageObj = new ImageObject();
	
    //2.Box
    //Renderer, BoxCollider�� �̸� �߰��Ǿ��ִ� ������Ʈ
    //->renderer,  ->collider �� ������ ����
    box = new Box();

    //3.Character
    //Renderer, BoxCollider, Animator, ZOrder, Ground ������Ʈ�� �߰��Ǿ��ִ� ������Ʈ
    //->renderer, ->collider, ->animator, ->zOrder, ->ground�� ���� �����ϴ�

	ItemImageClip();

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
    testGround->GetComponent<ZOrder>()->SetZ(400);
    testGround->AddComponent(new Ground());
    testGround->GetComponent<Ground>()->Init(100, 10, 0, 0);

	trashBox = new ItemObject();
	trashBox->Init();
	trashBox->item->SetItemImage("trashbox");
	trashBox->transform->SetPosition(640, 300);
	trashBox->zorder->Init();
	trashBox->zorder->SetZ(trashBox->transform->GetY() + 10);

	/* LEE CLIP MANAGER  */
	CLIPMANAGER->AddClip("lee_idle_right",     "lee/lee_idle_right.bmp",       400, 66, 8, 0.20f);
	CLIPMANAGER->AddClip("lee_idle_left",      "lee/lee_idle_left.bmp",        400, 66, 8, 0.20f);
	CLIPMANAGER->AddClip("lee_run_right",      "lee/lee_run_right.bmp",        432, 72, 8, 0.20f);
	CLIPMANAGER->AddClip("lee_run_left",       "lee/lee_run_left.bmp",         432, 72, 8, 0.20f);
	CLIPMANAGER->AddClip("lee_attack1_right",  "lee/lee_attack1_right.bmp",    280, 64, 4, 0.20f);
	CLIPMANAGER->AddClip("lee_attack1_left",   "lee/lee_attack1_left.bmp",     280, 64, 4, 0.20f);

	/*Doberman CLIP MANAGER*/
	CLIPMANAGER->AddClip("doberman_idle_left", "Doberman/idle_left.bmp", 656, 96, 4, 0.3f);
	CLIPMANAGER->AddClip("doberman_idle_right", "Doberman/idle_right.bmp", 656, 96, 4, 0.3f);
	CLIPMANAGER->AddClip("doberman_move_left", "Doberman/move_left.bmp", 1146, 96, 6, 0.2f);
	CLIPMANAGER->AddClip("doberman_move_right", "Doberman/move_right.bmp", 1146, 96, 6, 0.2f);
	//CLIPMANAGER->AddClip("runLeft", "Doberman/DogRunLeft.bmp", 1539, 96, 9, 0.1f));
	//CLIPMANAGER->AddClip("runRight", "Doberman/DogRunRight.bmp", 1539, 96, 9, 0.1f));
	CLIPMANAGER->AddClip("doberman_attack_left", "Doberman/attack_left.bmp", 1075, 96, 7, 0.2f);
	CLIPMANAGER->AddClip("doberman_attack_right", "Doberman/attack_right.bmp", 1075, 96, 7, 0.2f);



	// 210627 �ÿ� �߰� (Enemy Update)

 //   enemy = new Luke();
	//enemy->transform->SetPosition(800, 300);

	//enemy->ground->enable = false;
	//enemy->enemyAI->SetPlayer(character);
	//enemy->zOrder->SetZ(enemy->transform->GetY() + 132 / 2);
	//enemy->enemyinfo->SetSpeed(30.f);
 //   
	//// 210628 ��ö �������� ���� //
	//doberman = new Doberman();
 //   doberman->transform->SetPosition(1200, 400);

	//doberman->ground->enable = false;
	//doberman->enemyAI->SetPlayer(character);
	//doberman->zOrder->SetZ(enemy->transform->GetX() + 132 / 2);
	//doberman->enemyinfo->SetSpeed(100.f);

	//// ���� ��Ʃ ����//

	//matthew = new Character();
	//matthew->Init();
	//matthew->transform->SetPosition(2000, 400);
	//matthew->collider->isTrigger = true;
	//matthew->AddComponent(new Matthew());
	//matthew->GetComponent<Matthew>()->Init();
	//matthew->GetComponent<Matthew>()->SetPlayer(character);

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
	//matthew->Update();

	//doberman->Update();
	//matthew->Update();

    // 210627 �ÿ� �߰� (Enemy Update)
	//enemy->Update();
}

void StartScene::Render()
{
    BGMANAGER->Render();
    for (int i = 0; i < _objectV.size(); i++) {
        _objectV[i]->Render();
    }
	trashBox->Render();
    ZORDER->Render();
    for (int i = 0; i < WALL_NUM; i++) {
		wall[i]->Render();
    }
    testGround->Render();
	//matthew->Render();
	//doberman->Render();
    EFFECTMANAGER->Render();

    // 210627 �ÿ� �߰� (Enemy Render)
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

void StartScene::ItemImageClip()	
{
	CLIPMANAGER->AddClip("trashbox", "item/trashbox.bmp", 115, 87, 1, 1);
	CLIPMANAGER->AddClip("chair", "item/chair.bmp", 41, 48, 1, 1);

	//walk attack 
	CLIPMANAGER->AddClip("trashbox_walk_attack_right", "item/trashbox_walk_attack_right.bmp", 805, 93, 7, 0.2f);
	CLIPMANAGER->FindClip("trashbox_walk_attack_right")->isLoop = false;
	
	//trashBox->animator->AddClip("trashbox_walk_attack_right", CLIPMANAGER->FindClip("trashbox_walk_attack_right"));
}
