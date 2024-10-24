#include <LiquidCrystal.h>
#include <dht.h>
#include "Timer.h"

//dht temp and hum module
dht DHT;
#define DHTPIN 12

//joystick
#define leftSide 400
#define rightSide 800
#define upSide 400
#define downSide 800
int xValue = 0;
int yValue = 0;

//initialize LCD screen
LiquidCrystal lcd(11, 10, 9, 5, 4, 3, 2);

//display temp and humidity
void TH(int p) { 
  if (p == 1) {
    DHT.temperature = (DHT.temperature * 9/5) + 32;
    lcd.setCursor(0,0); 
    lcd.print("TEMP: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("F");
    lcd.setCursor(0,1);
    lcd.print("HUMID: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
  }
  else {
    lcd.setCursor(0,0); 
    lcd.print("TEMP: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("HUMID: ");
    lcd.print(DHT.humidity);
    lcd.print("%");
  }
}

//display temp
void TEMP(int j) { 
  if (j == 1) {
    DHT.temperature = (DHT.temperature * 9/5) + 32;
    lcd.setCursor(0,0); 
    lcd.print("TEMP: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("F");
    lcd.setCursor(0,1);
    lcd.print("STAT: ");
    if(DHT.temperature < 60) {
      lcd.print("COLD");
    }
    else if(DHT.temperature >= 60 && DHT.temperature < 70) {
      lcd.print("COOL");
    }
    else if(DHT.temperature >= 70 && DHT.temperature < 80) {
      lcd.print("MILD");
    }
    else if(DHT.temperature >= 80 && DHT.temperature < 90) {
      lcd.print("WARM");
    }
    else if(DHT.temperature >= 90) {
      lcd.print("HOT");
    }
  }
  else {
    lcd.setCursor(0,0); 
    lcd.print("TEMP: ");
    lcd.print(DHT.temperature);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(0,1);
    lcd.print("STAT: ");
    if(DHT.temperature <= 15) {
      lcd.print("COLD");
    }
    else if(DHT.temperature > 15 && DHT.temperature <= 21) {
      lcd.print("COOL");
    }
    else if(DHT.temperature > 21 && DHT.temperature <= 26) {
      lcd.print("MILD");
    }
    else if(DHT.temperature > 26 && DHT.temperature <= 32) {
      lcd.print("WARM");
    }
    else if(DHT.temperature > 32) {
      lcd.print("HOT");
    }
  }
}

//display humidity
void HUM(void) { 
  lcd.setCursor(0,0); 
  lcd.print("HUMID: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("STAT: ");
  if(DHT.humidity < 25) {
    lcd.print("LOW");
  }
  else if(DHT.humidity >= 25 && DHT.humidity < 30) {
    lcd.print("GOOD");
  }
  else if(DHT.humidity >= 30 && DHT.humidity < 60) {
    lcd.print("GREAT");
  }
  else if(DHT.humidity >= 60 && DHT.humidity < 70) {
    lcd.print("GOOD");
  }
  else if(DHT.humidity >= 70) {
    lcd.print("HIGH");
  }
}

//x value joystick sm
enum STATE_XJOY {START, TEMPERATURE, HUMIDITY} gState = START;
void X_JOYSTICK(int g) {
  switch (gState) {
    case START:
    if(xValue >= rightSide) {
      gState = TEMPERATURE;
    }
    else if(xValue <= leftSide) {
      gState = HUMIDITY;
    }
    else {
      gState = START;
    }
    break;

    case TEMPERATURE:
    if(xValue >= rightSide) {
      gState = HUMIDITY;
    }
    else if(xValue <= leftSide) {
      gState = START;
    }
    else {
      gState = TEMPERATURE;
    }
    break;

    case HUMIDITY:
    if(xValue >= rightSide) {
      gState = START;
    }
    else if(xValue <= leftSide) {
      gState = TEMPERATURE;
    }
    else {
      gState = HUMIDITY;
    }
  }

  switch (gState) {
    case START:
    lcd.clear();
    TH(g);
    T_LED(g);
    break; 

    case TEMPERATURE:
    lcd.clear();
    TEMP(g);
    T_LED(g);
    break;

    case HUMIDITY:
    lcd.clear();
    HUM();
    H_LED();
  }
}

//temp led sm
enum STATE_TLED {INIT, COLD, COOL, MILD, WARM, HOT} lState = INIT;
void T_LED(int L) {
  switch (gState) {
    case INIT:
    if(L == 1) {
      if(DHT.temperature < 60) {
        lState = COLD;
      }
      else if(DHT.temperature >= 60 && DHT.temperature < 70) {
        lState = COOL;
      }
      else if(DHT.temperature >= 70 && DHT.temperature < 80) {
        lState = MILD;
      }
      else if(DHT.temperature >= 80 && DHT.temperature < 90) {
        lState = WARM;
      }
      else if(DHT.temperature >= 90) {
        lState = HOT;
      }
      else {
        lState = INIT;
      }
    }
    else {
      if(DHT.temperature <= 15) {
        lState = COLD;
      }
      else if(DHT.temperature > 15 && DHT.temperature <= 21) {
        lState = COOL;
      }
      else if(DHT.temperature > 21 && DHT.temperature <= 26) {
        lState = MILD;
      }
      else if(DHT.temperature > 26 && DHT.temperature <= 32) {
        lState = WARM;
      }
      else if(DHT.temperature > 32) {
        lState = HOT;
      }     
      else {
        lState = INIT;
      }
    }
    break;

    case COLD:
    if(L == 1) {
      if(DHT.temperature < 60) {
        lState = COLD;
      }
      else if(DHT.temperature >= 60 && DHT.temperature < 70) {
        lState = COOL;
      }
      else if(DHT.temperature >= 70 && DHT.temperature < 80) {
        lState = MILD;
      }
      else if(DHT.temperature >= 80 && DHT.temperature < 90) {
        lState = WARM;
      }
      else if(DHT.temperature >= 90) {
        lState = HOT;
      }
      else {
        lState = INIT;
      }
    }
    else {
      if(DHT.temperature <= 15) {
        lState = COLD;
      }
      else if(DHT.temperature > 15 && DHT.temperature <= 21) {
        lState = COOL;
      }
      else if(DHT.temperature > 21 && DHT.temperature <= 26) {
        lState = MILD;
      }
      else if(DHT.temperature > 26 && DHT.temperature <= 32) {
        lState = WARM;
      }
      else if(DHT.temperature > 32) {
        lState = HOT;
      }     
      else {
        lState = INIT;
      }
    }
    break;

    case COOL:
    if(L == 1) {
      if(DHT.temperature < 60) {
        lState = COLD;
      }
      else if(DHT.temperature >= 60 && DHT.temperature < 70) {
        lState = COOL;
      }
      else if(DHT.temperature >= 70 && DHT.temperature < 80) {
        lState = MILD;
      }
      else if(DHT.temperature >= 80 && DHT.temperature < 90) {
        lState = WARM;
      }
      else if(DHT.temperature >= 90) {
        lState = HOT;
      }
      else {
        lState = INIT;
      }
    }
    else {
      if(DHT.temperature <= 15) {
        lState = COLD;
      }
      else if(DHT.temperature > 15 && DHT.temperature <= 21) {
        lState = COOL;
      }
      else if(DHT.temperature > 21 && DHT.temperature <= 26) {
        lState = MILD;
      }
      else if(DHT.temperature > 26 && DHT.temperature <= 32) {
        lState = WARM;
      }
      else if(DHT.temperature > 32) {
        lState = HOT;
      }     
      else {
        lState = INIT;
      }
    }
    break;

    case MILD:
    if(L == 1) {
      if(DHT.temperature < 60) {
        lState = COLD;
      }
      else if(DHT.temperature >= 60 && DHT.temperature < 70) {
        lState = COOL;
      }
      else if(DHT.temperature >= 70 && DHT.temperature < 80) {
        lState = MILD;
      }
      else if(DHT.temperature >= 80 && DHT.temperature < 90) {
        lState = WARM;
      }
      else if(DHT.temperature >= 90) {
        lState = HOT;
      }
      else {
        lState = INIT;
      }
    }
    else {
      if(DHT.temperature <= 15) {
        lState = COLD;
      }
      else if(DHT.temperature > 15 && DHT.temperature <= 21) {
        lState = COOL;
      }
      else if(DHT.temperature > 21 && DHT.temperature <= 26) {
        lState = MILD;
      }
      else if(DHT.temperature > 26 && DHT.temperature <= 32) {
        lState = WARM;
      }
      else if(DHT.temperature > 32) {
        lState = HOT;
      }     
      else {
        lState = INIT;
      }
    }
    break;

    case WARM:
    if(L == 1) {
      if(DHT.temperature < 60) {
        lState = COLD;
      }
      else if(DHT.temperature >= 60 && DHT.temperature < 70) {
        lState = COOL;
      }
      else if(DHT.temperature >= 70 && DHT.temperature < 80) {
        lState = MILD;
      }
      else if(DHT.temperature >= 80 && DHT.temperature < 90) {
        lState = WARM;
      }
      else if(DHT.temperature >= 90) {
        lState = HOT;
      }
      else {
        lState = INIT;
      }
    }
    else {
      if(DHT.temperature <= 15) {
        lState = COLD;
      }
      else if(DHT.temperature > 15 && DHT.temperature <= 21) {
        lState = COOL;
      }
      else if(DHT.temperature > 21 && DHT.temperature <= 26) {
        lState = MILD;
      }
      else if(DHT.temperature > 26 && DHT.temperature <= 32) {
        lState = WARM;
      }
      else if(DHT.temperature > 32) {
        lState = HOT;
      }     
      else {
        lState = INIT;
      }
    }
    break;

    case HOT:
    if(L == 1) {
      if(DHT.temperature < 60) {
        lState = COLD;
      }
      else if(DHT.temperature >= 60 && DHT.temperature < 70) {
        lState = COOL;
      }
      else if(DHT.temperature >= 70 && DHT.temperature < 80) {
        lState = MILD;
      }
      else if(DHT.temperature >= 80 && DHT.temperature < 90) {
        lState = WARM;
      }
      else if(DHT.temperature >= 90) {
        lState = HOT;
      }
      else {
        lState = INIT;
      }
    }
    else {
      if(DHT.temperature <= 15) {
        lState = COLD;
      }
      else if(DHT.temperature > 15 && DHT.temperature <= 21) {
        lState = COOL;
      }
      else if(DHT.temperature > 21 && DHT.temperature <= 26) {
        lState = MILD;
      }
      else if(DHT.temperature > 26 && DHT.temperature <= 32) {
        lState = WARM;
      }
      else if(DHT.temperature > 32) {
        lState = HOT;
      }     
      else {
        lState = INIT;
      }
    }
  }

  switch (lState) {
    case INIT:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    break;

    case COLD:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    break;

    case COOL:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    break;

    case MILD:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(A2, 0);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);
    break;

    case WARM:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    analogWrite(A2, 150);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);
    break;

    case HOT:
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    analogWrite(A2, 255);
    digitalWrite(A3, HIGH);
    digitalWrite(A4, LOW);
  }
}

//hum led sm
enum STATE_HLED {IN, LOWW, LGOOD, GREAT, HGOOD, HIGHH} hState = IN;
void H_LED(void) {
  switch (hState) {
    case IN:
    if(DHT.humidity < 25) {
      hState = LOWW;
    }
    else if(DHT.humidity >= 25 && DHT.humidity < 30) {
      hState = LGOOD;
    }
    else if(DHT.humidity >= 30 && DHT.humidity < 60) {
      hState = GREAT;
    }
    else if(DHT.humidity >= 60 && DHT.humidity < 70) {
      hState = HGOOD;
    }
    else if(DHT.humidity >= 70) {
      hState = HIGHH;
    }
    else {
      hState = IN;
    }
    break;

    case LOWW:
    if(DHT.humidity < 25) {
      hState = LOWW;
    }
    else if(DHT.humidity >= 25 && DHT.humidity < 30) {
      hState = LGOOD;
    }
    else if(DHT.humidity >= 30 && DHT.humidity < 60) {
      hState = GREAT;
    }
    else if(DHT.humidity >= 60 && DHT.humidity < 70) {
      hState = HGOOD;
    }
    else if(DHT.humidity >= 70) {
      hState = HIGHH;
    }
    else {
      hState = IN;
    }
    break;

    case LGOOD:
    if(DHT.humidity < 25) {
      hState = LOWW;
    }
    else if(DHT.humidity >= 25 && DHT.humidity < 30) {
      hState = LGOOD;
    }
    else if(DHT.humidity >= 30 && DHT.humidity < 60) {
      hState = GREAT;
    }
    else if(DHT.humidity >= 60 && DHT.humidity < 70) {
      hState = HGOOD;
    }
    else if(DHT.humidity >= 70) {
      hState = HIGHH;
    }
    else {
      hState = IN;
    }
    break;

    case GREAT:
    if(DHT.humidity < 25) {
      hState = LOWW;
    }
    else if(DHT.humidity >= 25 && DHT.humidity < 30) {
      hState = LGOOD;
    }
    else if(DHT.humidity >= 30 && DHT.humidity < 60) {
      hState = GREAT;
    }
    else if(DHT.humidity >= 60 && DHT.humidity < 70) {
      hState = HGOOD;
    }
    else if(DHT.humidity >= 70) {
      hState = HIGHH;
    }
    else {
      hState = IN;
    }
    break;

    case HGOOD:
    if(DHT.humidity < 25) {
      hState = LOWW;
    }
    else if(DHT.humidity >= 25 && DHT.humidity < 30) {
      hState = LGOOD;
    }
    else if(DHT.humidity >= 30 && DHT.humidity < 60) {
      hState = GREAT;
    }
    else if(DHT.humidity >= 60 && DHT.humidity < 70) {
      hState = HGOOD;
    }
    else if(DHT.humidity >= 70) {
      hState = HIGHH;
    }
    else {
      hState = IN;
    }
    break;

    case HIGHH:
    if(DHT.humidity < 25) {
      hState = LOWW;
    }
    else if(DHT.humidity >= 25 && DHT.humidity < 30) {
      hState = LGOOD;
    }
    else if(DHT.humidity >= 30 && DHT.humidity < 60) {
      hState = GREAT;
    }
    else if(DHT.humidity >= 60 && DHT.humidity < 70) {
      hState = HGOOD;
    }
    else if(DHT.humidity >= 70) {
      hState = HIGHH;
    }
    else {
      hState = IN;
    }
  }

  switch (hState) {
    case IN:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
    break;
    
    case LOWW:
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    break;

    case LGOOD:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    break;

    case GREAT:
    digitalWrite(6, LOW);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    break;

    case HGOOD:
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    break; 

    case HIGHH:
    digitalWrite(6, HIGH);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }
}

void setup() {
  lcd.clear();
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A2, OUTPUT);
  TimerSet(400);
  TimerOn();
}

void loop() {
int chk = DHT.read11(DHTPIN);
int f;
  xValue = analogRead(A0);
  yValue = analogRead(A1);
  if(yValue <= upSide) {
    f = 1;
  }
  else if(yValue >= downSide) {
    f = 0;
  }
  X_JOYSTICK(f);
  while(!TimerFlag) {}
  TimerFlag = 0; 
}