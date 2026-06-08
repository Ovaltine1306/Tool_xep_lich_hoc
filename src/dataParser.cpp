#include "../include/dataParser.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Bỏ các kí tự rác
string trim(const string& str) {
    auto start = str.find_first_not_of(" \t\r\n");
    auto end = str.find_last_not_of(" \t\r\n");     //Gemini :b
    return (start == string::npos) ? "" : str.substr(start, end - start + 1);
}

//Tách 1 dòng thành vector các cells
vector<string> tachDong(const string& line) {
    vector<string> result;
    string cell;
    bool inQuotes = false;      //check xem có trong ngoặc kép ko
    for (char c : line) {
        if (c == '"') inQuotes = !inQuotes;
        else if (!inQuotes && c == ',') {       //ngắt khi gặp dấu phẩy chuẩn
            if (cell == "NULL") cell = "";
            result.push_back(cell);
            cell.clear();
        }
        else if (c != '\r') cell += c;      
    }
    if (cell == "NULL") cell = "";
    result.push_back(cell);
    return result;
}

//Phân tích tuần từ aa-bb thành [1, 2, 3, ...]
vector<int> phanTichTuanHoc(string tuan) {
    vector<int> result;
    tuan = trim(tuan);
    stringstream ss(tuan);
    string segment;
    while (getline(ss, segment, ',')) {     //xét từng đoạn
        segment = trim(segment);    
        if (segment.empty()) continue;  //đã xét hết các đoạn
        auto pos = segment.find('-');   //tọa độ kí tự '-'
        if (pos != string::npos) {
            int start = stoi(segment.substr(0,pos));
            int end = stoi(segment.substr(pos + 1));
            for (int i = start; i <= end; i++) result.push_back(i);     //push từng tuần trong đoạn
        }
        else result.push_back(stoi(segment));   //nếu chỉ có 1 tuần lẻ
    }
    return result;
}

//Đọc file 
unordered_map<string,vector<lopHoc>> docFileCSV(string duongDan) {
    unordered_map<string,vector<lopHoc>> khoLopHoc;
    ifstream dataFile(duongDan);
    if (!dataFile.is_open()) return khoLopHoc;

    string line;
    while (getline(dataFile, line)) {
        if (line.empty()) continue;     //tach dong cuoi
        vector<string> cell = tachDong(line);

        lopHoc l;

        l.maLop = trim(cell[2]);  //Mã lớp
        l.maHP  = trim(cell[4]);  //Mã HP
        l.tenMon = cell[5]; //Tên HP
        l.soTin = cell[7].empty() ? 0 : stoi(cell[7]);  //Số tín chỉ
        l.thu = cell[10].empty() ? 0 : stoi(cell[10]);  //Thứ 
        l.tietBatDau = cell[12].empty() ? 0 : stoi(cell[12]);   //Tiết BĐ 
        l.tietKetThuc = cell[13].empty() ? 0 : stoi(cell[13]);  //Tiết KT 
        if (trim(cell[14]) == "Chiều") {
            l.tietBatDau += 6;
            l.tietKetThuc += 6;
        }
        if (l.thu == 0 || l.tietBatDau == 0 || l.tietKetThuc == 0) continue; //Bỏ các lớp đ có lịch học
        l.tuanHoc = phanTichTuanHoc(cell[15]);  //Tuần học 
        l.phongHoc = cell[16];      //Tên phòng học

        khoLopHoc[l.maHP].push_back(l);
    }
    return khoLopHoc;
}