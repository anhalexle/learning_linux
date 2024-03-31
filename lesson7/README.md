# Pipe

## Definition

- Tạo ra 2 file descriptor
  - 1 file cho đầu ghi
  - 1 file cho đầu đọc

## Method

- Tạo ra 1 pipe trong RAM, 1 virtual file
  **Note**: virtual file: file k đc ghi vào ổ cứng, xem như vùng nhớ tạm
- Khi 1 process ghi vào virtual file thì những **related process** (process cha con) có thể đọc dữ liệu từ nó

### Step:

- Have a **main** process
- Create a pipe
- Create child process A, B, C

### Reading from a pipe:

- Pipe rỗng -> hàm read thì sẽ block cho tới khi nhận đc 1 byte
- Đầu write bị đóng -> hàm read đọc lại toàn bộ dữ liệu còn lại -> return 0

### Pipes have a limited capacity:

- vùng nhớ đệm trong bộ nhớ
- Đạt dung lượng tối đa -> đầu read lấy một số dữ liệu khỏi byte -> đầu write mới được ghi tiếp

## How to create pipe

- Use system call pipe(): **int pipe(int fds[2])** mảng 2 phần tử chứa file descriptor cho đầu đọc và ghi
  - fds[0]: file đầu read
  - fds[1]: file đầu write
  - Trả về 0 nếu thành công, -1 nếu thất bại
- Nếu tạo pipe trước fork, thì các **related process** sẽ có thể giao tiếp thông qua pipe

!!! Take note: nếu k có giá trị trong pipe, pipe rỗng, hoặc mới khởi tạo pipe -> xài read sẽ bị block -> chờ nào pipe có dữ liệu

## Communication between parent and child process

- Based on reader - writer concept
- Create two pipe:
  - One pipe: parent (writer) - child(reader)
  - One pipe: parent (reader) - child(writer)

# FIFOs - named Pipes

## Definition

- Có tên trong hệ thống tệp và mở được như 1 tệp thông thường khác với pipe chỉ là virtual file
- Tồn tại miễn là hệ thống còn hoạt động
- lưu trong bộ nhớ cục bộ, tạo bởi hàm **mkfifo()** trong C
- pipe: related processes
- FIFO: non-related processes

## Create FIFOS from shell

**mkfifo -m 0666 ./helloFIFO**
