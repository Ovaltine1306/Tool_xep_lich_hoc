#pragma once // Đảm bảo header sẽ chỉ bị gọi 1 lần

#include<vector>
#include<string>
#include"commonTypes.h"

void xepLich(int index, std::vector<std::vector<lopHoc>>& dsCacNhomTheoMaMon, std::vector<lopHoc>& lichHienTai, std::vector<phuongAn>& result, dieuKienLoc& dieuKien);

std::vector<phuongAn> taoTKB(std::vector<std::string>& dsMaMon, dieuKienLoc& dieuKien);