#include "stdafx.h"
#include "Item.h"

void Item::Init()
{
	_animator = gameObject->GetComponent<Animator>();
	enterNum = 0;
	stayNum = 0;
	exitNum = 0;
}

void Item::Update()
{
	sprintf_s(debug[0], "%d", enterNum);
	sprintf_s(debug[1], "%d", stayNum);
	sprintf_s(debug[2], "%d", exitNum);
}

void Item::Render()
{
}

void Item::SetItemImage(string imageName)
{
	_animator->AddClip(imageName, CLIPMANAGER->FindClip(imageName));
	_animator->SetClip(imageName);
}

void Item::OnCollision(GameObject* gameObject)
{
	enterNum++;
}

void Item::OnTriggerEnter(GameObject* gameObject)
{
	enterNum++;
	//if(gameObject->tag == TAGMANAGER->GetTag("player"))
	//	this->gameObject->SetActive(false);
}

void Item::OnTriggerStay(GameObject* gameObject)
{
	stayNum++;
}

void Item::OnTriggerExit(GameObject* gameObject)
{
	exitNum++;
}

