#pragma once

#include "al/factory/Factory.h"
#include "game/Player/PlayerActorBase.h"

typedef PlayerActorBase* (*playerCreator)(const char*);

class ButterflyPlayerFactory : public al::Factory<playerCreator> {
public:
    ButterflyPlayerFactory();
    const char* convertName(const char* name) const override {
        // if (al::isEqualString(name, "PlayerActorHakoniwa") && al::isPadHoldZR(-1)) {
        return "ClashingBird";
        // }
        // return name;
    }
};