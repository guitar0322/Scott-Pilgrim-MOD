#pragma once
#include <vector>

using namespace std;

class SceneInfoLoader
{
private:
	vector<GameObject*>* _sceneObjectV;
public:
	void SetLinkObjectVAddress(vector<GameObject*>* _objectVAddress) { _sceneObjectV = _objectVAddress; }
	void LoadObjectInfo();
	void MakeSnow1(float x, float y);
};

