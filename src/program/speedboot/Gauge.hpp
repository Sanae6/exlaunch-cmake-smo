#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

class WorldResourceLoader;

class Gauge : public al::LayoutActor {
public:
    Gauge(WorldResourceLoader* resourceLoader, const al::LayoutInitInfo& initInfo);

    void exeAppear();
    void exeWait();
    void exeEnd();
private:
    WorldResourceLoader* worldResourceLoader;
};

namespace {
NERVE_HEADER(Gauge, Appear)
NERVE_HEADER(Gauge, Wait)
NERVE_HEADER(Gauge, End)
}