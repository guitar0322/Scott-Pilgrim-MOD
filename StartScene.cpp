#include "stdafx.h"
#include "StartScene.h"
#include "Item.h"
#include "Player.h"
#include "WallObj.h"
#include "Wall.h"
#include "Doberman.h"
#include "Matthew.h"
#include "Malcolm.h"
#include "William.h"
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

	/*Doberman CLIP MANAGER*/
	CLIPMANAGER->AddClip("doberman_idle_left", "doberman/idle_left.bmp", 656, 96, 4, 0.3f);
	CLIPMANAGER->AddClip("doberman_idle_right", "doberman/idle_right.bmp", 656, 96, 4, 0.3f);
	CLIPMANAGER->AddClip("doberman_move_left", "doberman/move_left.bmp", 1146, 96, 6, 0.2f);
	CLIPMANAGER->AddClip("doberman_move_right", "doberman/move_right.bmp", 1146, 96, 6, 0.2f);
	CLIPMANAGER->AddClip("doberman_attack_left", "doberman/attack_left.bmp", 1075, 96, 7, 0.2f);
	CLIPMANAGER->AddClip("doberman_attack_right", "doberman/attack_right.bmp", 1075, 96, 7, 0.2f);
	CLIPMANAGER->AddClip("doberman_hit_left", "doberman/hit_left.bmp", 664, 160, 4, 0.2f);
	CLIPMANAGER->AddClip("doberman_hit_right", "doberman/hit_right.bmp", 664, 160, 4, 0.2f);

	/*malcolm*/
	CLIPMANAGER->AddClip("malcolm_idle_left","malcolm/malcolm_idle_left.bmp",456,159,4,0.3f);
	CLIPMANAGER->AddClip("malcolm_idle_right","malcolm/malcolm_idle_right.bmp",456,159,4,0.3f);
	CLIPMANAGER->AddClip("malcolm_move_left","malcolm/malcolm_move_left.bmp",832,164,8,0.3f);
	CLIPMANAGER->AddClip("malcolm_move_right","malcolm/malcolm_move_right.bmp",832,164,8,0.2f);
	CLIPMANAGER->AddClip("malcolm_run_left","malcolm/malcolm_run_left.bmp",1320,158,8,0.2f);
	CLIPMANAGER->AddClip("malcolm_run_right", "malcolm/malcolm_run_right.bmp", 1320, 158, 8, 0.2f);
	CLIPMANAGER->AddClip("malcolm_attack_left", "malcolm/malcolm_attack_left.bmp", 1638, 174, 9, 0.2f);
	CLIPMANAGER->AddClip("malcolm_attack_right","malcolm/malcolm_attack_right.bmp",1638,174,9,0.2f);
	CLIPMANAGER->AddClip("malcolm_kick_left","malcolm/malcolm_kick_left.bmp",1050,159,5,0.2f);
	CLIPMANAGER->AddClip("malcolm_kick_right","malcolm/malcolm_kick_right.bmp",1050,159,5,0.2f);
	CLIPMANAGER->AddClip("malcolm_block_left","malcolm/malcolm_block_left.bmp",214,154,2,0.2f);
	CLIPMANAGER->AddClip("malcolm_block_right","malcolm/malcolm_block_right.bmp",214,154,2,0.2f);
	CLIPMANAGER->AddClip("malcolm_hit_left","malcolm/malcolm_hit_left.bmp",576,158,4,0.2f);
	CLIPMANAGER->AddClip("malcolm_hit_right","malcom/malcolm_hit_right.bmp",576,158,4,0.2f);

	 /*william*/
	 CLIPMANAGER->AddClip("william_idle_left","william/william_idle_left.bmp",488,146,4,0.3f);
	 CLIPMANAGER->AddClip("william_idle_right","william/william_idle_right.bmp",488,146,4,0.3f);
	 CLIPMANAGER->AddClip("william_move_left","william/william_move_left.bmp",1160,144,8,0.3f);
	 CLIPMANAGER->AddClip("william_move_right","william/william_move_right.bmp",1160,144,8,0.3f);
	 CLIPMANAGER->AddClip("william_attack_left","william/william_attack_left.bmp",2024,138,11,0.2f);
	 CLIPMANAGER->AddClip("william_attack_right","william/william_attack_right.bmp",2024,138,11,0.2f);
	 CLIPMANAGER->AddClip("william_belly_left","william/william_belly_left.bmp",952,134,7,0.2f);
	 CLIPMANAGER->AddClip("william_belly_right", "william/william_belly_right.bmp", 952, 134, 7, 0.2f);
	 CLIPMANAGER->AddClip("william_block_left", "william/william_block_left.bmp", 198,131,2,0.2f);
	 CLIPMANAGER->AddClip("william_block_right", "william/william_block_right.bmp", 198, 131, 2, 0.2f);
	 CLIPMANAGER->AddClip("william_hit_left", "william/william_hit_left.bmp", 429, 148, 4, 0.3f);
	 CLIPMANAGER->AddClip("william_hit_right", "william/william_hit_right.bmp", 429, 148, 4, 0.3f);

	// 210627 시영 추가 (Enemy Update)

    enemy = new Luke();
	enemy->transform->SetPosition(1200, 300);

    enemy = new Luke();
	enemy->transform->SetPosition(800, 300);
	enemy->ground->enable = false;
	enemy->enemyAI->SetPlayer(character);
	enemy->zOrder->SetZ(enemy->transform->GetY() + 132 / 2);
	enemy->enemyinfo->SetSpeed(30.f);
    
	// 210628 광철 도베르만 개선 //
	doberman = new Doberman();
    doberman->transform->SetPosition(1200, 400);
	doberman->ground->enable = false;
	doberman->enemyAI->SetPlayer(character);
	doberman->zOrder->SetZ(enemy->transform->GetX() + 132 / 2);
	doberman->enemyinfo->SetSpeed(60.0f);
	
	// 210629 광철 말콤 구현//
	malcolm = new Malcolm();
	malcolm->transform->SetPosition(1300, 500);
	malcolm->ground->enable = false;
	malcolm->enemyAI->SetPlayer(character);
	malcolm->zOrder->SetZ(enemy->transform->GetX() + 132 / 2);
	malcolm->enemyinfo->SetSpeed(30.0f);
	
	// 210629 광철 윌리엄 구현//
	william = new William();
	william->transform->SetPosition(1500, 500);
	william->ground->enable = false;
	william->enemyAI->SetPlayer(character);
	william->zOrder->SetZ(enemy->transform->GetX() + 132 / 2);
	william->enemyinfo->SetSpeed(20.0f);
	
	// 보스 매튜 구현//
	matthew = new Character();
	matthew->Init();
	matthew->transform->SetPosition(2000, 400);
	matthew->collider->isTrigger = true;
	matthew->zOrder->SetZ(matthew->transform->GetX()+132/2);
	matthew->AddComponent(new Matthew());
	matthew->GetComponent<Matthew>()->Init();
	matthew->GetComponent<Matthew>()->SetPlayer(character);
	
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

	// 210627 시영 추가 (Enemy Update)
	enemy = new Luke();
	enemy->Init();
	enemy->transform->SetPosition(800, 300);
	enemy->ground->enable = false;
	enemy->enemyAI->SetPlayer(character);

	character->GetComponent<Player>()->SetEnemy(enemy);

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
	matthew->Update();
	

    // 210627 시영 추가 (Enemy Update)
    enemy->Update();
	doberman->Update();
	malcolm->Update();
	william->Update();

    // 210627 시영 추가 (Enemy Update)
    //enemy->Update();
	/*matthew->Update();
	doberman->Update();*/

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
	//matthew->Render();
	//doberman->Render();
    EFFECTMANAGER->Render();

    // 210627 시영 추가 (Enemy Render)
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
