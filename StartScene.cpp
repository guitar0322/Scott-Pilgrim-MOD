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
    _mapWidth = 21206;
    _mapHeight = 680;
    mainCam = new Cam();
    mainCam->camera->SetMapSize(_mapWidth, _mapHeight);
    mainCam->transform->SetPosition(WINSIZEX / 2, 568 / 2);
    mainCam->camera->SetRenderHeight(568);
    CLIPMANAGER->AddClip("test_effect", "trap_blast_projectile.bmp", 168, 50, 4, 1.f);
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
    character = new Character();
    character->name = "character";
	character->AddComponent(new Player);
	character->GetComponent<Player>()->Init();
	character->ground->Init(100, 5, 0, 52);
	character->zOrder->Init();
	character->zOrder->SetY(568 / 2 + 52);

    wall[0] = new WallObj();
    wall[0]->Init(0, 300, 1000, 300);

    wall[1] = new WallObj();
    wall[1]->Init(0, WINSIZEY, 1000, WINSIZEY);

    wall[2] = new WallObj();
    wall[2]->Init(800, 200, 1000, 300);

    testGround = new GameObject();
    testGround->AddComponent(new Ground());
    testGround->GetComponent<Ground>()->Init();
    testGround->transform->SetPosition(500, 600);
    testGround->GetComponent<Ground>()->SetX(500);
    testGround->GetComponent<Ground>()->SetY(600);
    BackgroundInit();
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
    mainCam->transform->SetPosition(character->transform->GetX(), mainCam->transform->GetY());
    testGround->Update();
    character->Update();
    BGMANAGER->Update();
    EFFECTMANAGER->Update();
    ZORDER->Update();
    mainCam->Update();
}

void StartScene::Render()
{
    BGMANAGER->Render();
    ZORDER->Render();
    for (int i = 0; i < WALL_NUM; i++) {
		wall[i]->Render();
    }
    testGround->Render();
    EFFECTMANAGER->Render();
    sprintf_s(debug[0], "Player X : %f ", character->transform->GetX());
    sprintf_s(debug[1], "FPS : %d ", TIMEMANAGER->getFPS());
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 20, debug[0], strlen(debug[0]));
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 40, debug[1], strlen(debug[1]));
    TextOut(_backBuffer->getMemDC(), mainCam->transform->GetX() - 300, 60, debug[2], strlen(debug[2]));
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
    BGMANAGER->SetPlayer(character);
}
