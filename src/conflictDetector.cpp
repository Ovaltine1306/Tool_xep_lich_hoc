#include<iostream>
#include"../include/conflictDetector.h"
#include"../include/dataManager.h"

using namespace std;

bool kiemTraTrungGio(lopHoc& lop, vector<lopHoc>& lichHienTai){
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
bool kiemTraDieuKienLoc(lopHoc& lop, dieuKienLoc& dieuKien){
    if(dieuKien.lichHoc[lop.thu - 2] == 3) return false;

    if(dieuKien.lichHoc[lop.thu - 2] == 1 && lop.tietBatDau <= 6) return false;

    if(dieuKien.lichHoc[lop.thu - 2] == 2 && lop.tietBatDau >= 7) return false;

    if(dieuKien.tietDauTien > lop.tietBatDau || dieuKien.tietCuoiCung < lop.tietKetThuc) return false;

    return true;
}