#include "stdafx.h"
#include "SceneInfoLoader.h"

void SceneInfoLoader::LoadObjectInfo()
{
	vector<string> objectStringInfo = TXTDATAMANAGER->txtLoad("scene_info.txt");
	for (int i = 0; i < objectStringInfo.size() / 3; i++) {
		int x = atoi(objectStringInfo[i * 3].c_str());
		int y = atoi(objectStringInfo[i * 3 + 1].c_str());
		int objectType = atoi(objectStringInfo[i * 3 + 2].c_str());
		switch (objectType) {
		case 0:
			MakeSnow1(x, y);
			break;
		}
	}
}

void SceneInfoLoader::MakeSnow1(float x, float y)
{
	GameObject* snow = new GameObject();
	snow->transform->SetPosition(x, y);
	snow->AddComponent(new Renderer());
	snow->GetComponent<Renderer>()->Init("map/snow1.bmp", 108, 44);
	snow->AddComponent(new ZOrder());
	snow->GetComponent<ZOrder>()->Init();
	snow->GetComponent<ZOrder>()->SetZ(snow->transform->GetY() + 22);
	_sceneObjectV->push_back(snow);
}
