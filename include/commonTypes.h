#pragma once

#include<vector>
#include<string>

enum trangThaiNgay{
    hocBinhThuong = 0,
    nghiBuoiSang = 1,
    nghiBuoiChieu = 2,
    nghiCaNgay = 3
};

struct lopHoc{
    std::string tenMon;
    std::string maHP;
    std::string maLop;
    int thu;
    int tietBatDau;
    int tietKetThuc;
    std::vector<int> tuanHoc;
    std::string phongHoc;
};

struct phuongAn{
    int idPhuongAn;
    int tongSoTinChi;
    std::vector<lopHoc> danhSachLopHoc;
};

struct dieuKienLoc{
    trangThaiNgay lichHoc[7] = {hocBinhThuong}; // Khởi tạo cả 7 ngày đều là đi học

    // Checkbox
    bool uuTienToaGanNhau = false;
    bool uuTienPhongHocGanNhau = false;

    // Khung giờ
    int tietDauTien = 1;
    int tietCuoiCung = 12;
};