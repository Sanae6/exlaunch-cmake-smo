#include "game/GameData/GameDataHolderBase.h"

class AmonglaGameDataHolder : public al::GameDataHolderBase {
public:
    AmonglaGameDataHolder(al::MessageSystem*);

    const char* getSceneObjName(void) const override {
        return "GameDataHodler";
    }
    al::MessageSystem* getMessageSystem() const override {
        return mMessageSystem;
    }

private:
    al::MessageSystem* mMessageSystem;
};