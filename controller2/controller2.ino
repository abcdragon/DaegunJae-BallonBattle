#include <SoftwareSerial.h>
#include <math.h>

SoftwareSerial BTSerial(12, 13);   //bluetooth module Tx:Digital 2 Rx:Digital 3
int r = 8, b = 11, l = 9, w = 10;


void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(r, INPUT);pinMode(w, INPUT);pinMode(b, INPUT);pinMode(l, INPUT);
}

void loop() {
  bool cw = digitalRead(w), cb = digitalRead(b), cl = digitalRead(l), cr = digitalRead(r);
  Serial.print(cw);
  Serial.print(',');
  Serial.print(cb);
  Serial.print(',');
  Serial.print(cr);
  Serial.print(',');
  Serial.print(cl);
  Serial.print(',');
  if(!cw && !cb && !cl && !cr){ // ss
    Serial.print('s');
    BTSerial.write('s');  
  }
  else if(cw && !cb && !cl && !cr){ // w
    Serial.print('w');
    BTSerial.write('w');  
  }else if(cw && !cb && cl && !cr){ // lw
    Serial.print('8');
    BTSerial.write('8');  
  }else if(cw && !cb && !cl && cr){ // rw
    Serial.print("2");
    BTSerial.write('2');  
  }else if(!cw && cb && !cl && !cr){ // b
    Serial.print("b");
    BTSerial.write('b');  
  }else if(!cw && cb && cl && !cr){ // lb
    Serial.print("6");
    BTSerial.write('6');  
  }else if(!cw && cb && !cl && cr){ // rb
    Serial.print("4");
    BTSerial.write('4');  
  }else if(!cw && !cb && cl && !cr){ // l
    Serial.print("l");
    BTSerial.write('l');  
  }else if(!cw && !cb && !cl && cr){ // r
    Serial.print("r");
    BTSerial.write('r');  
  }
  Serial.println();
  delay(100);
}
