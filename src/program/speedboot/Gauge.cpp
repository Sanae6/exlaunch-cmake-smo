#include "speedboot/Gauge.hpp"
#include "al/layout/LayoutActor.h"
#include "al/util.hpp"
#include "al/util/LayoutUtil.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/MathUtil.h"
#include "al/util/NerveUtil.h"
#include "game/WorldList/WorldResourceLoader.h"
#include "logging/logger.hpp"

Gauge::Gauge(WorldResourceLoader* resourceLoader, const al::LayoutInitInfo& initInfo)
    : al::LayoutActor("LoadingGauge"), worldResourceLoader(resourceLoader) {
    al::initLayoutActor(this, initInfo, "GaugeAir", nullptr);
    initNerve(&nrvGaugeAppear, 0);
    al::setPaneLocalScale(this, "All", {5.0f, 5.0f});
    appear();
}

void Gauge::exeAppear() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "Appear", nullptr);
    }

    if (al::isActionEnd(this, nullptr)) {
        al::setNerve(this, &nrvGaugeWait);
    }
}

void Gauge::exeWait() {
    if (al::isNearZero(worldResourceLoader->calcLoadPercent(), 0.001f)) {
        if (al::isFirstStep(this) || al::isActionEnd(this, "Gauge"))
            al::startAction(this, "Decrease", "Gauge");
        return;
    }
    float actual = worldResourceLoader->calcLoadPercent() / 100.0f;
    if (actual < 1.0) {
        al::startFreezeAction(this, "Decrease", al::getActionFrameMax(this, "Decrease", "Gauge") * (1.0f - actual), "Gauge");
    }

    if (actual > 1.0f) {
        al::setNerve(this, &nrvGaugeEnd);
    }
}

void Gauge::exeEnd() {
    if (al::isFirstStep(this)) {
        al::startAction(this, "End", nullptr);
    }

    if (al::isActionEnd(this, nullptr)) {
        kill();
    }
}

namespace {
NERVE_IMPL(Gauge, Appear)
NERVE_IMPL(Gauge, Wait)
NERVE_IMPL(Gauge, End)
}  // namespace