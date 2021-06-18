#include "stdafx.h"
#include "ZOrderManager.h"
#include <algorithm>
#include "ZOrder.h"
ZOrderManager::ZOrderManager()
{
}

ZOrderManager::~ZOrderManager()
{
}

HRESULT ZOrderManager::init()
{
	return E_NOTIMPL;
}

void ZOrderManager::release()
{
}

bool CompareBottom(ZOrder* rendererA, ZOrder* rendererB) {
	return rendererA->GetY() < rendererB->GetY();
}
void ZOrderManager::update()
{
	sort(_zOrderV.begin(), _zOrderV.end(), CompareBottom);
}

void ZOrderManager::render()
{
	for (int i = 0; i < _zOrderV.size(); i++) {
		string name = _zOrderV[i]->gameObject->name;
		_zOrderV[i]->gameObject->Render();
	}
}

void ZOrderManager::AddZOrder(ZOrder* newZOrder)
{
	_zOrderV.push_back(newZOrder);
}

void ZOrderManager::EraseZOrder(ZOrder* targetZOrder)
{
	for (int i = 0; i < _zOrderV.size(); i++) {
		if (_zOrderV[i] == targetZOrder) {
			_zOrderV.erase(_zOrderV.begin() + i);
			break;
		}
	}
}
