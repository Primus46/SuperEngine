#pragma once
#include "GameObjects/Projectiles/SEProjectile.h"

class SEPlayerProjectile :
    public SEProjectile
{
public: 
    SEPlayerProjectile(SEString DefaultName, Window* AssignedWindow);
};

