#ifndef CPPGAME_SYNTHS_H
#define CPPGAME_SYNTHS_H

#include <windows.h>
#include <mmsystem.h>
#include <cmath>
#include <vector>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <thread>
#include <audioclient.h>
#include <mmdeviceapi.h>
#include <algorithm>

class Synths{
public:
    const static inline int rate = 44100;
    const static inline float half_tone = std::pow(2, 1.0f / 12.0f);
    static inline float seconds_per_beats = 0.1f;

    static inline IMMDeviceEnumerator* pEnumerator = nullptr;
    static inline IMMDevice* pDevice = nullptr;
    static inline IAudioClient* pAudioClient = nullptr;
    static inline IAudioRenderClient* pRenderClient = nullptr;
    static inline WAVEFORMATEX* pWaveFormat = nullptr;

    static void init();
    static std::vector<short> get_sin_wave(int tone, int beats);
    static std::vector<short> load_wav(std::filesystem::path& path);
    static std::vector<short> load_wav(std::string path);
    static std::vector<short> load_wav(const char* path);
    static void play_sound(std::vector<short> sound_arr, bool loop = false);
};

bool LoadWavAsShorts(std::filesystem::path& path, std::vector<short>& output, WAVEFORMATEX& output_fmt);
void PlayShortsVector(const std::vector<short>& samples, const WAVEFORMATEX& fmt, bool loop = false); 
#endif