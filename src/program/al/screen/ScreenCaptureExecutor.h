#pragma once

#include <heap/seadHeap.h>
#include <container/seadPtrArray.h>

namespace agl {
class DrawContext;
class RenderBuffer;
}  // namespace agl

namespace al {
class ScreenCapture;
class ScreenCaptureExecutor {
public:
    ScreenCaptureExecutor(int);
    ~ScreenCaptureExecutor();
    al::ScreenCapture* createScreenCapture(int, int, int);
    void tryCaptureAndDraw(agl::DrawContext*, const agl::RenderBuffer*, int);
    bool isDraw(int);
    void draw(agl::DrawContext*, const agl::RenderBuffer*, int);
    void tryCapture(agl::DrawContext*, const agl::RenderBuffer*, int);
    void requestCapture(bool, int);
    void onDraw(int);
    void offDraw(int);
    void offDraw();

private:
    sead::PtrArray<ScreenCapture> mScreenCaptures;
    bool mOn;
};
}  // namespace al