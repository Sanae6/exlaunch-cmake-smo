#pragma once
#include "game/Player/Interfaces/IUsePlayerPuppet.h"

class ClashingBird;

class ButterflyPlayerPuppet : public IUsePlayerPuppet {
public:
    ButterflyPlayerPuppet(ClashingBird*);

    void start(al::HitSensor*, al::HitSensor*) override;
    void end() override;
    void cancel() override;
    void setTrans(const sead::Vector3f&) override;
    void setPose(const sead::Quatf&) override;
    void setVelocity(const sead::Vector3f&) override;
    void resetPosition(const sead::Vector3f&) override;
    sead::Vector3f& getTrans() const override;
    sead::Vector3f& getVelocity() const override;
    sead::Vector3f& getGravity() const override;
    void calcFront(sead::Vector3f*) const override;
    void calcUp(sead::Vector3f*) const override;
    void startAction(sead::SafeString const&) const override;
    bool isActionEnd() const override;
    bool isActionPlaying(char const*) const override;
    void setAnimRate(float) const override;
    int getAnimFrameMax() const override;
    void hide() override;
    void show() override;
    bool isHidden() const override;
    void hideSilhouette() override;
    void showSilhouette() override;
    void hideShadow() override;
    void showShadow() override;
    void requestDamage() override;
    void clearRequestDamage() override;
    bool isRequestDamage() const override;
    void setBindEndOnGround() override;
    bool isBindEndOnGround() const override;
    void setBindEndJump(const sead::Vector3f&, int) override;
    bool isBindEndJump() const override;
    void validateCollisionCheck() override;
    void invalidateCollisionCheck() override;
    bool isValidCollisionCheck() override;
    bool isCollidedGround() override;
    sead::Vector3f& getCollidedGroundNormal() override;
    void validateSensor() override;
    void invalidateSensor() override;

private:
    ClashingBird* mPlayer;
};