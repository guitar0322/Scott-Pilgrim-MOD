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

    // 210629 시영 추가
    EnemyClipManager();

	// 210627 시영 추가 (Enemy Update)
    enemy = new Luke();
	enemy->transform->SetPosition(800, 300);
	enemy->ground->enable = false;
	enemy->enemyAI->SetPlayer(character);
	enemy->zOrder->SetZ(enemy->transform->GetY() + 132 / 2);
	enemy->enemyinfo->SetSpeed(30.f);

	doberman = new Doberman();
 	// 210628 광철 도베르만 개선 //
    doberman->transform->SetPosition(1200, 400);    
    doberman->ground->enable = false;
    doberman->enemyAI->SetPlayer(character);
    doberman->zOrder->SetZ(enemy->transform->GetX() + 132 / 2);
    doberman->enemyinfo->SetSpeed(100.f);

    // 보스 매튜 구현//    
    matthew = new Character();
    matthew->Init();
    matthew->transform->SetPosition(2000, 400);
    matthew->collider->isTrigger = true;
    matthew->AddComponent(new Matthew());
    matthew->GetComponent<Matthew>()->Init();
    matthew->GetComponent<Matthew>()->SetPlayer(character);

    BackgroundInit();
    WallInit();

    return S_OK;
}

void StartScene::Release()
{

}

void StartScene::Update()
{
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
	doberman->Update();
	matthew->Update();
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

void StartScene::EnemyClipManager()
{
    /*
        CLIP MANAGER (ORDER - JESSE, LEE, LUKE, MIKE, RICHARD) by. 시영
    */

    /* JESSE CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("jesse_idle_right", "jesse/jesse_idle_right.bmp", 344, 132, 4, 0.20f);
    CLIPMANAGER->AddClip("jesse_idle_left", "jesse/jesse_idle_left.bmp", 344, 132, 4, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("jesse_walk_right", "jesse/jesse_walk_right.bmp", 468, 138, 6, 0.20f);
    CLIPMANAGER->AddClip("jesse_walk_left", "jesse/jesse_walk_left.bmp", 468, 138, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("jesse_run_right", "jesse/jesse_run_right.bmp", 928, 134, 8, 0.20f);
    CLIPMANAGER->AddClip("jesse_run_left", "jesse/jesse_run_left.bmp", 928, 134, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("jesse_block_right", "jesse/jesse_block_right.bmp", 276, 136, 3, 0.20f);
    CLIPMANAGER->AddClip("jesse_block_left", "jesse/jesse_block_left.bmp", 276, 136, 3, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("jesse_hit_right", "jesse/jesse_hit_right.bmp", 470, 128, 5, 0.20f);
    CLIPMANAGER->AddClip("jesse_hit_left", "jesse/jesse_hit_left.bmp", 470, 128, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("jesse_kick_right", "jesse/jesse_kick_right.bmp", 1092, 116, 7, 0.20f);
    CLIPMANAGER->AddClip("jesse_kick_left", "jesse/jesse_kick_left.bmp", 1092, 116, 7, 0.20f);
    // ATTACK
    CLIPMANAGER->AddClip("jesse_attack_right", "jesse/jesse_attack_right.bmp", 924, 126, 7, 0.20f);
    CLIPMANAGER->AddClip("jesse_attack_left", "jesse/jesse_attack_left.bmp", 924, 126, 7, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("jesse_die_right", "jesse/jesse_die_right.bmp", 1680, 114, 12, 0.20f);
    CLIPMANAGER->AddClip("jesse_die_left", "jesse/jesse_die_left.bmp", 1680, 114, 12, 0.20f);

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

    /* LUKE CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("luke_idle_right", "luke/luke_idle_right.bmp", 800, 128, 8, 0.20f);
    CLIPMANAGER->AddClip("luke_idle_left", "luke/luke_idle_left.bmp", 800, 128, 8, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("luke_walk_right", "luke/luke_walk_right.bmp", 564, 136, 6, 0.20f);
    CLIPMANAGER->AddClip("luke_walk_left", "luke/luke_walk_left.bmp", 564, 136, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("luke_run_right", "luke/luke_run_right.bmp", 880, 130, 8, 0.20f);
    CLIPMANAGER->AddClip("luke_run_left", "luke/luke_run_left.bmp", 880, 130, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("luke_block_right", "luke/luke_block_right.bmp", 264, 128, 3, 0.20f);
    CLIPMANAGER->AddClip("luke_block_left", "luke/luke_block_left.bmp", 264, 128, 3, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("luke_hit_right", "luke/luke_hit_right.bmp", 600, 130, 5, 0.20f);
    CLIPMANAGER->AddClip("luke_hit_left", "luke/luke_hit_left.bmp", 600, 130, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("luke_kick_right", "luke/luke_kick_right.bmp", 1050, 134, 7, 0.20f);
    CLIPMANAGER->AddClip("luke_kick_left", "luke/luke_kick_left.bmp", 1050, 134, 7, 0.20f);
    // ATTACK 1
    CLIPMANAGER->AddClip("luke_attack1_right", "luke/luke_attack1_right.bmp", 560, 134, 4, 0.20f);
    CLIPMANAGER->AddClip("luke_attack1_left", "luke/luke_attack1_left.bmp", 560, 134, 4, 0.20f);
    // ATTACK 2
    CLIPMANAGER->AddClip("luke_attack2_right", "luke/luke_attack2_right.bmp", 568, 132, 4, 0.20f);
    CLIPMANAGER->AddClip("luke_attack2_left", "luke/luke_attack2_left.bmp", 568, 132, 4, 0.20f);
    // ATTACK 3
    CLIPMANAGER->AddClip("luke_attack3_right", "luke/luke_attack3_right.bmp", 832, 170, 8, 0.20f);
    CLIPMANAGER->AddClip("luke_attack3_left", "luke/luke_attack3_left.bmp", 832, 170, 8, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("luke_die_right", "luke/luke_die_right.bmp", 2100, 172, 14, 0.20f);
    CLIPMANAGER->AddClip("luke_die_left", "luke/luke_die_left.bmp", 2100, 172, 14, 0.20f);

    /* MIKE CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("mike_idle_right", "mike/mike_idle_right.bmp", 798, 134, 8, 0.20f);
    CLIPMANAGER->AddClip("mike_idle_left", "mike/mike_idle_left.bmp", 798, 134, 8, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("mike_walk_right", "mike/mike_walk_right.bmp", 564, 134, 6, 0.20f);
    CLIPMANAGER->AddClip("mike_walk_left", "mike/mike_walk_left.bmp", 564, 134, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("mike_run_right", "mike/mike_run_right.bmp", 880, 146, 8, 0.20f);
    CLIPMANAGER->AddClip("mike_run_left", "mike/mike_run_left.bmp", 880, 146, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("mike_block_right", "mike/mike_block_right.bmp", 282, 124, 3, 0.20f);
    CLIPMANAGER->AddClip("mike_block_left", "mike/mike_block_left.bmp", 282, 124, 3, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("mike_hit_right", "mike/mike_hit_right.bmp", 550, 126, 5, 0.20f);
    CLIPMANAGER->AddClip("mike_hit_left", "mike/mike_hit_left.bmp", 550, 126, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("mike_kick_right", "mike/mike_kick_right.bmp", 1064, 130, 7, 0.20f);
    CLIPMANAGER->AddClip("mike_kick_left", "mike/mike_kick_left.bmp", 1064, 130, 7, 0.20f);
    // ATTACK 1
    CLIPMANAGER->AddClip("mike_attack1_right", "mike/mike_attack1_right.bmp", 560, 124, 4, 0.20f);
    CLIPMANAGER->AddClip("mike_attack1_left", "mike/mike_attack1_left.bmp", 560, 124, 4, 0.20f);
    // ATTACK 2
    CLIPMANAGER->AddClip("mike_attack2_right", "mike/mike_attack2_right.bmp", 560, 136, 4, 0.20f);
    CLIPMANAGER->AddClip("mike_attack2_left", "mike/mike_attack2_left.bmp", 560, 136, 4, 0.20f);
    // ATTACK 3
    CLIPMANAGER->AddClip("mike_attack3_right", "mike/mike_attack3_right.bmp", 816, 170, 8, 0.20f);
    CLIPMANAGER->AddClip("mike_attack3_left", "mike/mike_attack3_left.bmp", 816, 170, 8, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("mike_die_right", "mike/mike_die_right.bmp", 2352, 172, 14, 0.20f);
    CLIPMANAGER->AddClip("mike_die_left", "mike/mike_die_left.bmp", 2352, 172, 14, 0.20f);

    /* RICHARD CLIP MANAGER */
    // IDLE
    CLIPMANAGER->AddClip("richard_idle_right", "richard/richard_idle_right.bmp", 800, 132, 8, 0.20f);
    CLIPMANAGER->AddClip("richard_idle_left", "richard/richard_idle_left.bmp", 800, 132, 8, 0.20f);
    // WALK
    CLIPMANAGER->AddClip("richard_walk_right", "richard/richard_walk_right.bmp", 588, 136, 6, 0.20f);
    CLIPMANAGER->AddClip("richard_walk_left", "richard/richard_walk_left.bmp", 588, 136, 6, 0.20f);
    // RUN
    CLIPMANAGER->AddClip("richard_run_right", "richard/richard_run_right.bmp", 864, 148, 8, 0.20f);
    CLIPMANAGER->AddClip("richard_run_left", "richard/richard_run_left.bmp", 864, 148, 8, 0.20f);
    // BLOCK
    CLIPMANAGER->AddClip("richard_block_right", "richard/richard_block_right.bmp", 270, 132, 3, 0.20f);
    CLIPMANAGER->AddClip("richard_block_left", "richard/richard_block_left.bmp", 270, 132, 3, 0.20f);
    // HIT
    CLIPMANAGER->AddClip("richard_hit_right", "richard/richard_hit_right.bmp", 540, 132, 5, 0.20f);
    CLIPMANAGER->AddClip("richard_hit_left", "richard/richard_hit_left.bmp", 540, 132, 5, 0.20f);
    // KICK
    CLIPMANAGER->AddClip("richard_kick_right", "richard/richard_kick_right.bmp", 1036, 144, 7, 0.20f);
    CLIPMANAGER->AddClip("richard_kick_left", "richard/richard_kick_left.bmp", 1036, 144, 7, 0.20f);
    // ATTACK 1
    CLIPMANAGER->AddClip("richard_attack1_right", "richard/richard_attack1_right.bmp", 560, 130, 4, 0.20f);
    CLIPMANAGER->AddClip("richard_attack1_left", "richard/richard_attack1_left.bmp", 560, 130, 4, 0.20f);
    // ATTACK 2
    CLIPMANAGER->AddClip("richard_attack2_right", "richard/richard_attack2_right.bmp", 576, 138, 4, 0.20f);
    CLIPMANAGER->AddClip("richard_attack2_left", "richard/richard_attack2_left.bmp", 576, 138, 4, 0.20f);
    // ATTACK 3
    CLIPMANAGER->AddClip("richard_attack3_right", "richard/richard_attack3_right.bmp", 848, 166, 8, 0.20f);
    CLIPMANAGER->AddClip("richard_attack3_left", "richard/richard_attack3_left.bmp", 848, 166, 8, 0.20f);
    // DIE
    CLIPMANAGER->AddClip("richard_die_right", "richard/richard_die_right.bmp", 2072, 172, 14, 0.20f);
    CLIPMANAGER->AddClip("richard_die_left", "richard/richard_die_left.bmp", 2072, 172, 14, 0.20f);

    /*Doberman CLIP MANAGER*/
    CLIPMANAGER->AddClip("doberman_idle_left", "Doberman/idle_left.bmp", 656, 96, 4, 0.3f);
    CLIPMANAGER->AddClip("doberman_idle_right", "Doberman/idle_right.bmp", 656, 96, 4, 0.3f);
    CLIPMANAGER->AddClip("doberman_move_left", "Doberman/move_left.bmp", 1146, 96, 6, 0.2f);
    CLIPMANAGER->AddClip("doberman_move_right", "Doberman/move_right.bmp", 1146, 96, 6, 0.2f);
    //CLIPMANAGER->AddClip("runLeft", "Doberman/DogRunLeft.bmp", 1539, 96, 9, 0.1f));
    //CLIPMANAGER->AddClip("runRight", "Doberman/DogRunRight.bmp", 1539, 96, 9, 0.1f));
    CLIPMANAGER->AddClip("doberman_attack_left", "Doberman/attack_left.bmp", 1075, 96, 7, 0.2f);
    CLIPMANAGER->AddClip("doberman_attack_right", "Doberman/attack_right.bmp", 1075, 96, 7, 0.2f);
}
