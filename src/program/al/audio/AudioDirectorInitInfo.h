#pragma once

#include "al/audio/BgmDirectorInitInfo.h"
#include "al/audio/SeDirectorInitInfo.h"
#include "types.h"

namespace al {
class AudioSystemInfo;
class AudioDirectorInitInfo {
public:
    AudioSystemInfo* mAudioSystemInfo;
    s64 unknown_0x8;
    char* mCurrentStage;
    s32 unknown_0x18;
    s64 unknown_0x20;
    SeDirectorInitInfo mSeDirectorInitInfo;
    BgmDirectorInitInfo mBgmDirectorInitInfo;
    char* mDuckingName;
};
}  // namespace al