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
    int soTin;
};

struct phuongAn{
    int idPhuongAn;
    int tongSoTinChi;
    std::vector<lopHoc> danhSachLopHoc;
};

struct dieuKienLoc{
    bool maTranNghi[9][2] = {false};

    // Khung giờ
    int tietDauTien = 1;
    int tietCuoiCung = 12;
}; 