#pragma once
class Scene
{
private:
protected:
	int _mapWidth;
	int _mapHeight;
	ImageObject* _background;
public:
	Scene();
	~Scene();
	Cam* mainCam;

	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

