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
	float _itemZ;							//item의 z값


public:
    int enterNum;
    int exitNum;
	
	bool _leftThrowItem;					//왼쪽으로 아이템을 던졌을때
	bool _rightThrowItem;					//오른쪽으로 아이템을 던졌을떄

	bool _ItemRangeOutLeftCameraX;			//아이템이 카메라의 left X좌표를 벗어났을때
	bool _ItemRangeOutRightCameraX;			//아이템이 카메라의 right X 좌표를 벗어났을때
    
	virtual void Init();
    virtual void Update();
    virtual void Render();

	virtual void SetItemImage(string imageName);
    
	virtual void OnCollision(GameObject* gameObject);					//물리충돌 발생할때 호출
    virtual void OnTriggerEnter(GameObject* gameObject);				//오브젝트의 박스콜라이더가 겹쳐짐이 시작될때 호출
    virtual void OnTriggerExit(GameObject* gameObject);					//오브젝트의 박스콜라이더가 겹쳐짐이 끝날때 호출

	virtual void ItemLeftMove();										//왼쪽으로 이동하는 아이템 move값
	virtual void ItemRightMove();										//오른쪽으로 이동하는 아이템 move값

	virtual void ItemRangeOutLeftMove();								//아이템이 카메라 범위 초과시 "left로 이동
	virtual void ItemRangeOutRightMove();								//아이템이 카메라 범위 초과시 "rgiht"로 이동

};

