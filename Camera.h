#pragma once
#include "GameObject.h"
class Camera : public Component
{
private :
	int _maxX, _maxY;
	int _screenWidth, _screenHeight;
	int _screenStartX, _screenStartY;
	int _renderWidth, _renderHeight;
	bool _isShake;
	int _shakeWeight;
	int _shakeNum;
	int _shakeMode;
	float _shakeAngle;
	int _shakeDir;
	pair<float, float> _shakeStart;
public:
	Camera();
	~Camera();
	HDC screenDC;
	HBITMAP hBit, oBit;
	int alpha;
	void ResizeScreen(int screenWidth, int screenHeight);
	virtual void Init();
	virtual void Render(HDC frontDC);
	virtual void Update();

	int GetMapWidth() { return _maxX; }
	int GetMapHeight() { return _maxY; }

	void SetScreenStart(int x, int y) { _screenStartX = x; _screenStartY = y; }
	pair<int, int> GetScreenStart() { return { _screenStartX, _screenStartY }; }

	void SetScreenWidth(int width) { _screenWidth = width; }
	void SetScreenHeight(int height) { _screenHeight = height; }
	void SetScreenSize(int width, int height) { _screenWidth = width; _screenHeight = height; }
	int GetScreenWidth() { return _screenWidth; }
	int GetScreenHeight() { return _screenHeight; }
	pair<int, int> GetScreenSize() { return { _screenWidth, _screenHeight }; }

	void SetRenderWidth(int width) { _renderWidth = width; }
	void SetRenderHeight(int height) { _renderHeight = height; }
	void SetRenderSize(int width, int height) { _renderWidth = width; _renderHeight = height;}
	void Shake(int weight, int mode);
	void ShakeOff();
	int GetRenderWidth() { return _renderWidth; }
	int GetRenderHeight() { return _renderHeight; }
	pair<int, int> GetRenderSize() { return { _renderWidth, _renderHeight }; }
	void SetMapSize(int width, int height) { _maxX = width; _maxY = height; }
};

