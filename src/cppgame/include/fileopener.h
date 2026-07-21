#ifndef FILE_OPENER_H
#define FILE_OPENER_H
#include <string>
#include <filesystem>

std::string getFileContents(const std::string& path);
std::string getFileContents(const char* path);
std::string getFileContents(const std::filesystem::path& path);

#endif