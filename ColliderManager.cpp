#include "stdafx.h"
#include "ColliderManager.h"

ColliderManager::ColliderManager()
{
}

ColliderManager::~ColliderManager()
{
}

HRESULT ColliderManager::init()
{
	return E_NOTIMPL;
}

void ColliderManager::release()
{
}

void ColliderManager::EraseCollider(BoxCollider* targetCollider)
{
	for (int i = 0; i < colliderList.size(); i++) {
		if (colliderList[i] == targetCollider) {
			colliderList.erase(colliderList.begin() + i);
			break;
		}
	}
}

void ColliderManager::AddCollider(BoxCollider* newCollider)
{
	colliderList.push_back(newCollider);
}
