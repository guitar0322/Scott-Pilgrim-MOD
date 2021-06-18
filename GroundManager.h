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
	bool CheckGround(int x, int y, int width, int height);
	bool CheckGround(RECT rc);
	bool CheckGround(int x, int y, int width, int height, int idx);
	bool CheckGround(RECT rc, int idx);
	RECT GetGroundRect(int idx);
};

