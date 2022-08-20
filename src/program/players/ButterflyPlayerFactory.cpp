#include "players/ButterflyPlayerFactory.hpp"
#include "al/factory/Factory.h"
#include "game/Player/PlayerActorBase.h"
#include "players/ClashingBird.hpp"

template <class T>
static PlayerActorBase* createCustomPlayer(const char* name) {
    return new T(name);
}

template <class T>
PlayerActorBase* createPlayerFunction(const char* name);

class PlayerActorHakoniwa;
class YukimaruRacePlayer;

al::NameToCreator<playerCreator> actorTable[] = {
    {"ClashingBird", &createCustomPlayer<ClashingBird>},
    {"PlayerActorHakoniwa", &createPlayerFunction<PlayerActorHakoniwa>},
    {"YukimaruRacePlayer", &createPlayerFunction<YukimaruRacePlayer>}
};

ButterflyPlayerFactory::ButterflyPlayerFactory() : al::Factory<playerCreator>() {
    factoryName = "AmonglaButterflies";
    factoryCount = 3;
    creatorTable = actorTable;
}


