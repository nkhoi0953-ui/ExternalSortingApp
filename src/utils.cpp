#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>

using namespace std;

// Hàm tạo dữ liệu mẫu: Ghi n số thực ngẫu nhiên vào file nhị phân
void generateTestData(const string& filename, int n) {
    // Mở file ở chế độ binary và output
    ofstream outFile(filename, ios::binary | ios::out);
    
    if (!outFile) {
        cerr << "Lỗi: Không thể tạo file " << filename << endl;
        return;
    }

    // Thiết lập bộ sinh số ngẫu nhiên (double)
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<double> dis(1.0, 1000.0); // Số thực từ 1.0 đến 1000.0

    for (int i = 0; i < n; ++i) {
        double val = dis(gen);
        // Ghi 8 bytes của biến double vào file
        outFile.write(reinterpret_cast<const char*>(&val), sizeof(double));
    }

    outFile.close();
    cout << "Đã ghi " << n << " số thực vào file: " << filename << endl;
}

// Hàm đọc và in file: Giúp minh họa dữ liệu
void printBinaryFile(const string& filename) {
    ifstream inFile(filename, ios::binary | ios::in);
    
    if (!inFile) {
        cerr << "Lỗi: Không thể mở file " << filename << endl;
        return;
    }

    double val;
    int count = 0;
    cout << fixed << setprecision(2); // In 2 chữ số thập phân cho đẹp
    cout << "--- Nội dung file [" << filename << "] ---" << endl;

    // Đọc từng khối 8 bytes cho đến khi hết file
    while (inFile.read(reinterpret_cast<char*>(&val), sizeof(double))) {
        cout << val << "\t";
        count++;
        // Xuống dòng mỗi 5 số cho dễ nhìn
        if (count % 5 == 0) cout << endl;
    }
    
    if (count % 5 != 0) cout << endl;
    cout << "Tổng cộng: " << count << " phần tử." << endl;
    cout << "------------------------------------------" << endl;

    inFile.close();
}