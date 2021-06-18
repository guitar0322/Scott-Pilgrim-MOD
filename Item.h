#pragma once
#include "GameObject.h"
class Item :
    public Component
{
public:
    int enterNum;
    int stayNum;
    int exitNum;
    virtual void Init();
    virtual void Update();
    virtual void Render();
    virtual void OnCollision(GameObject* gameObject);//물리충돌 발생할때 호출
    virtual void OnTriggerEnter(GameObject* gameObject);//오브젝트의 박스콜라이더가 겹쳐짐이 시작될때 호출
    virtual void OnTriggerStay(GameObject* gameObject);//오브젝트의 박스콜라이더가 겹쳐짐이 지속될때 호출
    virtual void OnTriggerExit(GameObject* gameObject);//오브젝트의 박스콜라이더가 겹쳐짐이 끝날때 호출
};

