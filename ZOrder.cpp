#include "stdafx.h"
#include "ZOrder.h"

void ZOrder::Init()
{
	_z = transform->GetY();
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
	if (WALLMANAGER->CheckCross(transform->GetX(), _z, transform->GetX(), _z + z) == true)
		return;

	transform->MoveY(z);
	_z += z;
}

void ZOrder::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB))
	{
		_rc = RectMakeCenter(transform->GetX(), _z, 5, 5);
		Rectangle(BackBuffer, _rc);
	}
}