#pragma once

#include "heap/seadDisposer.h"
namespace sead {

class Graphics : public IDisposer {
    SEAD_SINGLETON_DISPOSER(Graphics)
    Graphics();
    ~Graphics();
public:
};

}