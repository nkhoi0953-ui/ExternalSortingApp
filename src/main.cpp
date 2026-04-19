#include <iostream>
#include <windows.h>
#include <cstdio>
#include "../include/utils.h"
#include "../include/sorter.h"

using namespace std;

void showMenu() {
    cout << "\n=== CHƯƠNG TRÌNH SẮP XẾP NGOẠI ===" << endl;
    cout << "1. Tạo dữ liệu mẫu (Binary file)" << endl;
    cout << "2. Xem nội dung file" << endl;
    cout << "3. Thực hiện Sắp xếp ngoại (External Merge Sort)" << endl;
    cout << "0. Thoát" << endl;
    cout << "Chọn chức năng: ";
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    remove("data/output.bin");
    
    int choice;
    string inputFile = "data/input.bin";
    string outputFile = "data/output.bin";

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int n;
                cout << "Nhập số lượng số thực cần tạo: ";
                cin >> n;
                generateTestData(inputFile, n);
                cout << "Đã tạo file " << inputFile << endl;
                break;
            }
            case 2: {
            int subChoice;
            cout << "1. Xem file NGUỒN (input.bin)" << endl;
            cout << "2. Xem file KẾT QUẢ (output.bin)" << endl;
            cout << "Chon: ";
            cin >> subChoice;
            if (subChoice == 1) printBinaryFile(inputFile);
            else printBinaryFile(outputFile);
            break;
            }
            case 3: {
                int runSize;
                cout << "Nhập kích thước mỗi Run (số lượng số trong RAM): ";
                cin >> runSize;
                externalSort(inputFile, outputFile, runSize);
                cout << "\nSắp xếp hoàn tất! Kết quả tại: " << outputFile << endl;
                break;
            }
            case 0:
                cout << "Tạm biệt!" << endl;
                break;
            default:
                cout << "Lựa chọn không hợp lệ!" << endl;
        }
    } while (choice != 0);

    return 0;
}