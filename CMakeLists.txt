cmake_minimum_required(VERSION 3.10)

project(toolXepLichHoc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Nhặt toàn bộ file .cpp trong thư mục src và main.cpp ở ngoài (nếu có)
file(GLOB SOURCES "src/*.cpp" "*.cpp" "src/*.rc")

add_executable(toolXepLichHoc ${SOURCES})

# Trỏ thẳng vào thư mục include của bồ (nơi chứa webview.h và WebView2.h)
target_include_directories(toolXepLichHoc PRIVATE "${CMAKE_SOURCE_DIR}/include")

# [ ĐÂY LÀ DÒNG CHỐNG "DLL HELL" BẮT BUỘC PHẢI CÓ CHO MINGW ]
target_link_options(toolXepLichHoc PRIVATE -static -static-libgcc -static-libstdc++)

# Các thư viện hệ thống Windows bắt buộc phải link để vẽ giao diện
if(WIN32)
    target_link_libraries(toolXepLichHoc PRIVATE 
        user32 ole32 oleaut32 shlwapi comctl32 gdi32
    )
endif()

add_compile_definitions(_SILENCE_EXPERIMENTAL_COROUTINE_DEPRECATION_WARNINGS)