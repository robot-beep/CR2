#include <MotorDriver.h>
#include <Servo.h>

MotorDriver m;

Servo servo_brazo;
uint8_t pin_servo = 9;

const uint8_t s_izq = 6;
const uint8_t s_der = 5;

uint8_t s_izq_aux;
uint8_t s_der_aux;

uint8_t velocidad_avanzar = 50;//60;
uint8_t velocidad_aux = 30;//30;
uint8_t velocidad_retroceso = 50;//50;

const uint8_t trigger = 13;  
const uint8_t echo = A5;  

void setup() {
  pinMode(s_izq, INPUT);
  pinMode(s_der, INPUT);
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT);  
  digitalWrite(trigger, LOW);
  servo_brazo.attach(pin_servo);
  //Serial.begin(9600);
}
void loop()
{
  uint8_t lectura_s_izq = digitalRead(s_izq);
  uint8_t lectura_s_der = digitalRead(s_der);
  
  long distancia = calcular_distancia(trigger, echo);//15;

  if(distancia > 14){
    if(lectura_s_izq * lectura_s_der){
      m.motor(1,FORWARD,velocidad_avanzar);
      m.motor(2,FORWARD,velocidad_avanzar);
    }else if(lectura_s_der){
      m.motor(1,FORWARD,velocidad_avanzar);
      m.motor(2,FORWARD,velocidad_aux);
    }else if(lectura_s_izq){
      m.motor(1,FORWARD,velocidad_aux);
      m.motor(2,FORWARD,velocidad_avanzar);
    }else if(not(lectura_s_izq + lectura_s_der)){
      if(s_izq_aux){
        m.motor(1,BACKWARD,velocidad_retroceso);
        m.motor(2,FORWARD,velocidad_avanzar);  
      }else if(s_der_aux){
        m.motor(1,FORWARD,velocidad_avanzar);
        m.motor(2,BACKWARD,velocidad_retroceso);  
      }   
    }
    if(lectura_s_izq != lectura_s_der){
      s_izq_aux = lectura_s_izq;
      s_der_aux = lectura_s_der;  
    }    
  }else{
    m.motor(1,FORWARD,0);
    m.motor(2,FORWARD,0);
    mover_brazo(1);
    delay(500);
    mover_brazo(0);
    delay(500);
    mover_brazo(1);
    delay(500);
    mover_brazo(0);
    delay(500);
    m.motor(1,BACKWARD,120);
    m.motor(2,FORWARD,120);
    delay(500);
    m.motor(1,FORWARD,120);
    m.motor(1,FORWARD,120);
  }
}
void mover_brazo(uint8_t posicion){
  if(posicion == 1){
    servo_brazo.write(0);
  }else if(posicion == 0){
    servo_brazo.write(180);
  }
}
uint16_t calcular_distancia(uint8_t t, uint8_t e){

  long tiempo;
  long distancia;

  digitalWrite(t, HIGH);
  delayMicroseconds(10);    
  digitalWrite(t, LOW);
  
  tiempo = pulseIn(e, HIGH); 
  distancia = tiempo/59;           
  
  return distancia;
}
