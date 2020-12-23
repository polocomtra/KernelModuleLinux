# Đồ án 3 Hệ Điều Hành: Kernel Module Linux
Simple random character device Linux

Nhóm sinh viên:
- 18120186 - Nguyễn Cao Đăng Khoa
- 18120306 - Lê Thọ Đạt
- 18120542 - Nguyễn Tiến Tài

## Yêu cầu: Mục tiêu hiểu về Linux kernel module và hệ thống quản lý file và device trong linux, giao tiếp giữa tiến trình ở user space và code kernel space 
+ Viết một module dùng để tạo ra số ngẫu nhiên. 
+ Module này sẽ tạo một character device để cho phép các tiến trình ở userspace có thể open và read các số ngẫu nhiên.
### Linux Kernel Module: random ( number ) module
file randommodule.c chứa mã nguồn dùng để biên dịch ra module là một character device, có chức năng cho phép các tiến trình ở user space mở và đọc một số ngẫu nhiên từ file thiết bị của device này.
### Usage:
- Mở Terminal gõ lệnh ```make``` để tạo file file randommodule.ko 
- Gõ lệnh ```sudo insmod randommodule.ko``` để cài đặt module driver 
- Gõ lệnh ```lsmod | grep chardevdrv``` để xem module đã được cài chưa
- Biên dịch file test.c bằng lệnh ```gcc test.c -o test``` để tạo ra file test
- Tiến hành chạy file test bằng lệnh ```sudo ./test``` để kiểm tra kết quả
- Để gỡ module, gõ lệnh ```sudo rmmod chardevdrv```
- Dọn sạch folder bằng lệnh ```make clean```
