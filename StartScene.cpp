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

	/* LEE CLIP MANAGER */
   // IDLE
	CLIPMANAGER->AddClip("lee_idle_right", "lee/lee_idle_right.bmp", 800, 132, 8, 0.20f);
	CLIPMANAGER->AddClip("lee_idle_left", "lee/lee_idle_left.bmp", 800, 132, 8, 0.20f);
	// WALK               
	CLIPMANAGER->AddClip("lee_walk_right", "lee/lee_walk_right.bmp", 576, 138, 6, 0.20f);
	CLIPMANAGER->AddClip("lee_walk_left", "lee/lee_walk_left.bmp", 576, 138, 6, 0.20f);
	// RUN                
	CLIPMANAGER->AddClip("lee_run_right", "lee/lee_run_right.bmp", 864, 144, 8, 0.20f);
	CLIPMANAGER->AddClip("lee_run_left", "lee/lee_run_left.bmp", 864, 144, 8, 0.20f);
	// BLOCK              
	CLIPMANAGER->AddClip("lee_block_right", "lee/lee_block_right.bmp", 88, 132, 1, 0.20f);
	CLIPMANAGER->AddClip("lee_block_left", "lee/lee_block_left.bmp", 88, 132, 1, 0.20f);
	// HIT                
	CLIPMANAGER->AddClip("lee_hit_right", "lee/lee_hit_right.bmp", 550, 134, 5, 0.20f);
	CLIPMANAGER->AddClip("lee_hit_left", "lee/lee_hit_left.bmp", 550, 134, 5, 0.20f);
	// KICK               
	CLIPMANAGER->AddClip("lee_kick_right", "lee/lee_kick_right.bmp", 1050, 136, 7, 0.20f);
	CLIPMANAGER->AddClip("lee_kick_left", "lee/lee_kick_left.bmp", 1050, 136, 7, 0.20f);
	// ATTACK 1       
	CLIPMANAGER->AddClip("lee_attack1_right", "lee/lee_attack1_right.bmp", 560, 128, 4, 0.20f);
	CLIPMANAGER->AddClip("lee_attack1_left", "lee/lee_attack1_left.bmp", 560, 128, 4, 0.20f);
	// ATTACK 2
	CLIPMANAGER->AddClip("lee_attack2_right", "lee/lee_attack2_right.bmp", 568, 132, 4, 0.20f);
	CLIPMANAGER->AddClip("lee_attack2_left", "lee/lee_attack2_left.bmp", 568, 132, 4, 0.20f);
	// ATTACK 3       
	CLIPMANAGER->AddClip("lee_attack3_right", "lee/lee_attack3_right.bmp", 672, 156, 7, 0.20f);
	CLIPMANAGER->AddClip("lee_attack3_left", "lee/lee_attack3_left.bmp", 672, 156, 7, 0.20f);
	// DIE                
	CLIPMANAGER->AddClip("lee_die_right", "lee/lee_die_right.bmp", 2072, 172, 14, 0.20f);
	CLIPMANAGER->AddClip("lee_die_left", "lee/lee_die_left.bmp", 2072, 172, 14, 0.20f);

	// 210627 �ÿ� �߰� (Enemy Update)
	enemy = new Luke();
	enemy->Init();
	enemy->transform->SetPosition(800, 300);
	enemy->ground->enable = false;
	enemy->enemyAI->SetPlayer(character);

	character->GetComponent<Player>()->SetEnemy(enemy);
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
	/*matthew->Update();
	doberman->Update();*/

    // 210627 �ÿ� �߰� (Enemy Update)
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
