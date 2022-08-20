#pragma once

namespace agl {
class DrawContext;
}

namespace al {
class FontHolder;
class LayoutSystem;
class LayoutKit {
public:
    LayoutKit(al::FontHolder*);
    void createCameraParamForIcon();
    void createExecuteDirector(int);
    void createEffectSystem();
    void endInit();
    void update();
    void draw(const char*);
    void drawList(const char*, const char*);
    void setLayoutSystem(al::LayoutSystem*);
    void setDrawContext(agl::DrawContext*);
};
}  // namespace al