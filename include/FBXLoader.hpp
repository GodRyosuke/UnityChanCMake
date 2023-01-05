#pragma once

#include <string>

class FBXLoader {
public:
    FBXLoader();
    bool Load(std::string filePath);
    
};