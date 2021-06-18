#include "stdafx.h"
#include "ZOrderManager.h"
#include <algorithm>
#include "Renderer.h"
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

bool CompareBottom(Renderer* rendererA, Renderer* rendererB) {
	int bottomA = rendererA->GetRc().bottom;
	int bottomB = rendererB->GetRc().bottom;
	return bottomA < bottomB;
}
void ZOrderManager::update()
{
	sort(_rendererV.begin(), _rendererV.end(), CompareBottom);
}

void ZOrderManager::render()
{
	for (int i = 0; i < _rendererV.size(); i++) {
		string name = _rendererV[i]->gameObject->name;
		_rendererV[i]->Render();
	}
}

void ZOrderManager::AddRenderer(Renderer* newRenderer)
{
	string name = newRenderer->gameObject->name;
	_rendererV.push_back(newRenderer);
}

void ZOrderManager::EraseRenderer(Renderer* targetRenderer)
{
	for (int i = 0; i < _rendererV.size(); i++) {
		if (_rendererV[i] == targetRenderer) {
			_rendererV.erase(_rendererV.begin() + i);
			break;
		}
	}
}
