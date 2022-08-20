#pragma once

#include "al/layout/LayoutActor.h"
#include "al/layout/LayoutInitInfo.h"
#include "al/util/NerveUtil.h"

#include "logging/logger.hpp"

// TODO: kill layout if going through loading zone or paused

class HakoniwaSequence;
namespace al {
class SequenceInitInfo;
}
namespace nn {
namespace ui2d {
class TextureInfo;
}
}  // namespace nn
class MoviePlayer;

class MovieTestLayout : public al::LayoutActor {
public:
    MovieTestLayout(const char* name, const al::LayoutInitInfo& initInfo);

    void appear() override;

    void exeDecode();
    void exeWaitForInput();
    void exePlay();

    MoviePlayer* mMoviePlayer;
    nn::ui2d::TextureInfo* mTexture;
};

namespace {
NERVE_HEADER(MovieTestLayout, Decode)
NERVE_HEADER(MovieTestLayout, WaitForInput)
NERVE_HEADER(MovieTestLayout, Play)
}  // namespace