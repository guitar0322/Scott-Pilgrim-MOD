#include "stdafx.h"
#include "GroundManager.h"
#include "Ground.h"
HRESULT GroundManager::Init()
{
    return S_OK;
}

void GroundManager::Release()
{
    _groundV.clear();
}

void GroundManager::AddGround(Ground* newGround)
{
    _groundV.push_back(newGround);
}

void GroundManager::EraseGround(Ground* targetGround)
{
    for (int i = 0; i < _groundV.size(); i++) 
    {
        if (targetGround == _groundV[i]) 
        {
            _groundV.erase(_groundV.begin() + i);
            break;
        }
    }
}

bool GroundManager::CheckGround(int x, int y, int width, int height)
{
    for (int i = 0; i < _groundV.size(); i++) 
    {
        if (CheckGround(x, y, width, height, i))
        {
            return true;
        }
    }
    return false;
}

bool GroundManager::CheckGround(RECT rc)
{
    for (int i = 0; i < _groundV.size(); i++)
    {
        if (CheckGround(rc, i))
        {
            return true;
        }
    }
    return false;
}

bool GroundManager::CheckGround(int x, int y, int width, int height, int idx)
{
    RECT intersectRc;
    RECT destRc = RectMakeCenter(x, y, width, height);
    if (IntersectRect(&intersectRc, &destRc, &_groundV[idx]->GetRc())) {
        return true;
    }
    return false;
}

bool GroundManager::CheckGround(RECT rc, int idx)
{
    RECT intersectRc;
    if (IntersectRect(&intersectRc, &rc, &_groundV[idx]->GetRc())) {
        return true;
    }
    return false;
}

RECT GroundManager::GetGroundRect(int idx)
{
    return _groundV[idx]->GetRc();
}
