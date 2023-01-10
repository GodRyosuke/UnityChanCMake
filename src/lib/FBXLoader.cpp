#include "FBXLoader.hpp"

#include <fstream>
#include <iostream>

FBXLoader::FBXLoader() 
{

}

bool FBXLoader::Load(std::string filePath)
{
    std::ifstream ifs;
    ifs.open(filePath, std::ios::in | std::ios::binary);
    if (ifs.fail()) {
        printf("[FBXLoader] error: failed to Load %s\n", filePath.c_str());
        return false;
    }

    // ヘッダの読み出し
    {
        std::string headerStr = "";
        for (int i = 0; i < 18; i++) {
            char c;
            ifs.read(&c, sizeof(char));
            headerStr += c;
        }
        if (headerStr != "Kaydara FBX Binary") {
            printf("error: This FBX file does not FBX Binary\n");
            return false;
        }
    }

    int count = 0;
    while (!ifs.eof()) {
        char c;
        ifs.read((char*)&c, sizeof(char));
        if (c == 'F') {
            int x = 0;
        }
        count++;
    }
    ifs.close();

    // std::string lineStr;
    // while (getline(ifs, lineStr)) {

    // }
    
    return true;
}

