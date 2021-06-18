#pragma once
#include "singletonBase.h"

class Renderer;
class ZOrderManager : public singletonBase<ZOrderManager>
{
private:
	vector<Renderer*> _rendererV;
public:
	ZOrderManager();
	~ZOrderManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void AddRenderer(Renderer* newRenderer);
	void EraseRenderer(Renderer* targetRenderer);
};

