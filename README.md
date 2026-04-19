# External Sorting App - C++

Ứng dụng minh họa thuật toán **Sắp xếp ngoại (External Merge Sort)** được phát triển trong khuôn khổ môn học Cấu trúc dữ liệu và Giải thuật nâng cao. Ứng dụng cho phép sắp xếp tập tin nhị phân chứa dữ liệu số thực (`double`) có kích thước lớn hơn dung lượng RAM vật lý của hệ thống.

## 🚀 Tính năng nổi bật
* **K-way Merge Sort:** Sử dụng thuật toán trộn K đường để tối ưu hóa việc xử lý tập tin lớn.
* **Min-Heap Optimization:** Sử dụng cấu trúc dữ liệu Priority Queue (Min-Heap) giúp tìm phần tử nhỏ nhất trong giai đoạn Merge với độ phức tạp $O(\log K)$.
* **Xử lý nhị phân:** Đọc và ghi trực tiếp dữ liệu nhị phân (8-bytes) để đảm bảo tốc độ và độ chính xác tối đa.
* **Cơ chế dọn dẹp:** Tự động quản lý và dọn dẹp các file tạm (Sorted Runs) để bảo vệ dung lượng ổ đĩa.

## 🛠 Yêu cầu hệ thống & Cài đặt

### Yêu cầu
* Trình biên dịch: **GCC/G++** hỗ trợ tiêu chuẩn **C++17** trở lên.
* Hệ điều hành: Windows/Linux/macOS.

### Biên dịch
Sử dụng Terminal trong VS Code và chạy lệnh sau:

**g++ src/*.cpp -Iinclude -o main.exe**

**./main.exe**

## 📖 Hướng dẫn sử dụng
* **Tạo dữ liệu:** Chọn chức năng tạo file ngẫu nhiên để tạo tập tin input.bin
* **Cấu hình tham số:**
    Số lượng phần tử ($N$): Tổng số lượng số thực cần sắp xếp.
    Dung lượng đoạn ($runSize$): Số lượng phần tử được sắp xếp trong RAM trước khi ghi xuống file tạm.
* **Thực hiện sắp xếp:** Chương trình sẽ thực hiện chia đoạn, sắp xếp nội bộ và thực hiện trộn để tạo ra file output.bin hoàn chỉnh.