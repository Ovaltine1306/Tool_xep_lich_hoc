#include "webview/webview.h"
#include "commonTypes.h"
#include "scheduleEngine.h" // Thêm include này để hiểu hàm taoTKB thực tế
#include "dataManager.h"

#include <chrono>
#include <filesystem>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <fstream> 

namespace {

std::string trim(const std::string &s) {
  const std::string ws = " \t\n\r";
  const auto begin = s.find_first_not_of(ws);
  if (begin == std::string::npos) return "";
  const auto end = s.find_last_not_of(ws);
  return s.substr(begin, end - begin + 1);
}

std::string unescapeJsonString(std::string text) {
  std::string out;
  out.reserve(text.size());
  for (size_t i = 0; i < text.size(); ++i) {
    if (text[i] == '\\' && i + 1 < text.size()) {
      const char next = text[i + 1];
      switch (next) {
        case '\\': out.push_back('\\'); break;
        case '"': out.push_back('"'); break;
        case 'n': out.push_back('\n'); break;
        case 'r': out.push_back('\r'); break;
        case 't': out.push_back('\t'); break;
        default: out.push_back(next); break;
      }
      ++i;
    } else {
      out.push_back(text[i]);
    }
  }
  return out;
}

// Trích xuất mã môn học từ đối số thứ nhất trong JSON Array
std::string extractSubjectCodes(const std::string &req) {
  const std::regex firstArgRegex("\\[\\s*\"((?:\\\\.|[^\"\\\\])*)\"");
  std::smatch match;
  if (std::regex_search(req, match, firstArgRegex) && match.size() > 1) {
    return trim(unescapeJsonString(match[1].str()));
  }
  return "";
}

// --- BỘ TRÍCH XUẤT ĐIỀU KIỆN LỌC ---
int extractIntFilter(const std::string &req, const std::string &key, int defaultValue) {
  const std::regex intRegex("\"" + key + "\"\\s*:\\s*(\\d+)");
  std::smatch match;
  if (std::regex_search(req, match, intRegex) && match.size() > 1) {
    return std::stoi(match[1].str());
  }
  return defaultValue;
}

// Quét xem một buổi cụ thể có bị bắt nghỉ không
bool isSessionDisabled(const std::string &req, int day, const std::string &session) {
  std::string pattern = "\"dayOfWeek\"\\s*:\\s*" + std::to_string(day) + "\\s*,\\s*\"session\"\\s*:\\s*\"" + session + "\"";
  std::regex sessionRegex(pattern);
  return std::regex_search(req, sessionRegex);
}

// Hàm râu ria tách chuỗi "EM1170, IT3140" -> vector<string> đã được cứu về đây
std::vector<std::string> bopTachMaMon(const std::string& cleanCodes) {
    std::vector<std::string> res;
    std::stringstream ss(cleanCodes);
    std::string token;
    while (std::getline(ss, token, ',')) {
        size_t first = token.find_first_not_of(" \t\r\n");
        size_t last = token.find_last_not_of(" \t\r\n");
        if (first != std::string::npos && last != std::string::npos) {
            res.push_back(token.substr(first, last - first + 1));
        }
    }
    return res;
}

}  // namespace

int main() {
  std::cout << "=======================================================================" << std::endl;
  std::cout << "    [!] HUST SCHEDULE ENGINE v2.5 - SOFT RETRO CALENDAR EDITION        " << std::endl;
  std::cout << "    [+] CORE ALGORITHM : BACKTRACKING (QUAY LUI DEG QUY)               " << std::endl;
  std::cout << "    [+] DEVELOPED BY   : UONG VAN THINH & NGUYEN MINH TRI (IT1 - HUST) " << std::endl;
  std::cout << "    [+] VERSION        : 2026.06.07                                    " << std::endl;
  std::cout << "    [-] WARNING        : ALL RIGHTS RESERVED. DO NOT RE-BRAND!         " << std::endl;
  std::cout << "=======================================================================" << std::endl;
  std::cout << "[SYSTEM] Khoi chay he thong loc lich..." << std::endl;
  napData("Data.csv");
  try {
    webview::webview w(true, nullptr);
    w.set_title("HUST Schedule Engine");
    w.set_size(1200, 800, WEBVIEW_HINT_NONE);

    w.bind("taoTKB", [&](const std::string &req) -> std::string {
        // 🔥 LOG 1: Xem chính xác cục dữ liệu thô thằng Frontend ném sang là gì
        std::cout << "\n================ [DEBUG FRONTEND -> BACKEND] ================" << std::endl;
        std::cout << "[RAW REQ]: " << req << std::endl;

        // 1. Bốc tách mã môn từ giao diện
        std::string subjectCodesRaw = extractSubjectCodes(req);
        std::vector<std::string> dsMaMon = bopTachMaMon(subjectCodesRaw);

        // 🔥 LOG 2: Xem C++ bóc tách từ chuỗi ra được bao nhiêu môn học
        std::cout << "[MA MON NHAN DUOC]: ";
        for(const auto& m : dsMaMon) std::cout << "'" << m << "' ";
        std::cout << "\n-----------------------------------------------------------" << std::endl;

        // 2. Nạp dữ liệu vào struct dieuKienLoc xịn của bồ
        dieuKienLoc dk;
        dk.tietDauTien = extractIntFilter(req, "startPeriod", 1);
        dk.tietCuoiCung = extractIntFilter(req, "endPeriod", 12);
        
        for (int day = 2; day <= 8; ++day) {
            if (isSessionDisabled(req, day, "morning"))   dk.maTranNghi[day][0] = true;
            if (isSessionDisabled(req, day, "afternoon")) dk.maTranNghi[day][1] = true;
        }

        // 3. Gọi Engine chạy đệ quy Backtracking thực tế ra vector<phuongAn>
        std::vector<phuongAn> cacPhuongAn = taoTKB(dsMaMon, dk);

        // 🔥 LOG 3: Xem thuật toán đệ quy tìm ra được bao nhiêu phương án cuối cùng
        std::cout << "[KET QUA]: Tim thay thuc te " << cacPhuongAn.size() << " phuong an TKB." << std::endl;
        std::cout << "============================================================\n" << std::endl;

        // 4. Đóng gói đống vector của bồ thành chuỗi JSON sạch để ném về cho Web render
        std::string responseJson = "{\"schedules\":[";
        // ... (Đoạn code đóng gói JSON phía dưới giữ nguyên cho đến hết hàm)
        for (size_t i = 0; i < cacPhuongAn.size(); ++i) {
            const auto& pa = cacPhuongAn[i];
            responseJson += "{\"id\":\"PA-" + std::to_string(pa.idPhuongAn) + "\",";
            responseJson += "\"totalCredits\":" + std::to_string(pa.tongSoTinChi) + ",";
            responseJson += "\"classes\":[";
            for (size_t j = 0; j < pa.danhSachLopHoc.size(); ++j) {
                const auto& c = pa.danhSachLopHoc[j];
                responseJson += "{\"subjectCode\":\"" + c.maHP + "\","; 
                responseJson += "\"classCode\":\"" + c.maLop + "\",";
                responseJson += "\"dayOfWeek\":" + std::to_string(c.thu) + ",";    
                responseJson += "\"period\":\"" + std::to_string(c.tietBatDau) + "-" + std::to_string(c.tietKetThuc) + "\","; 
                responseJson += "\"room\":\"" + c.phongHoc + "\"}";    
                if (j + 1 < pa.danhSachLopHoc.size()) responseJson += ",";
            }
            responseJson += "]}";
            if (i + 1 < cacPhuongAn.size()) responseJson += ",";
        }
        responseJson += "]}";

        return responseJson;
    });

    // --- BỘ ĐỌC FILE INDEX.HTML ĐÃ ĐƯỢC RÁP LẠI CHUẨN BÀI ---
    std::string htmlContent;
    bool fileLoaded = false;
    std::vector<std::string> pathsToTry = {"index.html", "../index.html", "../../index.html", "../../../index.html"};

    for (const auto& p : pathsToTry) {
        std::ifstream htmlFile(p);
        if (htmlFile.is_open()) {
            std::stringstream buffer;
            buffer << htmlFile.rdbuf();
            htmlContent = buffer.str();
            htmlFile.close();
            fileLoaded = true;
            break;
        }
    }

    if (fileLoaded) {
        w.set_html(htmlContent);
    } else {
        w.set_html("<html><body><h2>🚨 Khong tim thay index.html!</h2></body></html>");
    }

    w.run();
    return 0;
  } catch (const std::exception &ex) {
    std::cerr << "Startup failed: " << ex.what() << std::endl;
  }
  return 1;
}