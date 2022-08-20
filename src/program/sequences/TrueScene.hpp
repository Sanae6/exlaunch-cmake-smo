#pragma once

#include "al/scene/Scene.h"

class TrueScene : public al::Scene {
public:
    TrueScene();
    void init(const al::SceneInitInfo & initInfo) override;
    
};