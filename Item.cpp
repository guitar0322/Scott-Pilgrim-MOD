#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	animator = gameObject->GetComponent<Animator>();
	_zorder = gameObject->GetComponent<ZOrder>();

	animator->AddClip("trashbox_left", CLIPMANAGER->FindClip("trashbox_left"));
	animator->AddClip("trashbox_walk_attack_right", CLIPMANAGER->FindClip("trashbox_walk_attack_right"));
	animator->AddClip("trashbox_walk_attack_left", CLIPMANAGER->FindClip("trashbox_walk_attack_left"));

	animator->AddClip("trashbox_walk_throw_right", CLIPMANAGER->FindClip("trashbox_walk_throw_right"));
	animator->AddClip("trashbox_walk_throw_left", CLIPMANAGER->FindClip("trashbox_walk_throw_left"));

	_itemSpeed = 320.f;		// �������� �ӵ�
	_gravity = 560.f;
	_friction = 60.f;		// ������
							//�� ������ ������ �ʱ⿡ init���� �� ��

	_angle = 0.f;			// ����
	_itemZ = 0.f;			// �÷��̾��� Z ���� �������� ���� ����
	
	_speedX = 0.f;			// ���ǵ�� �ޱ� ���� �̿��ϱ� ���� ����
	_speedY = 0.f;			// ��
	
	_isGround = true;		//�� ���� �ִ°�? �������� �� ó�� �� ���� �ֱ⿡ true
	itemAttack = false;
}

void Item::Update()
{
	if (itemAttack)
	{
		if (animator->currentFrame == 5)
		{
			ItemAttack();
		}
	}
	if (_speedX != 0)
	{
		ItemThrowAttack();
	}
	transform->MoveX(_speedX * TIMEMANAGER->getElapsedTime());
	
	if (_isGround == false)					//�� ���� ���� �ʴٸ�
	{
		transform->MoveY(_speedY * TIMEMANAGER->getElapsedTime());
		_speedY += _gravity * TIMEMANAGER->getElapsedTime();
	}

	if (_isGround == true)					//throw�ؼ� �� ���� ���� �Ѵٸ� ������ �ο�
	{
		if (_throwDir == false)				    //right�϶� ������
		{
			_speedX -= _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX <= 0) _speedX = 0;
		}

		if (_throwDir == true)				//left�϶� ������
		{
			_speedX += _friction * TIMEMANAGER->getElapsedTime();
			if (_speedX >= 0) _speedX = 0;
		}
	}
	//���� ���� ��
	if (transform->GetY() + gameObject->GetComponent<Renderer>()->GetHeight() / 2 >= _itemZ && _itemZ != 0)
	{
		_speedY = 0.0f;
		_isGround = true;
	}

	//item�� MainCam�� ���� �ʰ���
	if (MainCam->transform->GetX() - MainCam->GetRenderWidth() / 2 >= transform->GetX()
		|| MainCam->transform->GetX() + MainCam->GetRenderWidth() / 2 <= transform->GetX())
	{
		_speedX *= -1;					//���� �ʰ��� x ��ǥ ���� �ٲ���		
	}
}
void Item::Render()
{
}

void Item::SetItemImage(string imageName)
{
	animator->AddClip(imageName, CLIPMANAGER->FindClip(imageName));
	animator->SetClip(imageName);
}

void Item::ItemAttack()
{
	itemAttack = false;
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		if (_sectorEnemyV[i]->isActive == false) continue;

		float _distance = GetDistance(transform->GetX(), transform->gameObject->GetComponent<ZOrder>()->GetZ(),
			_sectorEnemyV[i]->transform->GetX(),
			_sectorEnemyV[i]->GetComponent<ZOrder>()->GetZ());

		if (_distance < 100) 
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(10);
			EFFECTMANAGER->EmissionEffect("attack_effect", transform->GetX(), transform->GetY());
		}
	}
}

void Item::ItemThrowAttack()
{
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		if (_isHitThrow[i] == true) continue;
		if (_sectorEnemyV[i]->isActive == false) continue;

		float _distance = GetDistance(transform->GetX(), transform->gameObject->GetComponent<ZOrder>()->GetZ(),
			_sectorEnemyV[i]->transform->GetX(),
			_sectorEnemyV[i]->GetComponent<ZOrder>()->GetZ());

		if (_distance < 100)
		{
			_sectorEnemyV[i]->GetComponent<EnemyAI>()->Hit(10);
			_isHitThrow[i] = true;
			EFFECTMANAGER->EmissionEffect("attack_effect", transform->GetX(), transform->GetY());
			_speedX *= -1;
		}
	}
}

void Item::Throw(bool dir)			//throw�� bool�� dir ��ȯ
{
	_throwDir = dir;	
	_isGround = false;
	vector<GameObject*> _sectorEnemyV = ENEMYMANAGER->GetSectorEnemy();
	_isHitThrow.clear();
	for (int i = 0; i < _sectorEnemyV.size(); i++)
	{
		_isHitThrow.push_back(false);
	}
	if (dir == false)				// right�϶�
	{
		_angle = 0;
	}
	if (dir == true)				// left�϶�
	{
		_angle = PI;
	}

	_speedX = cosf(_angle) * _itemSpeed;
	_speedY = -sinf(_angle) * _itemSpeed;
}

void Item::ChangeClip(string clipName, bool isInitFrame)
{
	if (isInitFrame == false)
	{
		animator->SetClip(animator->GetClip(clipName));
	}
	else
	{
		animator->SetClip(animator->GetClip(clipName), animator->currentFrame);
	}
}
