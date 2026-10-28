#pragma once

#include <vector>
#include <filesystem>

class Note{
    int tone;
    int duration;
    bool silent;
    Note(int tone, int duration, bool silent = false);
    std::vector<Note> load(std::filesystem::path path);
};

