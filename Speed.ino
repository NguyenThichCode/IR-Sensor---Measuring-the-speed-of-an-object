
#define IR_1 8
#define IR_2 7
#define INVERT_LOGIC 1
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
float Distance = 0.15; //distance between 2 white leds of the 2 IR sensors (estimated 15cm)
float Speed;
float Time;
unsigned long startTime , endTime;
bool record = false;

void setup() {
  pinMode(IR_1, INPUT); //set the sensor pin as input
  pinMode(IR_2, INPUT);
  Serial.begin(9600); // set the baud rate for serial monitor as 9600
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Ready");


}
// i was testing with Serial Monitor before putting on the lcd so i just leave it there if u need to test
void loop() {
  int first = digitalRead(IR_1);
  int last = digitalRead(IR_2);
  if (first == LOW && record == false) {
    record = true;
    startTime = millis();
    Serial.println("Start Recording");

  }
  if (last == LOW && record == true) {
    record = false;
    endTime = millis();
    Time = (endTime - startTime) / 1000.0;
    Speed = Distance / Time;

    // Chỉ in ra LCD khi đã tính toán xong một lượt đo
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Speed: ");
    lcd.print(Speed);
    lcd.print(" m/s");

    Serial.print("Speed: ");
    Serial.print(Speed);
    Serial.println(" m/s");

    // Tạm dừng để người dùng kịp đọc kết quả trước khi đo lượt tiếp theo
    delay(2000);
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("Ready");
  }
}
