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

int GroundManager::CheckGround(int x, int y, int width, int height)
{
    for (int i = 0; i < _groundV.size(); i++) 
    {
        int intersectHeight = CheckGround(x, y, width, height, i);
        if (intersectHeight != 0)
        {
            return intersectHeight;
        }
    }
    return 0;
}

int GroundManager::CheckGround(RECT rc)
{
    for (int i = 0; i < _groundV.size(); i++)
    {
        int intersectHeight = CheckGround(rc, i);
        if (intersectHeight != 0)
        {
            return intersectHeight;
        }
    }
    return 0;
}

int GroundManager::CheckGround(int x, int y, int width, int height, int idx)
{
    RECT intersectRc;
    RECT destRc = RectMakeCenter(x, y, width, height);
    if (IntersectRect(&intersectRc, &destRc, &_groundV[idx]->GetRc())) {
        return intersectRc.bottom - intersectRc.top;
    }
    return 0;
}

int GroundManager::CheckGround(RECT rc, int idx)
{
    RECT intersectRc;
    if (IntersectRect(&intersectRc, &rc, &_groundV[idx]->GetRc())) {
        return intersectRc.bottom - intersectRc.top;
    }
    return 0;
}

RECT GroundManager::GetGroundRect(int idx)
{
    return _groundV[idx]->GetRc();
}
