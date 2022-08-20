#pragma once


namespace al {
    class ISceneObj {
        public:
            virtual const char* getSceneObjName(void) const = 0;
            virtual ~ISceneObj();
            virtual void initAfterPlacementSceneObj(struct ActorInitInfo const&) {}
            virtual void initSceneObj(void) {}
    };
}