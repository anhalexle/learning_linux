# Message Queues

## Definition

- Danh sách liên kết duy trì bởi kernel
- Tất cả các process có thể trao đổi dữ liệu hệ thống qua việc truy cập vào 1 queue
- Message: type: message
- Dựa vào type message mà các process có thể lấy ra tin nhắn phù hợp (dựa vào type)

## POSIX Message Queues

- Tạo 1 message queue hoặc mở message queue có sẵn
- Ghi dữ liệu
- Đọc dữ liệu
- Đóng message queue khi k sử dụng
- Giải phóng (unlink) message queue

### Opening a message queue

- Sử dụng API: **mq_open()**
- Cú pháp: **mqd_t mq_open(const char *name, int oflag, mode_t mode, struct mq_attr *attr)** return a message queue on success, -1 on error
  - name: tên mesage_queue
  - oflag:
    - O_CREATE
    - O_EXCEL
    - O_RDONLY
    - O_NONBLOCK
  - mode: 0666
  - attr: Chỉ định thuộc tính message queue, nếu NULL -> thuộc tính mặc định

**Note**:
struct mq_attr {
long mq_flags; // check xem msqueue có block khi read hoặc write k ? value: 0 | O_NONBLOCK
long mq_maxmsg; // maximum number of messages on queue
long mq_msgsize; // maximum message bytes
long mq_curmsgs; // number of message currently
}

### Sending message

- Sủ dụng API: **mq_send()**
- Cú pháp: **int mq_send(mqd_t mqdes, const char \*msg_ptr, size_t msg_len, unsigned int msg_prio)**
  - mqdes: mq descriptor (trả về mq_attr)
  - msg_ptr: con trỏ tới message
  - msg_len: kích thước message
  - msg_prio: priority of message (số nguyên dương k âm, 0 là thấp nhất, có message mới thì được bỏ vào phía sau các message có độ ưu tiên giống nhau, không ưu tiên thì set cùng 1 giá trị)
    **Note**: return 0 on success, -1 on error

### Receving message

- Sử dụng API: **mq_receive()**
  - mqdes: mq descriptor được trả về ở 3.1
  - msg_ptr: con trỏ tới message
  - msg_len: kích thước message
  - msg_prio: priority của message

**Note** mq_receive() loại bỏ message có mức độ ưu tiên cao nhất khỏi quêu, tham chiếu bởi mqdes và trả về thông báo trong bộ đệm do msg_ptr trỏ tới

### Closing message queue

- API: **mq_close()**
- Cú pháp: **int mq_close(mqd_t mqdes)**

### Remove message queue

- API: **mq_unlink()**
- Cú pháp: **int mq\_\_unlink(mqd_t mqdes)**
