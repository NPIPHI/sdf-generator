#pragma once

#include <string>
#include <vector>

std::string getFileContents(const std::string& file_name);
std::vector<unsigned char> getFileRaw(const std::string& file_name);