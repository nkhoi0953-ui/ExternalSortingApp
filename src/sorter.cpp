#include "../include/sorter.h"
#include "../include/utils.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>

using namespace std;

// Cấu trúc để hỗ trợ Min-Heap
struct Node {
    double value;
    int runIdx;

    // Heap trả về giá trị nhỏ nhất
    bool operator>(const Node& other) const {
        return value > other.value;
    }
};

void externalSort(const string& input, const string& output, int runSize) {
    ifstream inFile(input, ios::binary);
    if (!inFile) {
        cerr << "Không thể mở file nguồn!!!" << endl;
        return;
    }

    // --- GIAI ĐOẠN 1: TẠO CÁC RUNS ĐÃ SẮP XẾP ---
    cout << "\n[Giai đoạn 1]: Đang chia file và sắp xếp nội (Internal Sort)..." << endl;
    
    vector<double> buffer;
    double val;
    int runCount = 0;
    bool hasData = true;

    while (hasData) {
        buffer.clear();
        // 1. Đọc tối đa 'runSize' phần tử vào RAM
        for (int i = 0; i < runSize; ++i) {
            if (inFile.read(reinterpret_cast<char*>(&val), sizeof(double))) {
                buffer.push_back(val);
            } else {
                hasData = false;
                break;
            }
        }

        if (buffer.empty()) break;

        // 2. Sắp xếp các phần tử trong RAM
        sort(buffer.begin(), buffer.end());

        // 3. Ghi vào file tạm (run file)
        string runName = "temp/run_" + to_string(runCount) + ".bin";
        ofstream outFile(runName, ios::binary);
        for (const double& d : buffer) {
            outFile.write(reinterpret_cast<const char*>(&d), sizeof(double));
        }
        outFile.close();

        cout << " -> Đã tạo: " << runName << " (chứa " << buffer.size() << " số)" << endl;
        runCount++;
    }
    inFile.close();

    cout << "==> Hoàn thành Giai đoạn 1. Tổng cộng có " << runCount << " runs." << endl;
    cout << "Dữ liệu tạm đã được tạo trong thư mục /temp." << endl;

    // Lệnh tạm dừng ở đây
    cout << "NHẤN PHÍM BẤT KỲ ĐỂ TIẾP TỤC SANG GIAI ĐOẠN MERGE..." << endl;
    system("pause");
    
    // --- GIAI ĐOẠN 2: TRỘN (K-WAY MERGE) ---
    cout << "\n[Giai đoạn 2]: Đang thực hiện trộn " << runCount << " runs..." << endl;

    // 1. Mở tất cả các file run tạm
    vector<ifstream*> runFiles(runCount);
    priority_queue<Node, vector<Node>, greater<Node>> minHeap;

    for (int i = 0; i < runCount; ++i) {
        string runName = "temp/run_" + to_string(i) + ".bin";
        runFiles[i] = new ifstream(runName, ios::binary);
        
        double val;
        if (runFiles[i]->read(reinterpret_cast<char*>(&val), sizeof(double))) {
            minHeap.push({val, i});
        }
    }

    // 2. Mở file kết quả để ghi
    ofstream outFile(output, ios::binary);
    
    while (!minHeap.empty()) {
        // Lấy số nhỏ nhất từ Heap
        Node top = minHeap.top();
        minHeap.pop();

        // Ghi vào file kết quả
        outFile.write(reinterpret_cast<char*>(&top.value), sizeof(double));

        // Đọc số tiếp theo từ chính file vừa lấy ra
        double nextVal;
        if (runFiles[top.runIdx]->read(reinterpret_cast<char*>(&nextVal), sizeof(double))) {
            minHeap.push({nextVal, top.runIdx});
        }
    }

    // 3. Đóng và dọn dẹp
    outFile.close();
    for (int i = 0; i < runCount; ++i) {
        runFiles[i]->close();
        delete runFiles[i];
        // Xóa file tạm sau khi dùng xong (đúng yêu cầu giải thuật ngoại)
        string runName = "temp/run_" + to_string(i) + ".bin";
        remove(runName.c_str()); 
    }

    cout << "==> Sắp xếp hoàn tất! Kết quả tại: " << output << endl;
}
