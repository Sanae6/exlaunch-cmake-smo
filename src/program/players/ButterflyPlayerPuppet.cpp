#include "players/ButterflyPlayerPuppet.hpp"
#include "al/util/LiveActorUtil.h"

#include "players/ClashingBird.hpp"

ButterflyPlayerPuppet::ButterflyPlayerPuppet(ClashingBird* player) : mPlayer(player) {}
void ButterflyPlayerPuppet::start(al::HitSensor*, al::HitSensor*){};
void ButterflyPlayerPuppet::end(){};
void ButterflyPlayerPuppet::cancel(){};
void ButterflyPlayerPuppet::setTrans(const sead::Vector3f&){};
void ButterflyPlayerPuppet::setPose(const sead::Quatf&){};
void ButterflyPlayerPuppet::setVelocity(const sead::Vector3f&){};
void ButterflyPlayerPuppet::resetPosition(const sead::Vector3f&){};
sead::Vector3f& ButterflyPlayerPuppet::getTrans() const {
    return al::getTrans(mPlayer);
};
sead::Vector3f& ButterflyPlayerPuppet::getVelocity() const {
    return al::getVelocity(mPlayer);
};
sead::Vector3f& ButterflyPlayerPuppet::getGravity() const {
    return al::getGravity(mPlayer);
};
void ButterflyPlayerPuppet::calcFront(sead::Vector3f*) const {};
void ButterflyPlayerPuppet::calcUp(sead::Vector3f*) const {};
void ButterflyPlayerPuppet::startAction(sead::SafeString const&) const {};
bool ButterflyPlayerPuppet::isActionEnd() const {return true;};
bool ButterflyPlayerPuppet::isActionPlaying(char const*) const {return false;};
void ButterflyPlayerPuppet::setAnimRate(float) const {};
int ButterflyPlayerPuppet::getAnimFrameMax() const {return 1;};
void ButterflyPlayerPuppet::hide(){};
void ButterflyPlayerPuppet::show(){};
bool ButterflyPlayerPuppet::isHidden() const {return false;};
void ButterflyPlayerPuppet::hideSilhouette(){};
void ButterflyPlayerPuppet::showSilhouette(){};
void ButterflyPlayerPuppet::hideShadow(){};
void ButterflyPlayerPuppet::showShadow(){};
void ButterflyPlayerPuppet::requestDamage(){};
void ButterflyPlayerPuppet::clearRequestDamage(){};
bool ButterflyPlayerPuppet::isRequestDamage() const {return true;};
void ButterflyPlayerPuppet::setBindEndOnGround(){};
bool ButterflyPlayerPuppet::isBindEndOnGround() const {return true;};
void ButterflyPlayerPuppet::setBindEndJump(const sead::Vector3f&, int){};
bool ButterflyPlayerPuppet::isBindEndJump() const {return false;};
void ButterflyPlayerPuppet::validateCollisionCheck(){};
void ButterflyPlayerPuppet::invalidateCollisionCheck(){};
bool ButterflyPlayerPuppet::isValidCollisionCheck(){};
bool ButterflyPlayerPuppet::isCollidedGround(){return false;};
sead::Vector3f& ButterflyPlayerPuppet::getCollidedGroundNormal() {
    return al::getOnGroundNormal(mPlayer, 0);
};
void ButterflyPlayerPuppet::validateSensor(){};
void ButterflyPlayerPuppet::invalidateSensor(){};