#include "al/scene/Scene.h"
#include "al/scene/SceneFactory.h"

typedef al::Scene* (*sceneCreator)();

class AmonglaSceneFactory : public alSceneFunction::SceneFactory {
public:
    AmonglaSceneFactory();
};