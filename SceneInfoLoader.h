#pragma once
#include <vector>

using namespace std;

class SceneInfoLoader
{
private:
	vector<GameObject*>* _sceneObjectV;
	vector<int> _typeV;
public:
	void SetLinkObjectVAddress(vector<GameObject*>* _objectVAddress) { _sceneObjectV = _objectVAddress; }
	void LoadObjectInfo();
	void LoadObjectInfo(int type);
	GameObject* MakeObject(float x, float y, int type);
	GameObject* MakeSnow1(float x, float y);
	GameObject* MakeSnow2(float x, float y);
	GameObject* MakeFencePillar(float x, float y);
	GameObject* MakeFencePillar2(float x, float y);
	GameObject* MakeLee(float x, float y);
	GameObject* MakeLeeEditor(float x, float y);
	vector<int> GetTypeV() const { return _typeV; }
};

