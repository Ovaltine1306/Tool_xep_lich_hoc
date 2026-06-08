#pragma once

#include "commonTypes.h"
#include <string>
#include <vector>
#include <unordered_map>

std::unordered_map<std::string,std::vector<lopHoc>> docFileCSV(std::string duongDan);
std::vector<int> phanTichTuanHoc(std::string tuan);