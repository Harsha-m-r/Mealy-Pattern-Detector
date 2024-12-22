////////////////////////////////////////////////////////////////////////////////
// 15bit Sequence Sender 
//
// LCD Display (LiquidCrystal_I2C):
//   VCC  -------------- Arduino 5V
//   GND  -------------- Arduino GND
//   SDA  -------------- Arduino A4
//   SCL  -------------- Arduino A5
//
// Buttons:
//   up_button    ------ Arduino digital pin 10
//   down_button  ------ Arduino digital pin 11
//   select_button------ Arduino digital pin 12
//   zero_button  ------ Arduino digital pin 6
//   one_button   ------ Arduino digital pin 7
//
// LED:
//   LED anode (longer leg)  ------ Arduino digital pin 5
//   LED cathode (shorter leg) ------ Arduino GND
//
// Additional Components:
//   - 220-ohm resistor for LED current limiting
//   - Push buttons for user input (up, down, select, 0, 1)
//
// Description:
// This Arduino project implements 15bit Sequence Sender using an LCD display
// to show menu options and sequence outputs. It uses buttons for navigation
// and sequence input, with an LED indicating detection of a specific sequence.
////////////////////////////////////////////////////////////////////////////////

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int up_button = 10;
int down_button = 11;
int select_button = 12;
int zero_button = 6;
int one_button = 7;
int menu = 1;
int led = 5;

String manual_sequence = "";

bool manual_mode_entered = false;
bool manual_mode_executed = false;
bool select_button_pressed = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(zero_button, INPUT_PULLUP);
  pinMode(one_button, INPUT_PULLUP);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("sequence ");
  lcd.setCursor(0, 1);
  lcd.print("     detector!!");
  delay(2000);

  pinMode(up_button, INPUT_PULLUP);
  pinMode(down_button, INPUT_PULLUP);
  pinMode(select_button, INPUT_PULLUP);

  update_menu();
}

void loop() {
  if (!digitalRead(down_button)) {
    menu++;
    update_menu();
    delay(100);
    while (!digitalRead(down_button));
  }
  if (!digitalRead(up_button)) {
    menu--;
    update_menu();
    delay(100);
    while (!digitalRead(up_button));
  }
  
  select_button_pressed = digitalRead(select_button) ? false : true;

  if (menu == 6 && manual_mode_entered && !manual_mode_executed && select_button_pressed) {
    handle_manual_mode();
  } else if (select_button_pressed) {
    execute_action();
    update_menu();
    delay(100);
    while (!digitalRead(select_button));
  }
}

void update_menu() {
  if (menu > 6) {
    menu = 1;
  } else if (menu < 1) {
    menu = 6;
  }

  lcd.clear();
  switch (menu) {
    case 1:
      lcd.print(">info");
      lcd.setCursor(0, 1);
      lcd.print(" preloaded 1");
      manual_mode_entered = false;
      break;
    case 2:
      lcd.print(" info");
      lcd.setCursor(0, 1);
      lcd.print(">preloaded 1");
      manual_mode_entered = false;
      break;
    case 3:
      lcd.print(">preloaded 2");
      lcd.setCursor(0, 1);
      lcd.print(" preloaded 3");
      manual_mode_entered = false;
      break;
    case 4:
      lcd.print(" preloaded 2");
      lcd.setCursor(0, 1);
      lcd.print(">preloaded 3");
      manual_mode_entered = false;
      break;
    case 5:
      lcd.print(">preloaded 4");
      lcd.setCursor(0, 1);
      lcd.print(" manual");
      manual_mode_entered = false;
      break;
    case 6:
      lcd.print(" preloaded 4");
      lcd.setCursor(0, 1);
      lcd.print(">manual");
      manual_mode_entered = true;
      manual_mode_executed = false;
      break;
  }
}

void execute_action() {
  switch (menu) {
    case 1:
      action1();
      break;
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4:
      action4();
      break;
    case 5:
      action5();
      break;
    case 6:
      if (manual_mode_entered) {
        lcd.clear();
        lcd.print(" manual mode");
        lcd.setCursor(0, 1);
        lcd.print(" press start");
        delay(1000);
      }
      break;
  }
}

void handle_manual_mode() {
  lcd.clear();
  lcd.print("enter sequence");
  lcd.setCursor(0, 1);
  lcd.blink();

  manual_sequence = "";

  while (manual_sequence.length() < 15) {
    if (!digitalRead(zero_button)) {
      manual_sequence += '0';
      lcd.print('0');
      delay(200);
    }
    if (!digitalRead(one_button)) {
      manual_sequence += '1';
      lcd.print('1');
      delay(200);
    }
  }

  lcd.noBlink();

  execute_manual_sequence();
  manual_mode_executed = true;
  update_menu();
  delay(100);
  while (!digitalRead(select_button));
}

void execute_manual_sequence() {
  lcd.clear();
  lcd.print("executing manual");
  lcd.setCursor(0, 1);
  lcd.print(" sequence...");
  delay(1000);

  execute_sequence(manual_sequence, 15);

  digitalWrite(led, LOW);
}

void execute_sequence(String sequence, int sequence_length) {
  for (int i = sequence_length - 1; i >= 0; i--) {
    lcd.setCursor(0, 1);
    lcd.print(sequence);
    lcd.setCursor(sequence_length - i - 1, 1);

    char current_bit = sequence.charAt(i);

    if (current_bit == '1') {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
    } else {
      digitalWrite(led, LOW);
      delay(1100);
    }

    sequence.remove(i, 1);

    lcd.clear();
  }

  lcd.clear();
  for (int blink_count = 0; blink_count < 3; blink_count++) {
    lcd.print("     over !!");
    delay(500);
    lcd.clear();
    delay(500);
  }

  lcd.clear();
  lcd.print("     over !!");
  delay(2000);
}

void action1() {
  lcd.clear();
  lcd.print("sequence ");
  lcd.setCursor(0, 1);
  lcd.print("     detector!!");
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.print("to be detected");
  lcd.setCursor(0, 1);
  lcd.print("4bit :- 1111    ");
  delay(2000);
}

void action2() {
  lcd.clear();
  lcd.print("sequence 1");
  lcd.setCursor(0, 1);

  String sequence = "010111011110101";
  int sequence_length = sequence.length();

  execute_sequence(sequence, sequence_length);
}

void action3() {
  lcd.clear();
  lcd.print("sequence 2");
  lcd.setCursor(0, 1);

  String sequence = "011110111011111";
  int sequence_length = sequence.length();

  execute_sequence(sequence, sequence_length);
}

void action4() {
  lcd.clear();
  lcd.print("sequence 3");
  lcd.setCursor(0, 1);

  String sequence = "111110111101111";
  int sequence_length = sequence.length();

  execute_sequence(sequence, sequence_length);
}

void action5() {
  lcd.clear();
  lcd.print("sequence 4");
  lcd.setCursor(0, 1);

  String sequence = "010110101010101";
  int sequence_length = sequence.length();

  execute_sequence(sequence, sequence_length);
}
