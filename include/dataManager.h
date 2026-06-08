#pragma once

#include "commonTypes.h"
#include <vector>
#include <string>
#include <unordered_map>

extern std::unordered_map<std::string,std::vector<lopHoc>> khoDuLieu;
void napData(std::string duongDan);

std::vector<lopHoc> layDanhSachLopTheoMon(std::string maHP);
void luuTrangThaiNguoiDung(std::vector<std::string> dsMonDangChon);
std::vector<std::string> taiTrangThaiNguoiDung();

