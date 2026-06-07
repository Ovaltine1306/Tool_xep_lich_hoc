#pragma once

#include"commonTypes.h"
#include<unordered_map>
#include<vector>
#include<string>
#include<regex>

bool kiemTraTrungGio(const lopHoc& lop, const std::vector<lopHoc>& lichHienTai);
void parsePeriodString(const std::string& periodStr, int& start, int& end);
bool kiemTraDieuKienLoc(const lopHoc& lop, const dieuKienLoc& dieuKien);