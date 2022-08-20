#include "al/layout/LayoutInitInfo.h"
#include "al/scene/SceneObjHolder.h"
#include "al/sequence/SequenceInitInfo.h"
#include "al/util/ControllerUtil.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/NerveUtil.h"
#include "logging/logger.hpp"

#include "al/string/StringTmp.h"
#include "al/util.hpp"

#include "prim/seadSafeString.h"

#include "rs/util.hpp"

#include "layouts/MoviePlayer.hpp"
#include "layouts/MovieTestLayout.hpp"

#include <cstdio>
#include <cstring>

namespace al {
    al::ISceneObj* createSceneObj(const al::IUseSceneObjHolder*, int);
    void updateTextureInfo(nn::ui2d::TextureInfo*, const agl::TextureData&);
    nn::ui2d::TextureInfo* createTextureInfo();
    const agl::TextureData* getRed2DTexture();
    void setPaneTexture(al::IUseLayout*, char const*, nn::ui2d::TextureInfo const*);
}

MovieTestLayout::MovieTestLayout(const char* name, const al::LayoutInitInfo& initInfo)
    : al::LayoutActor(name) {
    al::initLayoutActor(this, initInfo, name, 0);
    initNerve(&nrvMovieTestLayoutDecode, 0);

    mMoviePlayer = static_cast<MoviePlayer*>(al::createSceneObj(this, 0x24));
    mTexture = al::createTextureInfo();
}

void MovieTestLayout::appear() {
    al::setNerve(this, &nrvMovieTestLayoutDecode);

    mMoviePlayer->play("content:/MovieData/old_1.mp4");

    al::LayoutActor::appear();
}

void MovieTestLayout::exeDecode() {
    mMoviePlayer->update();
    if (mMoviePlayer->isDecode()) {
        al::setNerve(this, &nrvMovieTestLayoutWaitForInput);
    }
}

void MovieTestLayout::exeWaitForInput() {
    if (al::isFirstStep(this)) {
        al::hidePane(this, "TestAsset");
    }
    // if (al::isActionEnd(this, 0)) {
    //     al::setNerve(this, &nrvMovieTestLayoutWait);
    // }
    if (al::isPadTriggerRight(-1)) {
        al::setNerve(this, &nrvMovieTestLayoutPlay);
    }
}

void MovieTestLayout::exePlay() {
    if (al::isFirstStep(this)) {
        al::showPane(this, "TestAsset");
    }

    mMoviePlayer->update();
    auto* texture = mMoviePlayer->getTexture();
    al::updateTextureInfo(mTexture, *texture);
    al::setPaneTexture(this, "TestAsset", mTexture);
    if (mMoviePlayer->isLooped()) {
        mMoviePlayer->stop();
        kill();
        appear();
    }
}

namespace {
NERVE_IMPL(MovieTestLayout, Decode)
NERVE_IMPL(MovieTestLayout, WaitForInput)
NERVE_IMPL(MovieTestLayout, Play)
}  // namespace