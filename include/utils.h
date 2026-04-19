#ifndef UTILS_H
#define UTILS_H

#include <string>

// Tạo file nhị phân chứa n số thực ngẫu nhiên
void generateTestData(const std::string& filename, int n);

// Đọc và in nội dung file nhị phân ra màn hình 
void printBinaryFile(const std::string& filename);

#endif