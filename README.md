

# Sensor Gateway System

Hệ thống Gateway đa luồng được viết bằng ngôn ngữ C, thiết kế để nhận dữ liệu từ các cảm biến y tế (ECG và PPG) qua giao thức TCP/IP, lưu trữ vào cơ sở dữ liệu SQLite và quản lý nhật ký hệ thống (log) thông qua một tiến trình riêng biệt.

## 🚀 Tính năng chính

* **TCP Server**: Khả năng chấp nhận nhiều kết nối cảm biến đồng thời bằng kiến trúc đa luồng (`pthread`).
* **Xử lý đa luồng (Multi-threading)**:
* `Connection Thread`: Chấp nhận các kết nối mới.
* `Worker Threads`: Mỗi cảm biến được quản lý bởi một luồng riêng để nhận dữ liệu.
* `Storage Thread`: Luồng chuyên biệt để lấy dữ liệu từ hàng đợi (Shared List) và ghi vào Database.


* **Cơ chế Log độc lập**: Sử dụng `fork()` để tạo một tiến trình logger riêng, giao tiếp với tiến trình chính thông qua **Named Pipe (FIFO)**.
* **Quản lý bộ nhớ & Đồng bộ hóa**: Sử dụng `Mutex` và `Condition Variable` để đảm bảo an toàn dữ liệu khi nhiều luồng cùng truy cập vào danh sách cảm biến.
* **Graceful Shutdown**: Xử lý tín hiệu `SIGINT` (Ctrl+C) để đóng kết nối, giải phóng bộ nhớ và xuất dữ liệu an toàn trước khi thoát.

## 🛠 Kiến trúc hệ thống

1. **Tiến trình chính (Parent Process)**:
* Khởi tạo Socket, Bind và Listen.
* Tạo các luồng: `connection`, `data`, `storage`.
* Quản lý danh sách liên kết vòng/chia sẻ dữ liệu cảm biến.


2. **Tiến trình Logger (Child Process)**:
* Đọc dữ liệu từ FIFO.
* Ghi nhật ký kèm timestamp vào file `gateway.log`.


3. **Cơ sở dữ liệu**:
* Sử dụng SQLite để lưu trữ dữ liệu ECG/PPG theo thời gian thực.
* Tự động xuất (export) session khi kết thúc.



## 📂 Cấu trúc mã nguồn

* `main.c`: Luồng chính của chương trình, thiết lập server và quản lý tiến trình.
* `log.h/c`: Định nghĩa các hàm ghi log vào FIFO.
* `sensor_list.h/c`: Quản lý danh sách chia sẻ (Shared List) giữa các luồng.
* `connection.h/c`: Xử lý kết nối TCP.
* `database.h/c`: Giao tiếp với SQLite.

## ⚙️ Cài đặt và Sử dụng

### Yêu cầu

* Hệ điều hành: Linux/Unix.
* Trình biên dịch: `gcc`.
* Thư viện: `pthread`, `sqlite3`.

### Biên dịch

Sử dụng lệnh sau để biên dịch (giả sử bạn đã có các file header và source tương ứng):

```bash
gcc main.c log.c sensor_list.c connection.c database.c -o gateway -lpthread -lsqlite3

```

### Chạy ứng dụng

Chạy gateway với tham số là cổng (port) muốn lắng nghe:

```bash
./gateway 8080

```

## ⚠️ Lưu ý về luồng dữ liệu

* Dữ liệu gửi từ sensor cần theo định dạng: `%lf %lf` (Ví dụ: `1.23 4.56` tương ứng ECG và PPG).
* Hệ thống sử dụng `SO_REUSEADDR` để cho phép khởi động lại server nhanh chóng trên cùng một port.

## 📄 Giấy phép

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Python Version](https://img.shields.io/badge/python-3.8%2B-blue.svg)](https://www.python.org/)

📧 Liên hệ
Tác giả: Art3m1sHun

Email: minhhungdenguyn052@gmail.com

Dự án: https://github.com/Art3m1sHun/final-project