#include <Car_IO.h>
#include <Servo.h>
Servo car_servo;

#define car_serial Serial
String lastcommand, command;
String b_speed, b_controller, b_servo;
int b_speed_, b_controller_, b_servo_;

void setup() {
  Serial.begin(9600);
  while (!Serial) {

  }
  car_serial.begin(9600);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  car_servo.attach(_SERVO);
  car_servo.write(90);

}
void loop() {
  if (car_serial.available()) {
    command = car_serial.readStringUntil('\n');
    if (command != lastcommand) {
      handlingdata(command);
    }
    lastcommand = command;
  }
}



void handlingdata(String data) {
  if (data.indexOf("SPEED") > -1) {
    b_speed = splitString(data, "SPEED", "=", ",", 0);
  }
  if (data.indexOf("JOYSTICK") > -1) {
    b_controller = splitString(data, "JOYSTICK", "=", ",", 0);
  }
  if (data.indexOf("SERVO_L") > -1) {
    b_servo = splitString(data, "SERVO_L", "=", ",", 0);
  }
  //Debug
  //    Serial.println(b_speed + " ---- " + b_controller + " ---- " +  b_servo);
  //Controller && Servo
  controller(b_controller);
  speed_servo(b_speed, b_servo);
}

void speed_servo(String b_speeds , String b_servos) {
  b_speed_        = b_speeds.toInt() * 25.4;
  b_servo_        = b_servos.toInt();
  car_servo.write(b_servo_);
}

void controller(String b_controllers) {
  b_controller_   = b_controllers.toInt();
  //  Serial.println(String(b_speed_) + " ---- " + String(b_servo_) + " ---- " +  String(b_controller_));
  switch (b_controller_)
  {
    case 1:
      goFF();
      break;
    case 2:
      goBB();
      break;
    case 3:
      goL();
      break;
    case 4:
      goR();
      break;
    case 5:
      goFR();
      break;
    case 6:
      goFL();
      break;
    case 7:
      goBR();
      break;
    case 8:
      goBL();
      break;
    case 9:
      goStop();
      break;
  }
}

void goStop() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, 0);
}

void goFF() {
  analogWrite(IN_1, b_speed_);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, b_speed_);
  analogWrite(IN_4, 0);
}

void goBB() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, b_speed_);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, b_speed_);
}

void goL() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, b_speed_);
  analogWrite(IN_3, b_speed_);
  analogWrite(IN_4, 0);
}

void goR() {
  analogWrite(IN_1, b_speed_);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, b_speed_);
}

void goFR() {
  analogWrite(IN_1, b_speed_);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, b_speed_ / 2);
}

void goFL() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, b_speed_ / 2);
  analogWrite(IN_3, b_speed_);
  analogWrite(IN_4, 0);
}

void goBR() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, b_speed_);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, b_speed_ / 2);
}

void goBL() {
  analogWrite(IN_1, 0);
  analogWrite(IN_2, b_speed_ / 2);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, b_speed_);
}

String splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset) {
  unsigned char lenOfCommand = v_G_Command.length();
  unsigned char posOfCommand = v_G_motherString.indexOf(v_G_Command);
  int PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol, posOfCommand + lenOfCommand);

  while (v_G_Offset > 0) {
    v_G_Offset--;
    PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol, PosOfStartSymbol + 1);
  }

  int PosOfStopSymbol = v_G_motherString.indexOf(v_G_Stop_symbol, PosOfStartSymbol + 1);

  return v_G_motherString.substring(PosOfStartSymbol + 1, PosOfStopSymbol);
}
