#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

int M1Velocity = 5;
int M1Direction = 4;
int M2Velocity = 6;
int M2Direction = 7;

// M1 = right, M2 = left
short stopTime = 100;
void baseMove(bool l_State, bool r_State, short lv, short rv){
  digitalWrite(M1Direction, r_State);
  analogWrite(M1Velocity, rv);
  digitalWrite(M2Direction, l_State);
  analogWrite(M2Velocity, lv);
}

void stop(int st){
  analogWrite(M1Velocity, 0);
  analogWrite(M2Velocity, 0);
  delay(st);
}

void back(int velocity){ baseMove(LOW, HIGH, velocity, velocity); }
void right(int lv, int rv){ baseMove(HIGH, HIGH, lv, rv); }
void left(int lv, int rv){ baseMove(LOW, LOW, lv, rv); }
void ford(int velocity){ baseMove(HIGH, LOW, velocity, velocity); }
void b_left(int bv, int sub){ baseMove(LOW, HIGH, bv-sub, bv); } // bv ==> base velocity
void f_left(int bv, int sub){ baseMove(HIGH, LOW, bv-sub, bv); } // bv ==> base velocity
void f_right(int bv, int sub){ baseMove(HIGH, LOW, bv, bv-sub); } // bv ==> base velocity
void b_right(int bv, int sub){ baseMove(LOW, HIGH, bv, bv-sub); } // bv ==> base velocity

void setup() {
  pinMode(M1Direction, OUTPUT);
  pinMode(M1Velocity, OUTPUT);
  pinMode(M2Direction, OUTPUT);
  pinMode(M2Velocity, OUTPUT);

  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  Serial.print("ss : ");
  if(mySerial.available()){
    char ss = mySerial.read();
    Serial.print(ss);
    if(ss == 's') stop(100);
    else if(ss == 'w') ford(255);
    else if(ss == 'b') back(255);
    else if(ss == 'l') left(255, 255);
    else if(ss == 'r') right(255, 255);
    else if(ss == '2') f_right(255, 105);
    else if(ss == '4') b_right(255, 105);
    else if(ss == '6') b_left(255, 105);
    else if(ss == '8') f_left(255, 105);
  }
  Serial.println();
}
