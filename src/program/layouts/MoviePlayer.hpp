#pragma once

#include "agl/DrawContext.h"
#include "agl/TextureData.h"
#include "al/scene/ISceneObj.h"
#include <heap/seadDisposer.h>

class MoviePlayer : public al::ISceneObj, public sead::IDisposer {
public:
    MoviePlayer();
    ~MoviePlayer();
    void update();
    void draw(agl::DrawContext*) const;
    agl::TextureData* getTexture() const;
    void play(const char* movieLocation);
    void stop();
    bool isPlay() const;
    bool isDecode() const;
    bool isLooped() const;
};