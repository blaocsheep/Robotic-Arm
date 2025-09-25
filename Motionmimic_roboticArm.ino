#include <Servo.h>

int flexpin0= A0;
int flexpin1= A1;
int flexpin2= A2;
int flexpin3= A3;
int flexpin4= A4;

Servo finger0;
Servo finger1;
Servo finger2;
Servo finger3;
Servo finger4;

bool F0=false;
bool F1=false;
bool F2=false;
bool F3=false;
bool F4=false;

void setup() {
  Serial.begin(9600);
  finger0.attach(13);
  finger1.attach(12);
  finger2.attach(11);
  finger3.attach(10);
  finger4.attach(9);
  Serial.println("setup complete");
}

void loop() {
  int flexVal0= analogRead(flexpin0);
  int flexVal1= analogRead(flexpin1);
  int flexVal2= analogRead(flexpin2);
  int flexVal3= analogRead(flexpin3);
  int flexVal4= analogRead(flexpin4);
//thumb
  if(F0&&flexVal0>180){
      finger0.write(60);//if not bent and prev bent then cw
      F0=false;
      Serial.println("0.0 ");
  }
  else if(!F0&&flexVal0<180){
      finger0.write(120);//if not bent and prev bent then ccw
      F0=true;
      Serial.println("0.1 ");
  }
//pointer
  if(F1&&flexVal1>180){
      finger1.write(120);//if not bent and prev bent then ccw
      F1=false;
      Serial.print("1.0 ");
  }
  else if(!F1&&flexVal1<180){
      finger1.write(60);//if not bent and prev bent then cw
      F1=true;
      Serial.print("1.1 ");
  }
  //middle finger
  if(F2&&flexVal2>180){
      finger2.write(120);//if not bent and prev bent then ccw
      F2=false;
      Serial.print("2.0 ");
  }
  else if(!F2&&flexVal2<180){
      finger2.write(60);//if not bent and prev bent then cw
      F2=true;
      Serial.print("2.1 ");
  }
  //ring finger
  if(F3&&flexVal3>180){
      finger3.write(60);//if not bent and prev bent then cw
      F3=false;
      Serial.print("3.0 ");
  }
  else if(!F3&&flexVal3<180){
      finger3.write(120);//if not bent and prev bent then ccw
      F3=true;
      Serial.print("3.1 ");
  }
  //pinky
  if(F4&&flexVal4>180){
      finger4.write(60);//if not bent and prev bent then cw
      F4=false;
      Serial.print("4.0 ");
  }
  else if(!F4&&flexVal4<180){
      finger4.write(120);//if not bent and prev bent then ccw
      F4=true;
      Serial.print("4.1 ");
  }

  delay(600);
  finger0.write(90);
  finger1.write(90);
  finger2.write(90);
  finger3.write(90);
  finger4.write(90);
  //delay(1000);


  Serial.print("Sensor0: ");
  Serial.print(flexVal0);
  Serial.print("  Sensor1: ");
  Serial.print(flexVal1);
  Serial.print("  Sensor2: ");
  Serial.print(flexVal2);
  Serial.print("  Sensor3: ");
  Serial.print(flexVal3);
  Serial.print("  Sensor4: ");
  Serial.print(flexVal4);
  Serial.println();
 // delay(1000);


}
