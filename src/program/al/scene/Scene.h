#pragma once

#include <prim/seadSafeString.h>
#include "al/audio/AudioKeeper.h"
#include "al/camera/CameraDirector.h"
#include "al/nerve/NerveExecutor.h"
#include "al/scene/SceneInitInfo.h"
#include "al/scene/SceneObjHolder.h"
#include "al/camera/CameraDirector.h"
#include "al/audio/AudioKeeper.h"
#include "al/actor/LiveActorKit.h"

namespace al {
class StageResourceKeeper;
class LiveActorKit;
class LayoutKit;
class SceneStopCtrl;
class SceneMsgCtrl;
class ScreenCoverCtrl;
class AudioDirector;
class AudioKeeper;
class NerveKeeper;

class Scene : public al::NerveExecutor,
              public al::IUseAudioKeeper,
              public al::IUseCamera,
              public al::IUseSceneObjHolder {
public:
    Scene(const char* name);

    virtual ~Scene();
    virtual void init(const al::SceneInitInfo&);
    virtual void appear();
    virtual void kill();
    virtual void movement();
    virtual void control();
    virtual void drawMain();
    virtual void drawSub();
    al::AudioKeeper* getAudioKeeper() const override {
        return mAudioKeeper;
    }
    al::SceneObjHolder* getSceneObjHolder() const override {
        return mSceneObjHolder;
    }
    al::CameraDirector* getCameraDirector() const override {
        return mLiveActorKit->getCameraDirector();
    }

private:
    bool mIsAlive;
    sead::FixedSafeString<0x40> mName;
    StageResourceKeeper* mStageResourceKeeper;
    LiveActorKit* mLiveActorKit;
    LayoutKit* mLayoutKit;
    SceneObjHolder* mSceneObjHolder;
    SceneStopCtrl* mSceneStopCtrl;
    SceneMsgCtrl* mSceneMsgCtrl;
    ScreenCoverCtrl* mScreenCoverCtrl;
    AudioDirector* mAudioDirector;
    AudioKeeper* mAudioKeeper;
    NerveKeeper* mNerveKeeper;
};

static_assert(sizeof(al::Scene) == 0xd8);
}  // namespace al