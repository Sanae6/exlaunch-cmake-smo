#include "players/ClashingBird.hpp"
#include "al/util/ControllerUtil.h"
#include "al/util/LiveActorUtil.h"
#include "al/util/MathUtil.h"
#include "al/util/NerveUtil.h"
#include "al/util/RandomUtil.h"
#include "game/Player/PlayerActorBase.h"
#include "game/Player/PlayerInput.h"
#include "logging/logger.hpp"
#include "players/ButterflyPlayerPuppet.hpp"

namespace {
NERVE_HEADER(ClashingBird, Play);
NERVE_HEADER(ClashingBird, Puppet);
NERVE_IMPL(ClashingBird, Play);
NERVE_IMPL(ClashingBird, Puppet);
}  // namespace

ClashingBird::ClashingBird(const char* actorName) : PlayerActorBase(actorName) {}

void ClashingBird::initPlayer(const al::ActorInitInfo& actorInitInfo,
                              const PlayerInitInfo& playerInitInfo) {
    al::initActorWithArchiveName(this, actorInitInfo, "BirdClash", "Player");
    rs::initPlayerActorInfo(this, playerInitInfo);

    al::initNerve(this, &nrvClashingBirdPlay, 0);

    this->makeActorAlive();
    mPlayerInput = new PlayerInput(this, nullptr, nullptr);
    mPlayerPuppet = new ButterflyPlayerPuppet(this);
    // mPlayerHackKeeper = new PlayerHackKeeper();
}

namespace al {
    struct ComboCounter {
        ComboCounter() : mCounter(0) {}
        virtual void increment() {
            mCounter++;
        }
        int mCounter;
    };
    bool sendMsgPlayerReflectOrTrample(al::HitSensor*, al::HitSensor*, al::ComboCounter*);
}
namespace rs {
void sendMsgStartHack(al::HitSensor*, al::HitSensor*);
}

void ClashingBird::attackSensor(al::HitSensor* source, al::HitSensor* target) {
    al::ComboCounter counter;
    al::sendMsgPlayerReflectOrTrample(target, source, &counter);

}

bool ClashingBird::receiveMsg(const al::SensorMsg* sensor, al::HitSensor* left,
                              al::HitSensor* right) {
    return this->receivePushMsg(sensor, left, right, 1.0f);
}

void ClashingBird::movement() {
    PlayerActorBase::movement();

    if (al::isOnGround(this, 0)) {
        al::setActionFrameRate(this, 1);
//        sead::Vector3f& normal = al::getOnGroundNormal(this, 0);
//        al::addVelocity(this, sead::Vector3f(normal.x, normal.y, normal.z));

        if ((!al::isActionPlaying(this, "GroundWaitA") &&
            !al::isActionPlaying(this, "GroundWaitB")) || al::isActionEnd(this)) {
            al::startAction(this, al::isHalfProbability() ? "GroundWaitA" : "GroundWaitB");
        }
    } else {
        al::addVelocityY(this, -0.5f);
        al::scaleVelocity(this, 0.98f);
        al::setActionFrameRate(this, al::getVelocity(this).y * 0.5f);

        sead::Vector3f pos;
        mPlayerInput->calcMoveInput(&pos, -al::getGravity(this));
        if (al::isNearZero(al::getVelocity(this).y, 20.0f)) {
            float yVel = sead::MathCalcCommon<float>::abs(al::getVelocity(this).y);
            pos *= 20.0f - yVel;
        }
        pos.y = 0;
        al::turnToTarget(this, al::getTrans(this) + pos, 5.0f);
        al::getTrans(this) += pos;
    }

    updateCollider();
}

void ClashingBird::updateCollider() {
    sead::Vector3f& velocity = al::getVelocity(this);
    sead::Vector3f result = al::getActorCollider(this)->collide(velocity);
    *al::getTransPtr(this) += result;
    result = al::getTrans(this);
}

IUsePlayerPuppet* ClashingBird::getPlayerPuppet() {
    return mPlayerPuppet;
}

void ClashingBird::startDemoPuppetable() {
    Logger::log("start demo puppetable\n");
    al::setVelocity(this, sead::Vector3f::zero);
    al::setNerve(this, &nrvClashingBirdPuppet);
}

void ClashingBird::endDemoPuppetable() {
    Logger::log("end demo puppetable\n");
    al::setNerve(this, &nrvClashingBirdPlay);
}

void ClashingBird::startDemoShineGet() {}
void ClashingBird::endDemoShineGet() {}
void ClashingBird::startDemoMainShineGet() {}
void ClashingBird::endDemoMainShineGet() {}
void ClashingBird::startDemoHack() {}
void ClashingBird::endDemoHack() {}
void ClashingBird::startDemoKeepBind() {
    Logger::log("start demo keep bind\n");
    startDemoPuppetable();
}
void ClashingBird::noticeDemoKeepBindExecute() {
    Logger::log("start demo puppetable\n");
}
void ClashingBird::endDemoKeepBind() {
    Logger::log("end demo keep bind\n");
    endDemoPuppetable();
}
void ClashingBird::startDemoKeepCarry() {}
void ClashingBird::endDemoKeepCarry() {}

void ClashingBird::exePlay() {
    if (mPlayerInput->isTriggerJump()) {
        if (al::isOnGround(this, 0))
            al::setVelocityY(this, 8.0f);
        else
            al::addVelocityY(this, 8.0f);
        al::startAction(this, "Fly");
    }
}

void ClashingBird::exePuppet() {

}
