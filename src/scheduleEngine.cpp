#include"../include/scheduleEngine.h"
#include"../include/dataManager.h"
#include"../include/conflictDetector.h"
#include<iostream>

using namespace std;

int cnt = 0;

void xepLich(int index, vector<vector<lopHoc>>& dsCacNhomTheoMaMon, vector<lopHoc>& lichHienTai, vector<phuongAn>& result, dieuKienLoc& dieuKien){
    if(result.size() > 1000) return;
    if(index == dsCacNhomTheoMaMon.size()) {
        phuongAn paHienTai;
        paHienTai.danhSachLopHoc = lichHienTai;
        paHienTai.idPhuongAn = ++cnt;
        paHienTai.tongSoTinChi = 0;
        for(int i = 0; i < lichHienTai.size(); i++) {
            paHienTai.tongSoTinChi += lichHienTai[i].soTin;
        }
        result.push_back(paHienTai);
        return;
    }
        for (int i = 0; i < dsCacNhomTheoMaMon[index].size(); i++) {
            if(!kiemTraTrungGio(dsCacNhomTheoMaMon[index][i], lichHienTai) && kiemTraDieuKienLoc(dsCacNhomTheoMaMon[index][i], dieuKien)){
                lichHienTai.push_back(dsCacNhomTheoMaMon[index][i]);
                xepLich(index + 1, dsCacNhomTheoMaMon, lichHienTai, result, dieuKien);
                lichHienTai.pop_back();
            }
        }
    
}

vector<phuongAn> taoTKB(vector<string>& dsMaMon, dieuKienLoc& dieuKien) {
    cnt = 0;
    vector<vector<lopHoc>> dsCacNhomTheoMaMon;
    for (int i = 0; i < dsMaMon.size(); i++) {
        vector<lopHoc> dsLopLayDuoc = layDanhSachLopTheoMon(dsMaMon[i]);
        cout << "[DEBUG CSV] Mon " << dsMaMon[i] << " boc tu file CSV len duoc: " << dsLopLayDuoc.size() << " lop thuc te." << endl;
        dsCacNhomTheoMaMon.push_back(dsLopLayDuoc);
    }
    vector<lopHoc> lichHienTai;
    vector<phuongAn> result;
    xepLich(0, dsCacNhomTheoMaMon, lichHienTai, result, dieuKien);
    return result;
}