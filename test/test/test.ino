const int stepPin = 6;
const int dirPin  = 7;
const int enPin   = 8;

void setup () {
  // Đặt hai chân làm đầu ra
  pinMode (stepPin, OUTPUT);
  pinMode (dirPin, OUTPUT);

  pinMode (enPin, OUTPUT);
  digitalWrite (enPin, LOW);
}

void loop () {

  digitalWrite (dirPin, HIGH); // Cho phép động cơ di chuyển theo một hướng cụ thể
  // Tạo 200 xung để thực hiện một vòng quay đầy đủ
  for (int x = 0; x < 800; x ++) {
    digitalWrite (stepPin, HIGH);
    delayMicroseconds (500);
    digitalWrite (stepPin, LOW);
    delayMicroseconds (500);
  }
  delay(1000);

  digitalWrite (dirPin, LOW); // Thay đổi hướng xoay
  // Tạo ra 400 xung để thực hiện quay hai chu kỳ đầy đủ
  for (int x = 0; x < 800; x ++) {
    digitalWrite (stepPin, HIGH);
    delayMicroseconds (500);
    digitalWrite (stepPin, LOW);
    delayMicroseconds (500);
  }
  delay(1000);
}
