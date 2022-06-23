#include "SevenSegmentTM1637.h"
#include <EEPROM.h>

#define CLK 4
#define DIO 5

#define IR_Sensor 6
#define relay1 7
#define relay2 8
#define Ploten A0

int Ploten_stat = 0;
int Map_ploten = 0;
int IR_stat = 0;
int addr = 0;

SevenSegmentTM1637    display(CLK, DIO);

void setup() {

  Serial.begin(9600);
  display.begin();
  display.setBacklight(100);
  pinMode(Ploten, INPUT);
  pinMode(IR_Sensor, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);

  EEPROM.read(addr);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);


}

void loop() {
  Ploten_stat = analogRead(Ploten);
  IR_stat = digitalRead(IR_Sensor);

  Serial.print("Ploten : ");
  Serial.println(Ploten_stat);

  Map_ploten = map(Ploten_stat, 0, 1024, 0, 16);
  Serial.print("Map_ploten : ");
  Serial.println(Map_ploten);


  if (IR_stat == 0) {

    display.print("ON");
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    display.blink();

    for (Map_ploten; Map_ploten >= 0; Map_ploten--) {
      display.clear();
      display.print(Map_ploten);
      delay(1000);
    }

    digitalWrite(relay1, HIGH);
    digitalWrite(relay2, HIGH);
    display.print("OFF");
    display.blink();
    display.clear();

  }

  if ( Map_ploten != Map_ploten) {
    EEPROM.write(addr, Map_ploten);
  }
  
  display.clear();
  display.print(Map_ploten);
  delay(50);

}
