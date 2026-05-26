#include "../include/dataParser.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <unordered_map>
using namespace std;

unordered_map<string,vector<lopHoc>> docFileCSV(string duongDan) {
    unordered_map<string,vector<lopHoc>> khoLopHoc;
    ifstream dataFile(duongDan);
    if (!dataFile.is_open()) return khoLopHoc;

    string line;
    while (getline(dataFile, line)) {
        
    }
}