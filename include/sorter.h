#ifndef SORTER_H
#define SORTER_H

#include <string>

// Hàm thực hiện sắp xếp ngoại
// input: file nguồn, output: file đích, runSize: số phần tử tối đa trong RAM
void externalSort(const std::string& input, const std::string& output, int runSize);

#endif