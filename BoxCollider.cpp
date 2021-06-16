#include "stdafx.h"
#include "BoxCollider.h"

BoxCollider::BoxCollider()
{
	COLLIDERMANAGER->colliderList.push_back(this);
	width = 100;
	height = 100;
	isTrigger = false;
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::Update()
{
	rc = RectMakeCenter(transform->GetX(), transform->GetY(), width, height);
	int colNum = COLLIDERMANAGER->colliderList.size();
	for (int i = 0; i < colNum; i++) {
		if (CheckCollision(GetCenterX(rc), GetCenterY(rc), i)) {
			vCol.push_back(i);
		}
	}
	for (int i = 0; i < vCol.size(); i++) {
		bool isExist = false;
		for (int j = 0; j < prevCol.size(); j++) {
			 if(vCol[i] == prevCol[j]) {
				gameObject->OnTriggerStay(COLLIDERMANAGER->colliderList[prevCol[j]]->gameObject);
				isExist = true;
				break;
			}
		}
		if (isExist == false) {
			gameObject->OnTriggerEnter(COLLIDERMANAGER->colliderList[vCol[i]]->gameObject);
		}
	}

	for (int i = 0; i < prevCol.size(); i++) {
		bool isExist = false;
		for (int j = 0; j < vCol.size(); j++) {
			if (vCol[j] == prevCol[i]) {
				isExist = true;
				break;
			}
		}
		if (isExist == false) {
			gameObject->OnTriggerExit(COLLIDERMANAGER->colliderList[prevCol[i]]->gameObject);
		}
	}

	prevCol.clear();
	prevCol.assign(vCol.begin(), vCol.end());
	vCol.clear();
}
bool BoxCollider::CheckCollision(float tempX, float tempY) {
	if (enable == false) {
		return false;
	}
	int colNum = COLLIDERMANAGER->colliderList.size();
	int deltaX = tempX - transform->GetX();
	int deltaY = tempY - transform->GetY();
	int marginX = 0, marginY = 0;
	for (int i = 0; i < colNum; i++) {
		if (CheckCollision(tempX, tempY, i)) {
			if (COLLIDERMANAGER->colliderList[i]->isTrigger == false) {
				int w = intersectRc.right - intersectRc.left;
				int h = intersectRc.bottom - intersectRc.top;
				if (w <= h) {
					deltaX > 0 ? marginX = deltaX - w : marginX = deltaX + w;
				}
				else {
					deltaY > 0 ? marginY = deltaY - h : marginY = deltaY + h;
				}
				gameObject->OnCollision(COLLIDERMANAGER->colliderList[i]->gameObject);
				transform->Move(marginX, marginY);
				return true;
			}
		}
	}
	return false;
}
bool BoxCollider::CheckCollision(float tempX, float tempY, int colIdx)
{
	RECT tempRc = RectMakeCenter(tempX, tempY, width, height);
	RECT* targetRc;
	if (&this->rc == &COLLIDERMANAGER->colliderList[colIdx]->rc) return false;
	targetRc = &COLLIDERMANAGER->colliderList[colIdx]->rc;
	if (IntersectRect(&intersectRc, &tempRc, targetRc)) {
		int w = intersectRc.right - intersectRc.left;
		int h = intersectRc.bottom - intersectRc.top;
		if (h >= w) {
			if (intersectRc.right <= GetCenterX(*targetRc)) {
			}
			else {
			}
		}
		else {
		}
		return true;
	}
	return false;
}
void BoxCollider::Render()
{
	HPEN hPen, oPen;
	HBRUSH hBrush, oBrush;
	if (KEYMANAGER->isToggleKey(VK_TAB)) {
		return;
	}
	hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	oBrush = (HBRUSH)SelectObject(_backBuffer->getMemDC(), hBrush);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	oPen = (HPEN)SelectObject(_backBuffer->getMemDC(), hPen);
	Rectangle(_backBuffer->getMemDC(), rc);
	SelectObject(_backBuffer->getMemDC(), oPen);
	SelectObject(_backBuffer->getMemDC(), oBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}
