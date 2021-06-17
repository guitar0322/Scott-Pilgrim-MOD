#include "stdafx.h"
#include "AutoMove.h"
#include "TestComponent.h"
void AutoMove::Init()
{
}

void AutoMove::Update()
{
	//transform->MoveX(1);
	//pointerObj->MoveX(-1);
	pointerObj->GetComponent<TestComponent>()->Init();
}

void AutoMove::Render()
{
}
