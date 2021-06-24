#include "stdafx.h"
#include "ClearTrigger.h"

ClearTrigger::ClearTrigger()
{
}

ClearTrigger::~ClearTrigger()
{
}

void ClearTrigger::Init(RockMan* rockman)
{
	this->rockman = rockman;
}

void ClearTrigger::Update()
{
}

void ClearTrigger::Render()
{
}

void ClearTrigger::OnTriggerEnter(GameObject* gameObject)
{
	if (gameObject->tag == TAGMANAGER->GetTag("player")) {
		rockman->animator->SetClip(rockman->animator->GetClip("intro"));
		this->gameObject->SetActive(false);
	}
}
