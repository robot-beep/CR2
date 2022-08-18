#include <MotorDriver.h>

MotorDriver m;

const uint8_t s_izq = 13;
const uint8_t s_der = 5;

uint8_t s_izq_aux;
uint8_t s_der_aux;

uint8_t velocidad_avanzar = 60;   //76;
uint8_t velocidad_aux = 30;
uint8_t velocidad_retroceso = 50; //60;

void setup() {
  pinMode(s_izq, INPUT);
  pinMode(s_der, INPUT);
}

void loop() {
  uint8_t lectura_s_izq = digitalRead(s_izq);
  uint8_t lectura_s_der = digitalRead(s_der);

  if(lectura_s_izq == 1 && lectura_s_der == 1){
    m.motor(1,FORWARD,velocidad_avanzar);
    m.motor(2,FORWARD,velocidad_avanzar);
  }else if(lectura_s_izq == 0 && lectura_s_der == 1){
    m.motor(1,FORWARD,velocidad_avanzar);
    m.motor(2,FORWARD,velocidad_aux);
  }else if(lectura_s_izq == 1 && lectura_s_der == 0){
    m.motor(1,FORWARD,velocidad_aux);
    m.motor(2,FORWARD,velocidad_avanzar);
  }else if(lectura_s_izq == 0 && lectura_s_der == 0){
    if(s_izq_aux == 1 && s_der_aux == 0){
      m.motor(1,BACKWARD,velocidad_retroceso);
      m.motor(2,FORWARD,velocidad_avanzar);  
    }
    if(s_izq_aux == 0 && s_der_aux == 1){
      m.motor(1,FORWARD,velocidad_avanzar);
      m.motor(2,BACKWARD,velocidad_retroceso);  
    } 
  }
  if((lectura_s_izq == 0 && lectura_s_der == 1) || (lectura_s_izq == 1 && lectura_s_der == 0)){
    s_izq_aux = lectura_s_izq;
    s_der_aux = lectura_s_der;  
  }  
}
