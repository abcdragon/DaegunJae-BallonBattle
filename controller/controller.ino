#include <SoftwareSerial.h>
#include <math.h>

SoftwareSerial BTSerial(10, 11);   //bluetooth module Tx:Digital 2 Rx:Digital 3

int x = A0;
int y = A1;
int mean_x = 0, mean_y = 0;
int cor_x = 0, cor_y = 0;
int range = 150;
void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  int dx = 0, dy = 0;
  for(int i = 0; i < 10; i++){
    mean_x += map(analogRead(x), 0, 700, 0, 1000);
    mean_y += map(analogRead(y), 0, 1023, 0, 1000);
  }
  cor_x = 500 - mean_x/10;
  cor_y = 500 - mean_y/10;
}

void loop() {
  // 값 보정 각 스펙트럼은 -500 <= x <= 500, -500 <= y <= 500 라고 정의함
  int dx = map(analogRead(x), 0, 700, 0, 1000) + cor_x - 500, 
      dy = map(analogRead(y), 0, 1023, 0, 1000) + cor_y - 500;
  dx *= -1;
  bool xb = (-1 * range < dx && dx < range), yb = (-1 * range < dy && dy < range);
  if(xb && yb){
    BTSerial.write('s');
  }
  else if(yb && !xb){
    if(dx >= 0) {
      Serial.print("r ");
      BTSerial.print('r');
    }
    else {
      Serial.print("l ");
      BTSerial.write('l');
    }
  }
  else if(xb && !yb){
    if(dy >= 0) {
      Serial.print("w ");
      BTSerial.write('w');
    }
    else {
      Serial.print("b ");
      BTSerial.write('b');  
    }
  }
  else if(!xb && !yb){
    if(dx >= 0 && dy >= 0) {
      Serial.print("2 ");  
      BTSerial.write('2');
    }
    if(dx >= 0 && dy < 0) {
      Serial.print("4 ");  
      BTSerial.write('4');
    }
    if(dx < 0 && dy < 0) {
      Serial.print("6 ");  
      BTSerial.write('6');
    }
    if(dx < 0 && dy >= 0) {
      Serial.print("8 ");  
      BTSerial.write('8');
    }
  }
  Serial.print("x : ");
  Serial.print(dx);
  Serial.print(" y : ");
  Serial.println(dy);
  delay(100);
}
