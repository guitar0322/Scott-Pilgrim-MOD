#include "stdafx.h"

Transform::Transform()
{
	position.x = WINSIZEX / 2;
	position.y = WINSIZEY / 2;
	size.width = 100;
	size.height = 100;
	siblingIdx = -1;
}

Transform::~Transform()
{

}

bool Transform::Move(float x, float y)
{
	int childCount = GetChildCount();
	if (CheckCollision(position.x + x, position.y + y) == true) {
		return false;
	}
	position.x += x;
	position.y += y;
	for (int i = 0; i < childCount; i++) {
		child[i]->MoveX(x);
		child[i]->MoveY(y);
	}
	return true;
}

bool Transform::MoveX(float x)
{
	int childCount = GetChildCount();
	if (CheckCollision(position.x + x, position.y) == true) {
		return false;
	}
	position.x += x;
	for (int i = 0; i < childCount; i++) {
		child[i]->MoveX(x);
	}
	return true;
}

bool Transform::MoveY(float y)
{
	int childCount = GetChildCount();
	if (CheckCollision(position.x, position.y + y) == true) {
		return false;
	}
	position.y += y;
	for (int i = 0; i < childCount; i++) {
		child[i]->MoveY(y);
	}
	return true;
}

bool Transform::CheckCollision(float tempX, float tempY)
{
	BoxCollider* collider;
	collider = gameObject->GetComponent<BoxCollider>();
	if (collider == nullptr) {
		return false;
	}
	else {
		return collider->CheckCollision(tempX, tempY);
	}
	return false;
}

Transform* Transform::GetChild(int i)
{
	if (i >= GetChildCount()) {
		return nullptr;
	}
	else {
		return child[i];
	}
}

void Transform::AddChild(GameObject* gameObject)
{
	child.push_back(gameObject->transform);
	gameObject->transform->parent = this;
	gameObject->transform->siblingIdx = GetChildCount() - 1;
}

void Transform::AddChild(Transform* transform)
{
	child.push_back(transform);
	transform->parent = this;
	transform->siblingIdx = GetChildCount() - 1;
}

void Transform::DetachChild(int idx)
{
	if (idx > GetChildCount() - 1)
	{
		sprintf_s(error, "DetachChild���� : idx�� ���� �ʽ��ϴ�", idx);
		throw "�ڽĻ��� idx�� ���� �ʽ��ϴ�";
		return;
	}
	child[idx]->parent = nullptr;
	child[idx]->siblingIdx = -1;
	child.erase(child.begin() + idx);
}

void Transform::DetachParent()
{
	if (parent == nullptr) {
		sprintf_s(error, "DetachParent���� : �θ� ������Ʈ�� �������� �ʽ��ϴ�");
		throw "�θ� ������Ʈ�� �������� �ʽ��ϴ�";
		return;
	}
	parent->DetachChild(siblingIdx);
}
