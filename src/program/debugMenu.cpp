#include "debugMenu.hpp"
#include "agl/utl.h"
#include "game/HakoniwaSequence/HakoniwaSequence.h"

static const char* DBG_FONT_PATH = "DebugData/Font/nvn_font_jis1.ntx";
static const char* DBG_SHADER_PATH = "DebugData/Font/nvn_font_shader_jis1.bin";
static const char* DBG_TBL_PATH = "DebugData/Font/nvn_font_jis1_tbl.bin";

sead::TextWriter* textWriter;

void setupDebugMenu(GameSystem* gSys) {
    sead::Heap* curHeap = al::getCurrentHeap();

    agl::DrawContext* context = gSys->mSystemInfo->mDrawInfo->mDrawContext;

    if (curHeap && context) {
        sead::DebugFontMgrJis1Nvn::sInstance = sead::DebugFontMgrJis1Nvn::createInstance(curHeap);

        if (al::isExistFile(DBG_FONT_PATH) && al::isExistFile(DBG_SHADER_PATH) && al::isExistFile(DBG_TBL_PATH)) {
            sead::DebugFontMgrJis1Nvn::sInstance->initialize(curHeap, DBG_SHADER_PATH, DBG_FONT_PATH, DBG_TBL_PATH,
                                                             0x100000);
            sead::TextWriter::setDefaultFont(sead::DebugFontMgrJis1Nvn::sInstance);
            textWriter = new sead::TextWriter(context);
            sead::TextWriter::setupGraphics(context);
        } else {
            EXL_ABORT(0x6969);
        }
    } else {
        EXL_ABORT(0x4290);
    }
}

namespace GameSystemFunction {
    GameSystem* getGameSystem();
}

void SetupDebugMenu::Callback(void* layoutSystemThis) {
    Orig(layoutSystemThis);
    setupDebugMenu(GameSystemFunction::getGameSystem());
}

void drawBackground(agl::DrawContext* context) {

    sead::Vector3<float> p1; // top left
    p1.x = -1.0;
    p1.y = 0.3;
    p1.z = 0.0;
    sead::Vector3<float> p2; // top right
    p2.x = -0.2;
    p2.y = 0.3;
    p2.z = 0.0;
    sead::Vector3<float> p3; // bottom left
    p3.x = -1.0;
    p3.y = -1.0;
    p3.z = 0.0;
    sead::Vector3<float> p4; // bottom right
    p4.x = -0.2;
    p4.y = -1.0;
    p4.z = 0.0;

    sead::Color4f c;
    c.r = 0.1;
    c.g = 0.5;
    c.b = 0.1;
    c.a = 0.9;

    agl::utl::DevTools::beginDrawImm(context, sead::Matrix34<float>::ident, sead::Matrix44<float>::ident);
    agl::utl::DevTools::drawTriangleImm(context, p1, p2, p3, c);
    agl::utl::DevTools::drawTriangleImm(context, p3, p4, p2, c);
}

namespace al {
    void setRenderBuffer(al::LayoutKit*, const agl::RenderBuffer*);
}

void drawDebugMenu(HakoniwaSequence *curSequence, sead::Viewport *viewport, agl::DrawContext *drawContext) {
    al::executeDraw(curSequence->mLytKit, "２Ｄベース（メイン画面）");
    al::executeDraw(curSequence->mLytKit, "２Ｄオーバー（メイン画面）");

    int dispWidth = al::getLayoutDisplayWidth();
    int dispHeight = al::getLayoutDisplayHeight();

    textWriter->mViewport = viewport;

    textWriter->mColor = sead::Color4f(
        1.f,
        1.f,
        1.f,
        0.8f);

//    drawBackground((agl::DrawContext *)drawContext);
//
//    textWriter->beginDraw();
//
//    textWriter->setCursorFromTopLeft(sead::Vector2f(10.f, ((float)dispHeight / 3.0f) + 30.f));
//
//    textWriter->setScaleFromFontHeight(20.f);
//
//    textWriter->endDraw();
}

void DrawDebugMenu::Callback(HakoniwaSequence* sequence) {
    Orig(sequence);
    auto* drawInfo = sequence->getDrawInfo();
//    sead::Viewport viewport(*drawInfo->mSecondRenderBuffer);
//    viewport.apply(drawInfo->mDrawContext, *drawInfo->mSecondRenderBuffer);
//    drawInfo->mSecondRenderBuffer->bind(drawInfo->mDrawContext);
//    al::setRenderBuffer(sequence->mLytKit, drawInfo->mSecondRenderBuffer);

//    textWriter->mViewport = &viewport;
//    textWriter->mColor = sead::Color4f(1.f, 1.f, 1.f, 0.8f);
//    drawBackground(drawInfo->mDrawContext);
//    textWriter->beginDraw();
//    textWriter->setCursorFromTopLeft(sead::Vector2f(10.0f, 720.0f - 100.0f));
//    textWriter->setScaleFromFontHeight(20.f);
//
//    textWriter->printf("Amongla swag\n");
//
//    textWriter->endDraw();
}
