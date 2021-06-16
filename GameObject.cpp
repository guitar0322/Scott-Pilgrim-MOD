#include "stdafx.h"


GameObject::GameObject()
{
	transform = new Transform();
	transform->gameObject = this;
	isActive = true;
	tag = TAGMANAGER->GetTag("default");
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{
}

void GameObject::Update()
{
	if (isActive == false) return;
	for (int i = 0; i < component_num; i++) {
		if (components[i]->enable == true)
			components[i]->Update();
	}
}

void GameObject::Render()
{
	if (isActive == false) return;
	for (int i = 0; i < component_num; i++) {
		if(components[i]->enable == true)
			components[i]->Render();
	}
}

Component* GameObject::AddComponent(Component* component)
{
	component->gameObject = this;
	component->transform = this->transform;
	component->enable = true;
	components.push_back(component);
	component_num = components.size();
	return component;
}

void GameObject::OnCollision(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnCollision(gameObject);
	}
}

void GameObject::OnTriggerEnter(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerEnter(gameObject);
	}
}

void GameObject::OnTriggerStay(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerStay(gameObject);
	}
}

void GameObject::OnTriggerExit(GameObject* gameObject)
{
	if (isActive == false) return;
	for (int i = 0; i < components.size(); i++) {
		if (components[i]->enable == true)
			components[i]->OnTriggerExit(gameObject);
	}
}
