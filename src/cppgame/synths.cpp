#include "include/synths.h"

bool isInteger(float f) {
    return std::trunc(f) == f;
}

void Synths::init(){
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (FAILED(hr)) return;

    // 2. Create the device enumerator
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pEnumerator);
    if (FAILED(hr)) throw std::runtime_error("f1");

    // 3. Get the default audio rendering endpoint (speakers/headphones)
    hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
    if (FAILED(hr)) throw std::runtime_error("f2");

    // 4. Activate the audio client from the device
    hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, nullptr, (void**)&pAudioClient);
    if (FAILED(hr)) throw std::runtime_error("f3");

    // 5. Get the preferred system mixing format (usually 32-bit float or 16-bit PCM)
    hr = pAudioClient->GetMixFormat(&pWaveFormat);
    if (FAILED(hr)) throw std::runtime_error("f4");

    REFERENCE_TIME hnsRequestedDuration = 10000000; 
    hr = pAudioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, hnsRequestedDuration, 0, pWaveFormat, nullptr);

    UINT32 bufferFrameCount;
    hr = pAudioClient->GetBufferSize(&bufferFrameCount);

    hr = pAudioClient->GetService(__uuidof(IAudioRenderClient), (void**)&pRenderClient);
}

std::vector<short> Synths::get_sin_wave(int tone, int beats){
    float float_lenght = (beats * rate * seconds_per_beats); 
    if (!isInteger(float_lenght))
        throw std::runtime_error("CPPGAME::SYNTHS given beats, rate, and seconds_per_beats does not give whole number of samples.");
    if (float_lenght > ULLONG_MAX)
        throw std::runtime_error("CPPGAME::SYNTHS given beats, rate, and seconds_per_beats does give number of samples more than can be stored in unsigned long long.");
    unsigned long long lenght = (unsigned long long)(float_lenght);
    std::vector<short> result;
    result.resize(lenght);
    for (unsigned long long i = 0; i < lenght; i++){
        result[i] = std::sin(i);
    }
    return result;
}

std::vector<short> Synths::load_wav(std::filesystem::path& path){
    std::vector<short> result;
    WAVEFORMATEX fmt;
    bool good = LoadWavAsShorts(path, result, fmt);
    if (!good){
        std::cout << "can not load music. :(\r\n";
    }
    return result;
}
std::vector<short> Synths::load_wav(const char* path){
    std::filesystem::path p = std::filesystem::path(path);
    return load_wav(p);
}

std::vector<short> Synths::load_wav(std::string path){
    std::filesystem::path p = std::filesystem::path(path);
    return load_wav(p);
}


void Synths::play_sound(std::vector<short> sound_arr, bool loop){
    WAVEFORMATEX fmt;
    fmt.wFormatTag = WAVE_FORMAT_PCM;
    fmt.nChannels = 2;
    fmt.nSamplesPerSec = rate;
    fmt.nAvgBytesPerSec = rate * 4;
    fmt.nBlockAlign = 4;
    fmt.wBitsPerSample = 16;
    fmt.cbSize = 0;
    // if (sound_arr.size() < 44100){
    //     for (unsigned i = 0; i < 44100 - sound_arr.size(); i++){
    //         sound_arr.push_back(0);
    //     }
    // }
    if (!pAudioClient || !pRenderClient) {
        try {
            init();
        } catch (const std::exception& e) {
            std::cerr << "Synths audio init failed: " << e.what() << "\n";
            return;
        }
    }

    if (!pAudioClient || !pRenderClient) {
        std::cerr << "Synths audio client not initialized.\n";
        return;
    }
    std::thread audioThread(PlayShortsVector, sound_arr, fmt, loop);
    audioThread.detach();
}

bool LoadWavAsShorts(std::filesystem::path& path, std::vector<short>& output, WAVEFORMATEX& output_fmt) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) return false;

    char riff[4];
    file.read(riff, 4);
    if (std::strncmp(riff, "RIFF", 4) != 0) return false;

    int fileSize;
    file.read((char*)(&fileSize), 4);

    char wave[4];
    file.read(wave, 4);
    if (std::strncmp(wave, "WAVE", 4) != 0) return false;

    bool fmt_found = false;
    bool data_found = false;

    while (file.read(riff, 4)) {
        int chunkSize;
        file.read((char*)(&chunkSize), 4);

        if (std::strncmp(riff, "fmt ", 4) == 0) {
            if (sizeof(WAVEFORMATEX) >= chunkSize){
                file.read((char*)(&output_fmt), sizeof(WAVEFORMATEX));
                // Skip any extra format bytes if chunk is larger than standard PCMWAVEFORMAT
                file.seekg(chunkSize - sizeof(WAVEFORMATEX), std::ios::cur);
            }
            else{
                file.read((char*)(&output_fmt), chunkSize);
            }
            fmt_found = true;
        } 
        else if (std::strncmp(riff, "data", 4) == 0) {
            output.resize(chunkSize / sizeof(short));
            file.read((char*)(output.data()), chunkSize);
            data_found = true;
            break;
        } 
        else {
            file.seekg(chunkSize, std::ios::cur);
        }
    }

    return fmt_found && data_found && (output_fmt.wBitsPerSample == 16);
}

void PlayShortsVector(const std::vector<short>& samples, const WAVEFORMATEX& fmt, bool loop) {
    HWAVEOUT CPPGAME_SYNTHS_HWAVEOUT = 0;
    int res = waveOutOpen(&CPPGAME_SYNTHS_HWAVEOUT, WAVE_MAPPER, &fmt, 0, 0, CALLBACK_FUNCTION|WAVE_ALLOWSYNC);
    if (res != MMSYSERR_NOERROR) {
        std::cerr << "Failed to open audio output device.\n" << res << "\n";
        return;
    }
    HANDLE hEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    ResetEvent(hEvent);
    WAVEHDR waveHdr = {};
    waveHdr.lpData = const_cast<LPSTR>(reinterpret_cast<LPCSTR>(samples.data()));
    waveHdr.dwBufferLength = static_cast<DWORD>((samples.size()) * sizeof(short));
    if (loop){
        waveHdr.dwFlags = WHDR_BEGINLOOP | WHDR_ENDLOOP;
        waveHdr.dwLoops = 0xFFFF; // Number of loops
    }
    waveOutPrepareHeader(CPPGAME_SYNTHS_HWAVEOUT, &waveHdr, sizeof(WAVEHDR));
    waveOutWrite(CPPGAME_SYNTHS_HWAVEOUT, &waveHdr, sizeof(WAVEHDR));
    
    // Wait for playback to finish
    while (!(waveHdr.dwFlags & WHDR_DONE)) {
        Sleep(50);
    }

    waveOutUnprepareHeader(CPPGAME_SYNTHS_HWAVEOUT, &waveHdr, sizeof(WAVEHDR));
    waveOutClose(CPPGAME_SYNTHS_HWAVEOUT);
    CloseHandle(hEvent);
}