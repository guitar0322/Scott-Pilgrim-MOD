#include "stdafx.h"
#include "SceneInfoLoader.h"

void SceneInfoLoader::LoadObjectInfo()
{
	vector<string> objectStringInfo = TXTDATAMANAGER->txtLoad("scene_info.txt");
	_typeV.clear();
	for (int i = 0; i < objectStringInfo.size() / 3; i++) {
		int x = atoi(objectStringInfo[i * 3].c_str());
		int y = atoi(objectStringInfo[i * 3 + 1].c_str());
		int objectType = atoi(objectStringInfo[i * 3 + 2].c_str());
		_sceneObjectV->push_back(MakeObject(x, y, objectType));
		_typeV.push_back(objectType);
	}
}

void SceneInfoLoader::LoadObjectInfo(int type)
{
	vector<string> objectStringInfo = TXTDATAMANAGER->txtLoad("scene_info.txt");
	_typeV.clear();
	for (int i = 0; i < objectStringInfo.size() / 3; i++) {
		int x = atoi(objectStringInfo[i * 3].c_str());
		int y = atoi(objectStringInfo[i * 3 + 1].c_str());
		int objectType = atoi(objectStringInfo[i * 3 + 2].c_str());
		if (objectType != type) continue;
		_sceneObjectV->push_back(MakeObject(x, y, objectType));
		_typeV.push_back(type);
	}
}

GameObject* SceneInfoLoader::MakeObject(float x, float y, int type)
{
	GameObject* newObject = nullptr;
	switch (type) {
	case 0:
		newObject = MakeSnow1(x, y);
		break;
	case 1:
		newObject = MakeSnow2(x, y);
		break;
	case 2:
		newObject = MakeFencePillar(x, y);
		break;
	case 3:
		newObject = MakeFencePillar2(x, y);
		break;
	case 4:
		if (SCENEMANAGER->GetCurScene() == SCENEMANAGER->GetScene("start"))
			newObject = MakeLee(x, y);
		else
			newObject = MakeLeeEditor(x, y);
		break;
	}
	return newObject;
}

GameObject* SceneInfoLoader::MakeSnow1(float x, float y)
{
	GameObject* snow = new GameObject();
	snow->transform->SetPosition(x, y);
	snow->AddComponent(new Renderer());
	snow->GetComponent<Renderer>()->Init("map/snow1.bmp", 108, 44);
	snow->AddComponent(new ZOrder());
	snow->GetComponent<ZOrder>()->Init();
	snow->GetComponent<ZOrder>()->SetZ(snow->transform->GetY() + 22);
	return snow;
}

GameObject* SceneInfoLoader::MakeSnow2(float x, float y)
{
	GameObject* snow2 = new GameObject();
	snow2->transform->SetPosition(x, y);
	snow2->AddComponent(new Renderer());
	snow2->GetComponent<Renderer>()->Init("map/snow2.bmp", 164, 62);
	snow2->AddComponent(new ZOrder());
	snow2->GetComponent<ZOrder>()->Init();
	snow2->GetComponent<ZOrder>()->SetZ(snow2->transform->GetY() + 31);
	return snow2;
}

GameObject* SceneInfoLoader::MakeFencePillar(float x, float y)
{
	GameObject* fencePillar = new GameObject();
	fencePillar->transform->SetPosition(x, y);
	fencePillar->AddComponent(new Renderer());
	fencePillar->GetComponent<Renderer>()->Init("map/fence_pillar.bmp", 114, 168);
	fencePillar->AddComponent(new ZOrder());
	fencePillar->GetComponent<ZOrder>()->Init();
	fencePillar->GetComponent<ZOrder>()->SetZ(fencePillar->transform->GetY() + 84);
	return fencePillar;
}

GameObject* SceneInfoLoader::MakeFencePillar2(float x, float y)
{
	GameObject* fencePillar2 = new GameObject();
	fencePillar2->transform->SetPosition(x, y);
	fencePillar2->AddComponent(new Renderer());
	fencePillar2->GetComponent<Renderer>()->Init("map/fence_pillar2.bmp", 114, 156);
	fencePillar2->AddComponent(new ZOrder());
	fencePillar2->GetComponent<ZOrder>()->Init();
	fencePillar2->GetComponent<ZOrder>()->SetZ(fencePillar2->transform->GetY() + 78);
	return fencePillar2;
}

GameObject* SceneInfoLoader::MakeLee(float x, float y)
{
	GameObject* lee = new Luke();
	lee->transform->SetPosition(x, y);
	return lee;
}

GameObject* SceneInfoLoader::MakeLeeEditor(float x, float y)
{
	GameObject* demoLee = new GameObject();
	demoLee->transform->SetPosition(x, y);
	demoLee->AddComponent(new Renderer());
	demoLee->GetComponent<Renderer>()->Init("lee/lee_block_left.bmp", 88, 132);
	demoLee->AddComponent(new ZOrder());
	demoLee->GetComponent<ZOrder>()->Init();
	demoLee->GetComponent<ZOrder>()->SetZ(demoLee->transform->GetY() + 66);
	return demoLee;
}
