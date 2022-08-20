#pragma once

#include "al/util/NerveUtil.h"
#include "game/Interfaces/IUseDimension.h"
#include "game/Interfaces/IUsePlayerHack.h"
#include "game/Player/PlayerActorBase.h"
#include "players/ButterflyPlayerPuppet.hpp"

class ClashingBird : public PlayerActorBase /* , public IUseDimension  */ {
public:
    ClashingBird(const char*);
    void initPlayer(const al::ActorInitInfo&, const PlayerInitInfo&) override;
    void attackSensor(al::HitSensor* source, al::HitSensor* target) override;
    bool receiveMsg(const al::SensorMsg*, al::HitSensor*, al::HitSensor*) override;
    void movement() override;
    void updateCollider() override;
    IUsePlayerPuppet* getPlayerPuppet() override;
    bool isEnableDemo() override { return true; }
    void startDemoPuppetable() override;
    void endDemoPuppetable() override;
    void startDemoShineGet() override;
    void endDemoShineGet() override;
    void startDemoMainShineGet() override;
    void endDemoMainShineGet() override;
    void startDemoHack() override;
    void endDemoHack() override;
    void startDemoKeepBind() override;
    void noticeDemoKeepBindExecute() override;
    void endDemoKeepBind() override;
    void startDemoKeepCarry() override;
    void endDemoKeepCarry() override;

    // PlayerHackKeeper* getPlayerHackKeeper() const override { return mPlayerHackKeeper; }
    // ActorDimensionKeeper *getActorDimensionKeeper() const override { return
    // mActorDimensionKeeper; }

    void exePlay();
    void exePuppet();

private:
    PlayerInput* mPlayerInput;
    PlayerHackKeeper* mPlayerHackKeeper;
    ActorDimensionKeeper* mActorDimensionKeeper;
    ButterflyPlayerPuppet* mPlayerPuppet;
    class BindState {
        al::HitSensor* ownBindSensor;
        al::HitSensor* boundHitSensor;
    } mBindState;
};