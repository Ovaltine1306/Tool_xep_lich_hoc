#include "../include/dataParser.h"
#include "../include/dataManager.h"
#include <iostream>
#include <fstream>
using namespace std;

//Kho lưu trữ dữ liệu dưới dạng <Mã HP, Lớp học>
unordered_map<string,vector<lopHoc>> khoDuLieu;

//Nạp dữ liệu vào kho
void napData(string duongDan) {
    khoDuLieu = docFileCSV(duongDan);
    return;
}

//Lấy danh sách lớp
vector<lopHoc> layDanhSachLopTheoMon(string maHP) {
    if (khoDuLieu.find(maHP) == khoDuLieu.end()) return {};
    else return khoDuLieu[maHP];
}

//Save các môn đang chọn 
void luuTrangThaiNguoiDung(vector<string> dsMonDangChon) {
    ofstream saveFile("userSave.csv");
    for (string mon : dsMonDangChon) saveFile << mon << endl;
    saveFile.close();
    return;
}

//Lấy các môn đang chọn dở ra
vector<string> taiTrangThaiNguoiDung() {
    ifstream saveFile("userSave.csv");
    vector<string> result;
    string mon;
    while (getline(saveFile,mon)) result.push_back(mon);
    saveFile.close();
    return result;
}
