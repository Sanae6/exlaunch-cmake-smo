#pragma once

namespace al {
class AudioDirector;
class Sequence;
class AudioSystemInfo;
class AudioDirectorInitInfo;

void initAudioDirector(al::Sequence*, al::AudioSystemInfo*, al::AudioDirectorInitInfo&);
};  // namespace al