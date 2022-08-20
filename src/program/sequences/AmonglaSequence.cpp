#include "sequences/AmonglaSequence.hpp"
#include <basis/seadNew.h>
#include <gfx/seadCamera.h>
#include <gfx/seadOrthoProjection.h>
#include <gfx/seadPrimitiveRenderer.h>
#include <gfx/seadViewport.h>
#include <heap/seadHeapMgr.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include "al/audio/AudioDirectorInitInfo.h"
#include "al/audio/AudioSystemFunction.h"
#include "al/scene/SceneCreator.h"
#include "al/screen/ScreenCaptureExecutor.h"
#include "al/util.hpp"
#include "al/util/ControllerUtil.h"
#include "game/GameData/GameDataHolder.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"
#include "game/System/Application.h"
#include "logging/logger.hpp"
#include "nvn/nvn_api.h"
#include "nvn/nvn_types.h"
#include "sequences/AmonglaGameDataHolder.hpp"
#include "sequences/AmonglaHeaderDump.hpp"
#include "sequences/AmonglaSceneFactory.hpp"
#include "sequences/TrueScene.hpp"

struct SequenceFactory {
    static al::Sequence* createSequence(const char* name);
};

void drawBackground(agl::DrawContext* context);

al::Sequence* amonglaPatch(const char* name) {
    return new AmonglaSequence(AmonglaSequence::name());
}

AmonglaSequence::AmonglaSequence(const char* name) : al::Sequence(name) {
    Logger::log("CONSTRUCTOR\n");
}

void AmonglaSequence::init(const al::SequenceInitInfo& initInfo) {
    AmonglaSequence::initDrawSystemInfo(initInfo);
    Logger::log("initDrawSystemInfo\n");

    mScreenCaptureExecutor = new al::ScreenCaptureExecutor(1);
    const auto physicalArea = getDrawInfo()->mFirstRenderBuffer->getPhysicalArea();
    mScreenCaptureExecutor->createScreenCapture((int)(physicalArea.getSizeX()),
                                                (int)(physicalArea.getSizeY()), 0);
    Logger::log("screenCapture created\n");

    al::AudioDirectorInitInfo audioInitInfo = {};
    al::AudioSystemInfo* audioSystemInfo =
        alAudioSystemFunction::getAudioSystemInfo(initInfo.mSystemInfo);
    audioInitInfo.mSeDirectorInitInfo.unknown_0x0 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x4 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x30 = -1;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x60 = -1.0;
    audioInitInfo.unknown_0x20 = 0;
    audioInitInfo.unknown_0x18 = 0;
    audioInitInfo.mAudioSystemInfo = nullptr;
    audioInitInfo.unknown_0x8 = 0;
    audioInitInfo.mCurrentStage = nullptr;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x8 = 1;
    audioInitInfo.mSeDirectorInitInfo.mUseMusicEffects = true;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x21 = false;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x28 = nullptr;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x38 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x64 = 1.0;
    audioInitInfo.mBgmDirectorInitInfo.unknown_0x0 = false;
    audioInitInfo.mSeDirectorInitInfo.mName = "注視点";
    audioInitInfo.mSeDirectorInitInfo.unknown_0x18 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x50 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x58 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x40 = 0;
    audioInitInfo.mSeDirectorInitInfo.unknown_0x48 = 0;
    audioInitInfo.mBgmDirectorInitInfo.unknown_0x8 = nullptr;
    audioInitInfo.mDuckingName = nullptr;
    
    Logger::log("audioInitInfo prepared\n");
    al::initAudioDirector(this, audioSystemInfo, audioInitInfo);
    Logger::log("initializedAudioDirector\n");
    initAudioKeeper("Sequence");
    Logger::log("initializedAudioKeeper\n");

    AmonglaGameDataHolder* holder = new AmonglaGameDataHolder(initInfo.mSystemInfo->mMessageSys);
    al::initSceneCreator(this, initInfo, holder, getAudioDirector(), mScreenCaptureExecutor,
                         new AmonglaSceneFactory());
    Logger::log("initializedSceneCreator!!!!\n");
}

void AmonglaSequence::drawMain() const {
    al::Sequence::drawMain();

    drawBackground(getDrawInfo()->mDrawContext);
}
