//
// Created by 16182 on 7/16/2020.
//

#include "io.hpp"
#include<string>
#include<sstream>
#include<fstream>

std::string getFileContents(const std::string& file_name) {
    std::ifstream file(file_name);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<unsigned char> getFileRaw(const std::string &file_name) {
    std::ifstream file(file_name, std::ios::binary | std::ios::ate);
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);
    std::vector<unsigned char> buffer(size);
    if (file.read(reinterpret_cast<char *>(buffer.data()), size))
    {
        return buffer;
    } else {
        printf("Failed to open %s\n", file_name.c_str());
        return {};
    }
}
