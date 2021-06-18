#include "stdafx.h"
#include "ZOrder.h"

void ZOrder::Init()
{
	_y = transform->GetY();
	ZORDER->AddZOrder(this);
}

void ZOrder::OnEnable()
{
	ZORDER->AddZOrder(this); //오브젝트가 켜질때 매니저에 추가
}

void ZOrder::OnDisable()
{
	ZORDER->EraseZOrder(this); //오브젝트가 꺼지면 매니저에서 제거
}
