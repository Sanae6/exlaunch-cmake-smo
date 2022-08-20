#include "al/layout/LayoutInitInfo.h"
#include "al/nerve/Nerve.h"
#include "al/nerve/NerveStateBase.h"
#include "al/util/ControllerUtil.h"
#include "al/util/NerveUtil.h"
#include "al/wipe/WipeHolder.h"
#include "game/GameData/GameDataFunction.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/WorldList/WorldResourceLoader.h"
#include "speedboot/Gauge.hpp"

NERVE_HEADER(HakoniwaSequence, LoadStage);
NERVE_HEADER(HakoniwaSequence, LoadWorldResourceWithBoot);
NERVE_IMPL(HakoniwaSequence, LoadStage);
NERVE_IMPL(HakoniwaSequence, LoadWorldResourceWithBoot);
namespace speedboot {
class CustomBootNerve : public al::Nerve {
public:
    void execute(al::NerveKeeper* keeper) override {
        // auto* sequence = static_cast<HakoniwaSequence*>(keeper->mParent);
        if (al::updateNerveState(keeper->mParent)) {
            al::setNerve(keeper->mParent, &nrvHakoniwaSequenceLoadStage);
        }
    }
};

CustomBootNerve nrvMyBallsSimulatorCock;

al::LayoutInitInfo copiedInitInfo;

namespace {
NERVE_HEADER(HakoniwaSequenceDeezNuts, InitThread)
NERVE_HEADER(HakoniwaSequenceDeezNuts, LoadStage)
NERVE_HEADER(HakoniwaSequenceDeezNuts, WipeToKill)
}  // namespace

struct HakoniwaSequenceDeezNuts : public al::NerveStateBase {
    HakoniwaSequenceDeezNuts(HakoniwaSequence* sequence)
        : al::NerveStateBase("AmongSex"), mSequence(sequence) {
        Logger::log("Amongla death\n");
        Logger::log("Sequence: %s, Resource loader: %p\n", mSequence->getName().cstr(),
                    mSequence->mResourceLoader);
        initNerve(&nrvHakoniwaSequenceDeezNutsInitThread, 0);
    }

    void exeInitThread() {
        if (al::isFirstStep(this)) {
            mSequence->mInitThread->start();
        }

        if (mSequence->mInitThread->isDone()) {
            al::setNerve(this, &nrvHakoniwaSequenceDeezNutsLoadStage);
        }
    }

    bool isDoneLoading() const {
        return mSequence->mResourceLoader->isEndLoadWorldResource() && mSequence->mInitThread->isDone();
    }

    void exeLoadStage() {
        if (al::isFirstStep(this)) {
            // mSequence->mInitThread->start();
            const char* name = GameDataFunction::getNextStageName(this->mSequence->mGameDataHolder);
            if (name == nullptr) name = GameDataFunction::getMainStageName(this->mSequence->mGameDataHolder, 0);
            int scenario = GameDataFunction::calcNextScenarioNo(this->mSequence->mGameDataHolder);
            if (scenario == -1) scenario = 1;
            int world = this->mSequence->mGameDataHolder.mData->mWorldList->tryFindWorldIndexByStageName(name);
            if (world > -1) {
                Logger::log("Requesting %d-%d\n", world, scenario);
                mSequence->mResourceLoader->requestLoadWorldHomeStageResource(world, scenario);
            }
        }
        // Logger::log("Percentage %.02f, %s\n", mSequence->mResourceLoader->calcLoadPercent(),
        //             mSequence->mResourceLoader->isEndLoadWorldResource() ? "true" : "false");

        if (isDoneLoading()) {
            al::setNerve(this, &nrvHakoniwaSequenceDeezNutsWipeToKill);
        }
    }

    void exeWipeToKill() {
        if (al::isFirstStep(this)) {
            mSequence->mWipeHolder->startClose("FadeWhite", -1);
        }

        if (mSequence->mWipeHolder->isCloseEnd()) kill();
    }

private:
    HakoniwaSequence* mSequence;
};

namespace {
NERVE_IMPL(HakoniwaSequenceDeezNuts, InitThread);
NERVE_IMPL(HakoniwaSequenceDeezNuts, LoadStage);
NERVE_IMPL(HakoniwaSequenceDeezNuts, WipeToKill);
}  // namespace

HakoniwaSequenceDeezNuts* deezNutsState;

extern "C" void _ZN10BootLayoutC1ERKN2al14LayoutInitInfoE(BootLayout* layout,
                                                          const al::LayoutInitInfo& layoutInitInfo);

void prepareLayoutInitInfo(BootLayout* layout, const al::LayoutInitInfo& layoutInitInfo) {
    register HakoniwaSequence* sequence asm ("x19");
    new Gauge(sequence->mResourceLoader, layoutInitInfo);
    _ZN10BootLayoutC1ERKN2al14LayoutInitInfoE(layout, layoutInitInfo);
}

void hakoniwaSetNerveSetup(al::IUseNerve* useNerve, al::Nerve* nerve) {
    al::setNerve(useNerve, &nrvMyBallsSimulatorCock);
    auto* sequence = static_cast<HakoniwaSequence*>(useNerve);
    deezNutsState = new HakoniwaSequenceDeezNuts(sequence);
    al::initNerveState(useNerve, deezNutsState, &nrvMyBallsSimulatorCock, "AmongSex");
}
}  // namespace speedboot