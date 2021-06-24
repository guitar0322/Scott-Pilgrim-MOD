#pragma once
class Wall;
class WallManager : public singletonBase<WallManager>
{
private:
	vector<Wall*> _wallV;
public:
	void Init();
	void Release();

	void AddWall(Wall* newWall) { _wallV.push_back(newWall); }
	void EraseWall(Wall* targetWall);

	bool CheckCross(int startX, int startY, int endX, int endY);
	bool CheckCross(int startX, int startY, int endX, int endY, int idx);
};

