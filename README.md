# **tiny-shell**

## Description
Practical project xây dựng **tiny-shell** của học phần Nguyên lý Hệ điều hành


## Usage
Compile project ra file <h a><strong><code>shell.out</code></strong></h> bằng lệnh: 
```
make build
```
Chạy chương trình **tiny-shell** bằng lệnh: 

```
make run
```

hoặc

```
./shell.out
```

Xóa các file được tạo bởi make:
```
make clean
```

## Function

**tiny-shell** hỗ trợ một số các tính năng đơn giản sau:

- Tạo tiến trình con chạy chương trình ở dạng: 
    - Foreground mode
    - Background mode
    - Tạo tiến trình chạy ở terminal khác
- Quản lý các tiến trình
    - ```list```: In ra danh sách các tiến trình gồm tên, mã số, mã số tiến trình cha, trạng thái
    - ```kill```, ```stop```, ```resume```: Hủy bỏ, tạm dừng, tiếp tục một background process
- Thực hiện một số câu lệnh đặc biệt
    - ```exit,help,date,dir,cd```
    - ```path/addpath```: Xem và cài đặt biến môi trường
- **tiny-shell** nhận tín hiệu ngắt từ bàn phím (Ctrl+C) để hủy bỏ foreground process (nếu có)
- Hỗ trợ câu lệnh dùng để thực thi file ***.sh***
- Hỗ trợ câu lệnh đọc một file thực thi từng dòng lệnh hỗ trợ trong tiny-shell

## System Requirement
- Hệ điều hành: ***Linux***
<!-- - Chip xử lý: ***x86, ARM*** -->

## Contributor

```
Phạm Đức Minh   - 20210586

Hoàng Nhật Minh - 20214256
```