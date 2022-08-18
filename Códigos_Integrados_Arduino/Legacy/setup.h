#include "set_variables.h"

void setup_servo(){
  servo_brazo.attach(pin_servo);
}
void setup_ultrasonido(){
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT);  
  digitalWrite(trigger, LOW);
}
void setup_linea(){
  pinMode(s_izq, INPUT);
  pinMode(s_der, INPUT);
}
void setup_color(){
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  pinMode(sensorOut, INPUT);  
}
