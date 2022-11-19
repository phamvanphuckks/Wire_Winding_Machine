1. 
Revolution is completely circle movement arround a point.
pulse/rev: a number of pulse per a revolution
rpm: revolution per minute

2.
+ vi bước càng lớn => động cơ quay càng mịn
+ tính toán giá trị period nạp vào timer
F = 72 000 000
F cho TB6600 là 0-20Khz
trong đó 0-13khz nếu 50/50, 0-20Khz nếu 25/75
=> ta chọn 0-13khz => prescaler 6000 => Ftimer= 72000000/6000 = 12000hz = 12khz


=> setup tốc độ quay là setup rpm
=> period = (60/(pulse_of_revolution*rpm) / (1/12000))/2   // 1, quy theo đơn vị s || 2, /2 là do 50% duty cycle
=============================================================================================================================================
1. Điều khiển chiều quay
2. Setup số vòng quay
3. Setup tốc độ quay
4. Biết được vòng quay hiện tại
5. Nhớ được số vòng đã quay khi pause
6. Reset

Mã bản tin

| 0x55 0xAA | Length | command type | 4 byte | CheckSum |
