#include<iostream>
#include"../include/conflictDetector.h"
#include"../include/dataManager.h"


bool kiemTraTrungGio(const lopHoc& lop, const std::vector<lopHoc>& lichHienTai){
    int length = lichHienTai.size();
    for (int i = 0; i < length; i++) { //loop qua lịch học tất cả các môn hiện tại
        if(lop.thu != lichHienTai[i].thu) continue;

        if(lop.tietKetThuc < lichHienTai[i].tietBatDau || lop.tietBatDau > lichHienTai[i].tietKetThuc) continue;
        for (int index1 = 0; index1 < lop.tuanHoc.size(); index1++) {
            for (int index2 = 0; index2 < lichHienTai[i].tuanHoc.size(); index2++) {
                if(lop.tuanHoc[index1] == lichHienTai[i].tuanHoc[index2]) return true;
            }
        }
    }
    return false;
}
void parsePeriodString(const std::string& periodStr, int& start, int& end) {
    size_t dash = periodStr.find('-');
    if (dash != std::string::npos) {
        start = std::stoi(periodStr.substr(0, dash));
        end = std::stoi(periodStr.substr(dash + 1));
    } else {
        start = std::stoi(periodStr);
        end = std::stoi(periodStr);
    }
}

bool kiemTraDieuKienLoc(const lopHoc& lop, const dieuKienLoc& dieuKien) {
    // 1. LỌC THEO KHOẢNG TIẾT HỌC CẤU HÌNH
    // Loại ngay nếu tiết bắt đầu sớm hơn hoặc tiết kết thúc muộn hơn khung cấu hình
    if (lop.tietBatDau < dieuKien.tietDauTien || lop.tietKetThuc > dieuKien.tietCuoiCung) {
        return false; 
    }

    // 2. LỌC THEO MA TRẬN BUỔI NGHỈ (Dùng biến lop.thu làm chỉ số hàng)
    // Quy chuẩn kíp học HUST: Tiết 1-5 là Sáng (index 0), Tiết 6-12 là Chiều (index 1)
    if (lop.tietBatDau <= 5) { 
        // Lớp dính kíp SÁNG -> Check xem thứ này có bị tích đỏ ép nghỉ sáng không
        if (dieuKien.maTranNghi[lop.thu][0]) return false; 
    }
    if (lop.tietKetThuc >= 6) { 
        // Lớp dính kíp CHIỀU -> Check xem thứ này có bị tích đỏ ép nghỉ chiều không
        if (dieuKien.maTranNghi[lop.thu][1]) return false; 
    }

    return true; // Vượt qua vòng gửi xe thì cho vào danh sách quay lui
}