# IPC

- IPC has two types: communication and synchronization
- Communication:
  - Data Transfer: chia sẻ dữ liệu \*\*Note: 2 process a <-> b qua package (dữ liệu gửi 1 lần rồi mất đi)
    - Byte Stream: luồng
      - pipe
      - FIFO
      - Stream socket
    - Message: bản tin
      - System V Message Queue
      - POSIX Message Queue
      - Datagram socket
  - Shared Memory: chia sẻ vùng nhớ \*\*Note: 1 vùng nhớ A trên RAM thì cả process A và B đều tương tác với vùng nhớ A
    - System V Shared Memory
    - POSIX Shared Memory
    - Memory mapping:
      - Anonymous Mapping
      - File Mapping
- Synchronization:
  - Semaphore
    - System V Semaphore
    - POSIX Semaphore
      - Named
      - Unamed
  - File lock
    - "record" lock (fcntl())
    - file lock (flock())
  - Mutex (threads)
  - Conditional variable (threads)

# Shared memory

- Cho phép nhiều tiến trình truy cập cùng lúc
- Tốc đọ xử lý nhanh hơn
- Nằm giữa heap, stack

## How to use shared memory

- API POSIX
- API System V

-> Ánh xạ shared memory vào trong từng process image của từng process

\*\* Note:

- Pipe, socket, message queue: ghi từ user <-> kernel <-> Hardware (RAM)
- Shared memory: user <-> Hardware(RAM)

* buffer = malloc(4mb): Heap: virtual address
* buffer = mmap(4mb): real hardware address

\*\* Shared memory init khá lâu

- Shared memory khởi tạo 1 lần -> không thể hủy sau khi khởi tạo
- Khởi tạo khi runtime
- Xử lý đồng bộ -> do đc sử dụng chung bởi nhiều thằng
- mutex(thread) - semaphore(process): xử lý đồng bộ

## Step to create POSIX Shared memory

- Tạo shared memory
- Set kích thước cho shared memory object
- Map/unmap shared memory object (map trên stack của process image)
- Giải phóng shared memory object

### api system call:

shared memory object is still a file

**shm_open()**: to create shared memory object
**ftruncate()**: set size cho memory object
**mmap()**: map
**munmap()**: unmap
**shm_unlink()**: free shared memory object

### Mapping type

- File: file thật (FIFO): shared memory cho non-related process
- Anonymous: virtual(pipe): shared memory cho related process

### Visibility of modifications: khả năng quan sát sự thay đổi của dữ liệu

- Private: không quan sát được -> không thấy sự thay đổi -> A mod nhưng B k thấy A mod -> dùng copy on-write (copy ra vùng nhớ mới để thực hiện sự thay đổi)
- Shared: quan sát được
