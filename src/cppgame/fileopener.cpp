#include <string>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <filesystem>
#include "include/fileopener.h"

std::string getFileContents(const std::string& path){
    std::ifstream in(path, std::ios::binary);
	if (!in){
        throw(errno);
    }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

std::string getFileContents(const char* path){
    std::ifstream in(path, std::ios::binary);
	if (!in){
        throw(errno);
    }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}

std::string getFileContents(const std::filesystem::path& path){
    std::ifstream in(path, std::ios::binary);
	if (!in){
        throw(errno);
    }
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return contents;
}