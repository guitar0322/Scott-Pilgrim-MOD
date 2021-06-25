#pragma once
class Ground;
class GroundManager : public singletonBase<GroundManager>
{
private:
	vector<Ground*> _groundV;
public:
	GroundManager() {};
	~GroundManager() {};
	HRESULT Init();
	void Release();
	void AddGround(Ground* newGround);
	void EraseGround(Ground* targetGround);
	int CheckGround(int x, int y, int width, int height);
	int CheckGround(RECT rc);
	int CheckGround(int x, int y, int width, int height, int idx);
	int CheckGround(RECT rc, int idx);
	RECT GetGroundRect(int idx);
};

