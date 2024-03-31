## Socket lesson

socket: cơ chế truyền thông giữa 2 process trong 2 máy khác nhau

- 3 type: Domain, Type, Protocol
  \*\* Domain (tên miền): cho 2 process nói chuyện với nhau

## tên miền = IP + Port

- Unix domain: two process in one computer (đại diện là 1 file "/data/socket")
- Internet Domain: in different computers (có thể trên cùng 1 máy)
  IPv4
  IPv6
  \*\* Type: cơ chế truyền nhận
- Stream (TCP): chuỗi bit (audio, video)
- Datagram (UDP): gói tin (message)
  => khác nhau TCP có bắt tay 3 bước
  \*\* Protocol:
- Cách đông gói dữ liệu
- Có 4 loại:

* Unix Stream (TCP)
* Uninix Datagram (UDP)
* IPv4 Stream Socket
* IPv4 Datagram Socket

\*\* Stream Socket

Flow hoạt động
Stream socket
\*\* Server
socket: tạo ra file -> nhà
3 đối số: domain, type and protocol
bind -> treo biển số nhà
listen -> giới hạn số người nghe -> tối đa bao nhiêu ông đc xử lý trong 1 thời điểm
accept -> ngồi đợi khách tới -> 2 hướng xử lý: chấp nhận kết nối, không chấp nhận kết nối (blocks until client connect)

\*\* Client
b1: tạo ra 1 file socket
b2: connect tới server
b3: server quyết định chấp nhận hay k chấp nhận

-> 2 thằng read/write thông qua 1 file socket

htons: host byte to network byte order (short) This function converts 16-bit (2-byte) quantities from host byte order to network byte order.
INADDR_ANY: bind socket for all available interface: means any address for socket binding;

## Byte order

Thứ tự lưu trữ các bytes

- Computer
- Network

* 1.1 Computer byte order -> Thứ tự lưu trữ các byte dữ liệu trên máy tính

- Big - edian: các bytes có trọng số cao nhất sẽ được lưu ở ô có địa chỉ thấp nhất
- Little - edian: các bytes có trọng số thấp nhất sẽ được lưu ở ô có địa chỉ thấp nhất

* 1.2 Network byte order -> Thứ tự lưu trữ các byte trên mạng (Big edian)

vd1: little-edian port 200 => 0x07D0
htons(0x07D0) -> host to net short(2 bytes)
net -> big-edian -> 0xD007
-> Convert port 2000 little - edian -> big-edian
2000 -> 53255

chuyển số nguyên thì cần byte order, chuỗi thì k cần
-> gửi số nguyên ra mạng -> htons, ntohs
