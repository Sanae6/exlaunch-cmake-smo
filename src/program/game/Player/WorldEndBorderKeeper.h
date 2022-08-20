#pragma once

#include <math/seadVector.h>
#include "al/nerve/NerveExecutor.h"

class WorldEndBorderKeeper : al::NerveExecutor {
public:
    void update(sead::Vector3<float> const&, sead::Vector3<float> const&, bool);
    void reset();

private:
    char detail[0x50];
};