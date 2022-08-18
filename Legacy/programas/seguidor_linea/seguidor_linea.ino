const uint8_t s_izq = 9;
const uint8_t s_der = 8;

void setup() {
  Serial.begin(9600);
  pinMode(s_izq, INPUT);
  pinMode(s_der, INPUT);
  
}

void loop() {
  uint8_t lectura_s_izq = digitalRead(s_izq);
  uint8_t lectura_s_der = digitalRead(s_der);
 
  Serial.print("sensor izquerdo: ");
  Serial.print(lectura_s_izq);
  Serial.print("sensor derecho: ");
  Serial.println(lectura_s_der);

  if(lectura_s_izq == 1 && lectura_s_der == 1){
    //motor_izquierdo_go
    //motor_derecho_go
  }
  if(lectura_s_izq == 0 && lectura_s_der == 1){
    //motor_izquierdo_go
    //motor_derecho_stop
  }
  if(lectura_s_izq == 1 && lectura_s_der == 0){
    //motor_izquierdo_stop
    //motor_derecho_go
  }
  
  delay(10);
}
