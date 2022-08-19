#include <MotorDriver.h>
#include <Servo.h>

//sensores
#define S0 A0
#define S1 A1
#define S2 16
#define S3 17
#define sensorOut 18

MotorDriver m;

Servo servo_brazo;
uint8_t pin_servo = 9;

const uint8_t s_izq = 15;
const uint8_t s_der = 14;

uint8_t s_izq_aux;
uint8_t s_der_aux;

uint8_t velocidad_avanzar = 100;//60;
uint8_t velocidad_aux = 50;//30;
uint8_t velocidad_retroceso = 80;//50;

const uint8_t trigger = 13;  
const uint8_t echo = 19; //A5  

void setup() {
  // put your setup code here, to run once:
  //sensor de color 
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(sensorOut, INPUT);

  //seguidor de lineas
  
  pinMode(s_izq, INPUT);
  pinMode(s_der, INPUT);

  //ultrasonido
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT);  
  digitalWrite(trigger, LOW);

  //servomotor
  servo_brazo.attach(pin_servo);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  //servomotor
  mover_brazo(1); 
  delay(500);
  mover_brazo(0);
  delay(500);
  mover_brazo(1); 
  delay(500);
  mover_brazo(0);
  delay(2000);


  //sensor de ultrasonido
//  for(int i=0; i<1000; i++){
//    long distancia = calcular_distancia(trigger, echo);//15;
//    Serial.println(distancia);
//  }
  

  //seguidor de lineas

  while(true){
    long distancia = calcular_distancia(trigger, echo);
    Serial.println(distancia);
    
    uint8_t lectura_s_izq = digitalRead(s_izq);
    uint8_t lectura_s_der = digitalRead(s_der);

    
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
    if(distancia < 10 and distancia !=0){
      m.motor(1,FORWARD,0);
      m.motor(2,FORWARD,0);  
      delay(500);
      saludar();
      delay(1000);
      girar180();
      delay(1500);
    }   
  }
}

void mover_brazo(uint8_t posicion){
  if(posicion == 1){
    servo_brazo.write(0);
  }else if(posicion == 0){
    servo_brazo.write(90);
  }
}

int calcular_distancia(uint8_t t, uint8_t e){

  long tiempo;
  int distancia;

  digitalWrite(t, HIGH);
  delayMicroseconds(10);    
  digitalWrite(t, LOW);
  
  tiempo = pulseIn(e, HIGH, 5000); 
  distancia = tiempo/59;           
  
  return distancia;
}

//gira al robot 180° (falta probarlo)
void girar180(){
  m.motor(1,FORWARD,60); 
  m.motor(2,BACKWARD,60);
  delay(100);
}

//está funcion devuelve "0" si el color es rojo, "1" si el color es verde y "2" si el color es azul. (por revisar)
uint8_t color(){
  int redPW = getRedPW();
  int greenPW = getGreenPW();
  int bluePW = getBluePW();
  Serial.print(" Rojo: ");
  Serial.print(redPW); 
  Serial.print(" Verde: ");
  Serial.print(greenPW); 
  Serial.print(" Blue: ");
  Serial.print(bluePW);
  
}

int getRedPW() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

int getGreenPW() {
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

int getBluePW() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  int PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

void saludar(){
  mover_brazo(0); 
  delay(200); 
  mover_brazo(1); 
  delay(200); 
}
