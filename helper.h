//
// Created by 韩孟娇 on 2/18/18.
//

#ifndef RAW2SWC_HELPER_H
#define RAW2SWC_HELPER_H

#include <iostream>
#include <vector>

struct vec3f{
    float x, y, z;
};

struct vec4f{
    float x, y, z, w;
};

struct CommandLine{
    CommandLine(int argc, const char** argv);
    std::vector<std::string> inputFiles;
    std::string outputFile;
};

inline CommandLine::CommandLine(int argc, const char** argv){
    for(int i = 1; i < argc; i++){
        const std::string arg = argv[i];
        if(arg == "--output"){
            outputFile = argv[++i];
        }else{
            inputFiles.push_back(arg);
        }
    }
}

struct swcFile{
    std::vector<int> index;
    std::vector<int> component;
    std::vector<vec3f> position;
    std::vector<float> radius;
    std::vector<int> preIndex;
    std::vector<vec4f> color;
};

#endif //RAW2SWC_HELPER_H
