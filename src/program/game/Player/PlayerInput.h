#pragma once

#include <math/seadVector.h>

namespace al {
class LiveActor;
}
class IUsePlayerCollision;
class IUseDimension;

class PlayerInput {
public:
    PlayerInput(const al::LiveActor*, const IUsePlayerCollision*, const IUseDimension*);
    void calcMoveInput(sead::Vector3<float>* result, const sead::Vector3<float>& gravity) const;
    bool isTriggerJump() const;
    bool isHoldJump() const;
    bool isMove(void) const;
    bool isMoveDeepDown(void) const;
    bool isMoveDeepDownNoSnap(void) const;
    bool isNoInput(void) const;
private:
    char detail[0x140];
};