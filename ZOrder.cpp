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

void ZOrder::Render()
{
	if (!KEYMANAGER->isToggleKey(VK_TAB))
	{
		_rc = RectMakeCenter(transform->GetX(), _y, 5, 5);
		Rectangle(_backBuffer->getMemDC(), _rc);
	}
}