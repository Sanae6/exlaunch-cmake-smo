#pragma once

#include <basis/seadTypes.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <gfx/seadProjection.h>
#include "math/seadBoundBox.h"

namespace sead {
class OrthoProjection : public Projection {
    SEAD_RTTI_OVERRIDE(OrthoProjection, Projection);

public:
    OrthoProjection();
    ~OrthoProjection() override;

    float getNear();
    float getFar();
    float getFovy();
    float getAspect();
    float getOffset();

    u32 getProjectionType() const override;
    void doUpdateMatrix(Matrix44f* mtx) const override;
    void doUpdateDeviceMatrix(Matrix44f*, const Matrix44f&, Graphics::DevicePosture) const override;
    void doScreenPosToCameraPosTo(Vector3f*, const Vector3f&) const override;

private:
    float near, far;
    float top, bottom, left, right;
};
}