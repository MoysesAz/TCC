#include <Arduino.h>

int pirPin = 10;      // Pino do sensor PIR
int count = 10;
int state = 0;
void setup() {
  Serial.begin(115200);
  pinMode(pirPin, INPUT);
}

void teste() {
    if (count > 0) {
      delay(500);
      count -= 1;
      if (digitalRead(pirPin) == 1) {
        count = 10;
      }
      teste();
    } else {
      Serial.println("Gato saiu do recinto!!!");
    }
}

void loop() {
    state = digitalRead(pirPin);
    if (state == 1) {
      count = 10;
      Serial.println("Gato no recinto!!!");
      teste();
    } else {
    
    }
}
