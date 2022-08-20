#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <math/seadQuat.h>

namespace al {
    class GamePadSystem;
}

class PlayerInitInfo {
public:
    al::GamePadSystem* mGamePadSystem;
    sead::Matrix34f* mViewMtx;
    int mPort;
    const char* mCostume;
    const char* mCap;
    sead::Vector3f mPosition;
    sead::Quatf mRotation;
    bool mNeedleNose;
    bool mClosetScene;
};