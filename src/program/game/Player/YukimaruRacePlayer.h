#pragma once

#include "game/Interfaces/IUseDimension.h"
#include "PlayerActorBase.h"
#include "PlayerPuppet.h"
#include "PlayerInput.h"
#include "PlayerAnimator.h"
#include "HackCap.h"
#include "PlayerModelKeeper.h"
#include "PlayerColliderHakoniwa.h"
#include "PlayerConst.h"
#include "PlayerHackKeeper.h"
#include "PlayerInfo.h"
#include "PlayerInitInfo.h"

namespace al {
    class WipeSimple;
    class AnimScaleController;
}

class YukimaruInput {
    public:
    int *whatever;
};

class YukimaruStateMove {
    public:
    char unk[0x18]; // inherits
    al::LiveActor *mRacePlayer;
    YukimaruInput *mInput; // 20
    sead::Quatf *quat; // 28
    sead::Matrix34f bounceNrmMtx; // 30
    sead::Vector3f addVel; // 60
    sead::Vector3f collidedNormalSum; // 6C
    float something; // 78
    float something2; // 7C
    float something3; // 80
    int something4; // 84
    int something5; // 88
    int something6; // 8C
    int something7; // 90
    int something8; // 94
    int something9; // 98
    float bounceVelocity; // 9C
    int type; // A0
    bool isJump; // A4
    bool hackOrEnemy; // A5
    al::AnimScaleController *scaleController; // A8
    al::AnimScaleController *scaleController2; // B0
};

class YukimaruRacePlayer : public PlayerActorBase, public YukimaruInput {
    public:
    void initPlayer(al::ActorInitInfo const &, PlayerInitInfo const &);

    char unk[0x8]; // unknown
    PlayerInput *mPlayerInput;
    sead::Quatf quat;
    sead::Quatf quat2;
    sead::Quatf quat3;
    sead::Vector3f trans;
    sead::Vector3f endPos; // might be the last respawn point?
    YukimaruStateMove *mStateMove;
    al::WipeSimple *endWipe;
    sead::Vector3f trans3;
    sead::Vector3f respawnPoint;
    int timePassed;
    bool isTutorial; // might be a pointer
};