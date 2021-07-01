#pragma once
#include "Component.h"
#include "EnemyInfo.h"

/* 상태패턴을 위한 전방선언 */
class EnemyState;

class EnemyAI : public Component
{
private:
	/* Enemy가 player를 찾기 위해 선언 */
	GameObject* _player;

	/* 디자인 패턴(상태패턴)용 */
	EnemyState* state;	

public:
	EnemyAI();
	~EnemyAI();

	Animator* animator;
	EnemyInfo* enemyinfo;
	ZOrder* zOrder;

	/* 210630 Patrol 관련 변수 & 함수 설정 */
	float deltaX;
	float deltaY;
	pair<float, float> patrolPoint;

	virtual void Init();
	virtual void Update();
	virtual void Render();

	void Hit(float damage);
	void Dead();
	/* 상태별 Clip 변경하기 위한 함수 */
	void ChangeClip(string clipName, bool isInitFrame);

	/* _player를 찾기 위한 GETTER/SETTER */
	void SetPlayer(GameObject* player) { _player = player; }
	void SetState(EnemyState* newState);
	Transform* GetPlayerTransform() const { return _player->transform; }

	/* 210629 상태를 지정하기 위한 SETTER */
//	void SetState(EnemyState* newState);

	/* 210630 private Player 가져오기 위한 함수 충돌(히트) */
	GameObject* GetPlayer() const { return _player; }
};