#pragma once

#include "agl/DrawContext.h"
#include "agl/RenderBuffer.h"

namespace al {
class GameDrawInfo {
public:
    agl::RenderBuffer* mFirstRenderBuffer;
    agl::RenderBuffer* mSecondRenderBuffer;
    bool mUseFirstBuffer;
    agl::DrawContext* mDrawContext;
};
}  // namespace al
