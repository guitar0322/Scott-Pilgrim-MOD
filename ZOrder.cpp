#include "stdafx.h"
#include "ZOrder.h"

void ZOrder::Init()
{
	_y = transform->GetY();
	_x = transform->GetX();
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

void ZOrder::MoveZ(float z)
{
	if (WALLMANAGER->CheckCross(transform->GetX(), _y, transform->GetX(), _y + z) == true)
		return;

	transform->MoveY(z);
	_y += z;
}

void ZOrder::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB))
	{
		_rc = RectMakeCenter(transform->GetX(), _y, 5, 5);
		Rectangle(BackBuffer, _rc);
	}
}