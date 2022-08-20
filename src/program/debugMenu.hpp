#pragma once

#include <sead/basis/seadNew.hpp>
#include <sead/devenv/seadDebugFontMgrNvn.h>
#include <sead/gfx/seadViewport.h>
#include <sead/textwriter.h>

#include "agl/DrawContext.h"

#include "game/System/GameSystem.h"

#include "al/util.hpp"
#include "logging/logger.hpp"
#include "hook/trampoline_hook.hpp"

HOOK_DEFINE_TRAMPOLINE(SetupDebugMenu) {
    static void Callback(void*);
};

class HakoniwaSequence;
HOOK_DEFINE_TRAMPOLINE(DrawDebugMenu) {
    static void Callback(HakoniwaSequence*);
};
extern void drawDebugMenu(HakoniwaSequence *curSequence, sead::Viewport *viewport, agl::DrawContext *drawContext);