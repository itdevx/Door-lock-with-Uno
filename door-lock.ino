#include <Keypad.h>
#include <LiquidCrystal.h>
#include <ezBuzzer.h>
#include <Wire.h>
#include <Servo.h>


#define Relay A0

Servo servo;

const int rows = 4;
const int cols = 4;

String pad;
String pad_password;
char keypressed;
char keypressed_password;

String password_1 = "542159";
String password_2 = "852565";
String password_3 = "477114";
String password_4 = "699335";
String password_5 = "569669";
String password_6 = "119559";
String password_7 = "287991";
String password_8 = "335597";
String password_Admin = "516271";

const int buzzer_pin = 12;

int cursorColumn = 0;

char keys[rows][cols] = {
  {'1', '2', '3', 'f1'},
  {'4', '5', '6', 'f2'},
  {'7', '8', '9', 'f3'},
  {'.', '0', '=', 'f4'},
};

byte pin_rows[rows] = {9, 8, 7, 6};
byte pin_cols[cols] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_cols, rows, cols);
LiquidCrystal lcd(10, 11, A2, A3, A4, A5);
ezBuzzer buzzer(buzzer_pin);


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, 1);
  servo.attach(1);
  pinMode(buzzer_pin, OUTPUT);

}

void loop() {
  if (pad != password_Admin) {
    LcdStart();
    readKeypad();
    CheckPassword();
  }
  // while (pad == password_Admin){
  //   AddNewPassword();
  // }
  
}


void CheckPassword() {
  while (keypressed == "=") {
    lcd.clear();
    pad = "";
  }

  while (pad == password_1 || pad == password_2 || pad == password_3 || pad == password_4 || pad == password_5 || pad == password_6 || pad == password_7 || pad == password_8 || pad == password_Admin) {

    if (pad == password_1) {
      OpenDoor();
      lcd.print("Welcome Yasin");
      CloseDoor();
    }else if (pad == password_2) {
      OpenDoor();
      lcd.print("Welcome Safari");
      CloseDoor();
    }else if (pad == password_3) {
      OpenDoor();
      lcd.print("Welcome Tabeei");
      CloseDoor();
    }else if (pad == password_4) {
      OpenDoor();
      lcd.print("Welcome Nesaei");
      CloseDoor();
    }else if (pad == password_5) {
      OpenDoor();
      lcd.print("Welcome Maldar");
      CloseDoor();
    }else if (pad == password_6) {
      OpenDoor();
      lcd.print("WLC NOORMohamadi");
      CloseDoor();
    }else if (pad == password_7) {
      OpenDoor();
      lcd.print("Welcome Ghavidel");
      CloseDoor();
    }else if (pad == password_8) {
      OpenDoor();
      lcd.print("WLC Ghodosian");
      CloseDoor();
    }
    // else if (pad == password_Admin) {      
    //   AddNewPassword();
    // }
  

  }
  if (pad.length() >= 6) {
    tone(buzzer_pin, 640);
    delay(300);
    lcd.clear();
    pad = "";
    keypressed = NULL;
    noTone(buzzer_pin);
  }

}

void OpenDoor() {
  tone(buzzer_pin, 440);
  delay(500);
  noTone(buzzer_pin);
  delay(100);
  digitalWrite(Relay, 0);
  lcd.clear();
  lcd.setCursor(0, 1);
}

void CloseDoor() {
  delay(1000);
  digitalWrite(Relay, 1);
  delay(1000);
  lcd.clear();
  pad = "";
}

void LcdStart() {
  lcd.setCursor(0, 0);
  lcd.print("Enter Password : ");
  lcd.setCursor(5, 1);
  for (int i = 0; i < pad.length(); i++) {
    lcd.print("*");
  }
}

void readKeypad() {
  buzzer.loop();
  char keypressed = keypad.getKey();

  if (keypressed == '=') {
    lcd.clear();
    pad = "";
    keypressed = NULL;
  }

  String konv = String(keypressed);
  pad += konv;

  if (keypressed) {
    buzzer.beep(50);
  }

}

// BUG
void AddNewPassword() {
  buzzer.loop();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Add[1] Open[2]");
  char keypressed_password = keypad.getKey();
  String konv_password = String(keypressed_password);
  pad_password += konv_password;

  if (keypressed_password == '1') {
    lcd.setCursor(5, 1);
    lcd.print(pad_password);
  }
  if (keypressed_password == '2') {
    lcd.print("YOOOOOOOOO");
  }

  if(keypressed_password == '=') {
    lcd.clear();
    pad_password = "";
    keypressed_password = NULL;
  }

  if(keypressed_password) {
    buzzer.beep(50);
  }

}

// ahmad - nesaei - ghavidel - sadegh - maldar - safari - ghodos - yasin
