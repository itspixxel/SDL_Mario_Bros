#pragma once
#include "AudioManager.h"

class SoundEffect
{
    private:
        AudioManager* m_audio_manager;
        Mix_Chunk* m_sound;
        int m_last_channel;
        int m_preferred_channel;

    public:
        SoundEffect(AudioManager* audio_manager, std::string path, int preferred_channel);
        ~SoundEffect();

        void Play(int loops = 0);
        void Stop();

        void SetPreferredChannel(int channel) { this->m_preferred_channel = channel; }
        bool IsLoaded() { return this->m_sound != nullptr; }
};