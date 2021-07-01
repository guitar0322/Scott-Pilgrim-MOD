#include "stdafx.h"
#include "Player.h"
#include "PlayerIdleState.h"

void Player::InputHandle()
{
	PlayerState* newState = _state->InputHandle(this);
	if (newState != nullptr)
	{
		_state->Exit(this);
		SAFE_DELETE(_state);
		_state = newState;
		_state->Enter(this);
	}
}

void Player::Init()
{
	animator = gameObject->GetComponent<Animator>();
	collider = gameObject->GetComponent<BoxCollider>();
	ground = gameObject->GetComponent<Ground>();
	zOrder = gameObject->GetComponent<ZOrder>();

	ClipInit();
	_speed = 48;							//�÷��̾� �ӵ�
	_gravity = 200;							//�÷��̾� �߷� (���� �� �߷°�)
	friction = 130;							//�÷��̾� ���� (���ٰ� �̲����� ��)
	jumpPower = 200;						//�÷��̾� ������

	dir = false;							//�¿� Ȯ�� ��
	dirZ = false;							//Z�� Ȯ�ο�
	isRun = false;							//�÷��̾ �ٴ� �� ����
	runKeyPress = false;					//�ٴ� Ű�� ������ �� ����
	jumpZ = false;							//Z�� ���� Ȯ�ο�
	block = false;							//���� Ȯ�ο�
	isZJump = false;						//Z�� ���� �� �÷��̾� �׶��� ���� Ȯ�ο�
	onGround = false;

	isPick = false;							//�������� �־����� ����
	isCatch = false;						//�������� ��Ҵ��� ����

	_state = new PlayerIdleState();			//Idle ���·� �ʱ�ȭ
	_state->Enter(this);
	runDelay = 0;
	jumpDelay = 0;
	pickDelay = 0;

	hp = 100;
	attack = 10;
	isUppercut = false;
	pressL = false;

}

void Player::Update()
{
	InputHandle();
	groundCheckRc = RectMakeCenter(transform->GetX(), transform->GetY() + collider->height / 2 + 5,
		collider->width, 10);
	_state->Update(this);
	if (runKeyPress == true)
		runDelay += TIMEMANAGER->getElapsedTime();
	if (jumpZ == true)
		jumpDelay += TIMEMANAGER->getElapsedTime();

	if (isPick == true)
	{
		pickDelay += TIMEMANAGER->getElapsedTime();
		if (pickDelay >= 0.3f)
		{
			if (!dir)
			{
				item->transform->SetPosition(transform->GetX() - 14, transform->GetY() - 77);
			}
			if (dir)
			{
				item->transform->SetPosition(transform->GetX() + 14, transform->GetY() - 77);
			}
			pickDelay = 0;
			isPick = false;
		}
	}
}

void Player::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB)) 
	{
		HPEN hPen, oPen;
		HBRUSH hBrush, oBrush;

		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		oBrush = (HBRUSH)SelectObject(BackBuffer, hBrush);
		hPen = CreatePen(PS_DOT, 1, RGB(255, 255, 255));
		oPen = (HPEN)SelectObject(BackBuffer, hPen);
		Rectangle(BackBuffer, groundCheckRc);
		SelectObject(BackBuffer, oPen);
		SelectObject(BackBuffer, oBrush);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
}

void Player::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == false)
	{
		animator->SetClip(animator->GetClip(clipName), animator->currentFrame);
	}
	else
	{
		animator->SetClip(animator->GetClip(clipName));
	}
}

void Player::ClipInit()
{
	idleRight.Init("player/idle_right.bmp", 640, 122, 8, 0.20f);
	idleLeft.Init("player/idle_left.bmp", 640, 122, 8, 0.20f);
	walkRight.Init("player/walk_right.bmp", 456, 128, 6, 0.25f);
	walkLeft.Init("player/walk_left.bmp", 456, 128, 6, 0.25f);
	runRight.Init("player/run_right.bmp", 864, 126, 8, 0.17f);
	runLeft.Init("player/run_left.bmp", 864, 126, 8, 0.17f);
	jumpRight.Init("player/jump_right.bmp", 686, 144, 7, 0.15f);
	jumpRight.isLoop = false;
	jumpLeft.Init("player/jump_left.bmp", 686, 144, 7, 0.15f);
	jumpLeft.isLoop = false;
	fallRight.Init("player/fall_right.bmp", 490, 144, 5, 0.15f);
	fallRight.isLoop = false;
	fallLeft.Init("player/fall_left.bmp", 490, 144, 5, 0.15f);
	fallLeft.isLoop = false;
	jumpZorderRight.Init("player/jump_Zorder_right.bmp", 882, 144, 9, 0.08f);
	jumpZorderRight.isLoop = false;
	jumpZorderLeft.Init("player/jump_Zorder_left.bmp", 882, 144, 9, 0.08f);
	jumpZorderLeft.isLoop = false;
	groundRight.Init("player/ground_right.bmp", 98, 144, 1, 0.10f);
	groundRight.isLoop = false;
	groundLeft.Init("player/ground_left.bmp", 98, 144, 1, 0.10f);
	groundLeft.isLoop = false;

	shieldRight.Init("player/block_right.bmp", 532, 126, 7, 0.22f);
	shieldRight.isLoop = false;
	shieldLeft.Init("player/block_left.bmp", 532, 126, 7, 0.22f);
	shieldLeft.isLoop = false;

	kickAttackRight.Init("player/kick_attack_right.bmp", 896, 126, 7, 0.15f);
	kickAttackRight.isLoop = false;
	kickAttackLeft.Init("player/kick_attack_left.bmp", 896, 126, 7, 0.15f);
	kickAttackLeft.isLoop = false;
	kickSkillRight.Init("player/kick_skill_right.bmp", 7958, 152, 23, 0.1f);
	kickSkillRight.isLoop = false;
	kickSkillLeft.Init("player/kick_skill_left.bmp", 7958, 152, 23, 0.1f);
	kickSkillLeft.isLoop = false;

	walkJumpKickRight.Init("player/walk_jump_kick_right.bmp", 980, 106, 7, 0.1f);
	walkJumpKickRight.isLoop = false;
	walkJumpKickLeft.Init("player/walk_jump_kick_left.bmp", 980, 106, 7, 0.1f);
	walkJumpKickLeft.isLoop = false;
	runJumpKickRight.Init("player/run_jump_kick_right.bmp", 1036, 102, 7, 0.15f);
	runJumpKickRight.isLoop = false;
	runJumpKickLeft.Init("player/run_jump_kick_left.bmp", 1036, 102, 7, 0.15f);
	runJumpKickLeft.isLoop = false;
	//���� �̹���
	attack1Right.Init("player/attack1_right.bmp", 480, 118, 3, 0.1f);
	attack2Right.Init("player/attack2_right.bmp", 640, 118, 4, 0.1f);
	attack3Right.Init("player/attack3_right.bmp", 366, 130, 3, 0.15f);
	attack4Right.Init("player/attack4_right.bmp", 864, 166, 8, 0.15f);

	attack1Right.isLoop = false;
	attack2Right.isLoop = false;
	attack3Right.isLoop = false;
	attack4Right.isLoop = false;

	attack1Left.Init("player/attack1_left.bmp", 480, 118, 3, 0.1f);
	attack2Left.Init("player/attack2_left.bmp", 640, 118, 4, 0.1f);
	attack3Left.Init("player/attack3_left.bmp", 366, 130, 3, 0.15f);
	attack4Left.Init("player/attack4_left.bmp", 864, 166, 8, 0.15f);

	attack1Left.isLoop = false;
	attack2Left.isLoop = false;
	attack3Left.isLoop = false;
	attack4Left.isLoop = false;


	//�μ� �̹���
	twoHandPickRight.Init("player/two_hand_pick_right.bmp", 192, 130, 2, 0.20f);
	twoHandPickRight.isLoop = false;
	twoHandPickLeft.Init("player/two_hand_pick_left.bmp", 192, 130, 2, 0.20f);
	twoHandPickLeft.isLoop = false;
	twoHandIdleRight.Init("player/two_hand_idle_right.bmp", 312, 120, 4, 0.20f);
	twoHandIdleLeft.Init("player/two_hand_idle_left.bmp", 312, 120, 4, 0.20f);
	twoHandWalkRight.Init("player/two_hand_walk_right.bmp", 468, 130, 6, 0.25f);
	twoHandWalkLeft.Init("player/two_hand_walk_left.bmp", 468, 130, 6, 0.25f);
	twoHandRunRight.Init("player/two_hand_run_right.bmp", 944, 120, 8, 0.17f);
	twoHandRunLeft.Init("player/two_hand_run_left.bmp", 944, 120, 8, 0.17f);
	twoHandJumpRight.Init("player/two_hand_jump_right.bmp", 658, 146, 7, 0.15f);
	twoHandJumpRight.isLoop = false;
	twoHandJumpLeft.Init("player/two_hand_jump_left.bmp", 658, 146, 7, 0.15f);
	twoHandJumpLeft.isLoop = false;
	twoHandFallRight.Init("player/two_hand_fall_right.bmp", 470, 146, 5, 0.15f);
	twoHandFallRight.isLoop = false;
	twoHandFallLeft.Init("player/two_hand_fall_left.bmp", 470, 146, 5, 0.15f);
	twoHandFallLeft.isLoop = false;
	twoHandGroundRight.Init("player/two_hand_ground_right.bmp", 94, 146, 1, 0.10f);
	twoHandGroundRight.isLoop = false;
	twoHandGroundLeft.Init("player/two_hand_ground_left.bmp", 94, 146, 1, 0.10f);
	twoHandGroundLeft.isLoop = false;
	twoHandZorderRight.Init("player/two_hand_Zorder_right.bmp", 768, 146, 8, 0.08f);
	twoHandZorderRight.isLoop = false;
	twoHandZorderLeft.Init("player/two_hand_Zorder_left.bmp", 768, 146, 8, 0.08f);
	twoHandZorderLeft.isLoop = false;

	twoHandWalkAttackRight.Init("player/two_hand_walk_attack_right.bmp", 938, 126, 7, 0.2f);
	twoHandWalkAttackRight.isLoop = false;
	twoHandWalkAttackLeft.Init("player/two_hand_walk_attack_left.bmp", 938, 126, 7, 0.2f);
	twoHandWalkAttackLeft.isLoop = false;
	twoHandRunAttackRight.Init("player/two_hand_run_attack_right.bmp", 756, 138, 6, 0.15f);
	twoHandRunAttackRight.isLoop = false;
	twoHandRunAttackLeft.Init("player/two_hand_run_attack_left.bmp", 756, 138, 6, 0.15f);
	twoHandRunAttackLeft.isLoop = false;



	animator->AddClip("idle_right", &idleRight);
	animator->AddClip("idle_left", &idleLeft);
	animator->AddClip("walk_right", &walkRight);
	animator->AddClip("walk_left", &walkLeft);
	animator->AddClip("run_right", &runRight);
	animator->AddClip("run_left", &runLeft);
	animator->AddClip("jump_right", &jumpRight);
	animator->AddClip("jump_left", &jumpLeft);
	animator->AddClip("fall_right", &fallRight);
	animator->AddClip("fall_left", &fallLeft);
	animator->AddClip("jump_Zorder_right", &jumpZorderRight);
	animator->AddClip("jump_Zorder_left", &jumpZorderLeft);
	animator->AddClip("ground_right", &groundRight);
	animator->AddClip("ground_left", &groundLeft);

	animator->AddClip("block_right", &shieldRight);
	animator->AddClip("block_left", &shieldLeft);

	animator->AddClip("kick_attack_right", &kickAttackRight);
	animator->AddClip("kick_attack_left", &kickAttackLeft);
	animator->AddClip("kick_skill_right", &kickSkillRight);
	animator->AddClip("kick_skill_left", &kickSkillLeft);
	animator->AddClip("walk_jump_kick_right", &walkJumpKickRight);
	animator->AddClip("walk_jump_kick_left", &walkJumpKickLeft);
	animator->AddClip("run_jump_kick_right", &runJumpKickRight);
	animator->AddClip("run_jump_kick_left", &runJumpKickLeft);

	animator->AddClip("attack1_right", &attack1Right);
	animator->AddClip("attack2_right", &attack2Right);
	animator->AddClip("attack3_right", &attack3Right);
	animator->AddClip("attack4_right", &attack4Right);
	animator->AddClip("attack1_left", &attack1Left);
	animator->AddClip("attack2_left", &attack2Left);
	animator->AddClip("attack3_left", &attack3Left);
	animator->AddClip("attack4_left", &attack4Left);

	//�μ� �̹���

	animator->AddClip("two_hand_idle_right", &twoHandIdleRight);
	animator->AddClip("two_hand_idle_left", &twoHandIdleLeft);
	animator->AddClip("two_hand_pick_right", &twoHandPickRight);
	animator->AddClip("two_hand_pick_left", &twoHandPickLeft);
	animator->AddClip("two_hand_walk_right", &twoHandWalkRight);
	animator->AddClip("two_hand_walk_left", &twoHandWalkLeft);
	animator->AddClip("two_hand_run_right", &twoHandRunRight);
	animator->AddClip("two_hand_run_left", &twoHandRunLeft);
	animator->AddClip("two_hand_jump_right", &twoHandJumpRight);
	animator->AddClip("two_hand_jump_left", &twoHandJumpLeft);
	animator->AddClip("two_hand_fall_right", &twoHandFallRight);
	animator->AddClip("two_hand_fall_left", &twoHandFallLeft);
	animator->AddClip("two_hand_ground_right", &twoHandGroundRight);
	animator->AddClip("two_hand_ground_left", &twoHandGroundLeft);
	animator->AddClip("two_hand_Zorder_right", &twoHandZorderRight);
	animator->AddClip("two_hand_Zorder_left", &twoHandZorderLeft);
	animator->AddClip("two_hand_walk_attack_right", &twoHandWalkAttackRight);
	animator->AddClip("two_hand_walk_attack_left", &twoHandWalkAttackLeft);
	animator->AddClip("two_hand_run_attack_right", &twoHandRunAttackRight);
	animator->AddClip("two_hand_run_attack_left", &twoHandRunAttackLeft);

	animator->AddTransaction("pickup_to_pickup_idle_right", &twoHandPickRight, &twoHandIdleRight);
	animator->AddTransaction("pickup_to_pickup_idle_left", &twoHandPickLeft, &twoHandIdleLeft);
}

void Player::OnTriggerEnter(GameObject * gameObject)
{
	item = gameObject->GetComponent<Item>();
}

void Player::OnTriggerExit(GameObject * gameObject)
{
	item = nullptr;
}

void Player::PickItem()								// item ȹ�� ������
{
	if (transform->GetChildCount() == 0)		//player�� �ڽ��� ������
	{
		transform->AddChild(item->transform);	//player�� item�� �ڽ����� ������
		isCatch = true;							//item�� ������ �ִ� ���°� �ȴ�
		equipItem = item->gameObject;
	}
}


void Player::PutItem()															//item�� ��������
{
	if (equipItem != nullptr)													//item�� ���� ������ ������
	{
		equipItem->transform->DetachParent();									//item�� �θ� �Ҵ´�
		equipItem->GetComponent<Item>()->SetItemZ(this->zOrder->GetZ());		//�������� itemz�� player�� z���� ������
		equipItem->GetComponent<Item>()->Throw(dir);							//dir�� ���� throw	
		equipItem = nullptr;													
	}	
	isCatch = false;															//item�� ���� �����̰�
	item = nullptr;																//item�� ���� �Ҵ´�	
}

void Player::Hit(int damage)
{
	hp -= damage;
	if (hp <= 0)
	{
		gameObject->SetActive(false);
		// TODO - DEAD
	}
}
