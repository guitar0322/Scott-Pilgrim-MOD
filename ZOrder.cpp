#include "stdafx.h"
#include "ZOrder.h"

void ZOrder::Init()
{
	_y = transform->GetY();
	ZORDER->AddZOrder(this);
}

void ZOrder::OnEnable()
{
	ZORDER->AddZOrder(this); //������Ʈ�� ������ �Ŵ����� �߰�
}

void ZOrder::OnDisable()
{
	ZORDER->EraseZOrder(this); //������Ʈ�� ������ �Ŵ������� ����
}
