#pragma once

#include "al/factory/Factory.h"
#include "al/scene/Scene.h"

namespace alSceneFunction {
typedef al::Scene* (*sceneCreator)();

class SceneFactory : public al::Factory<sceneCreator> {
public:
    SceneFactory();
};
}  // namespace alSceneFunction