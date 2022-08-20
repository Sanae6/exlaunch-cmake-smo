#pragma once

#include "GameFrameWorkNx.h"
#include "game/System/GameDrawInfo.h"
#include <heap/seadDisposer.h>

namespace al {
    class AccountHolder;
    class SystemKit;
}

class Application {
    SEAD_SINGLETON_DISPOSER(Application)
    Application();

public:
    al::GameDrawInfo* mGameDrawInfo;
    al::AccountHolder* mAccountHolder;
    al::GameFrameworkNx* mFramework;  // 0x28
};
