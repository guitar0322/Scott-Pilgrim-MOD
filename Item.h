#pragma once
#include "Component.h"

class Item :
    public Component
{
private:
	Animator* _animator;
	ZOrder* _zorder;

	float _itemSpeed;						//아이템의 속도
	float _gravity;							//중력
	float _angle;							//각도

	float _friction;						//마찰력
	float _dashSpeed;						//이동이 끝난 후 속도

	float _speedX;
	float _speedY;

	bool _dir;								//방향값 false가 right   /// true가 left
	bool _onGround;							//땅에 착지 했나?

public:
	
	float itemZ;							//item의 z값
	
	bool throwDir;							//던졌을때 방향 설정해주기 위한 bool값
	
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
   
	void Throw(bool dir);					//던졌을때 방향 설정 함수
};

