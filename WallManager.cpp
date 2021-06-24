#include "stdafx.h"
#include "WallManager.h"
#include "Wall.h"
void WallManager::Init()
{
}

void WallManager::Release()
{
}

void WallManager::EraseWall(Wall* targetWall)
{
	for (int i = 0; i < _wallV.size(); i++)
	{
		if (_wallV[i] == targetWall) 
		{
			_wallV.erase(_wallV.begin() + i);
			break;
		}
	}
}

bool WallManager::CheckCross(int startX, int startY, int endX, int endY)
{
	for (int i = 0; i < _wallV.size(); i++) 
	{
		if (CheckCross(startX, startY, endX, endY, i) == true) 
		{
			return true;
		}
	}
	return false;
}

bool WallManager::CheckCross(int startX, int startY, int endX, int endY, int idx)
{
	if (_wallV[idx]->IsCross(startX, startY, endX, endY) == true)
		return true;
	return false;
}
