#pragma once
#include "GameObject.h"
class ObjectInfo :
    public Component
{
public:
    ObjectInfo(bool isAir);
    ~ObjectInfo();
    bool isAir;
};

