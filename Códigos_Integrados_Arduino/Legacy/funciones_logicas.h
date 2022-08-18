void mostrar_datos(){
  Serial.print("s_izq: ");
  Serial.print(lectura_s_izq);
  Serial.print(" | s_der: ");
  Serial.print(lectura_s_der);
  Serial.print(" | distancia: ");
  Serial.println(distancia);
  Serial.print("Rojo PW = ");
  Serial.print(redPW);
  Serial.print(" | Verde PW = ");
  Serial.print(greenPW);
  Serial.print(" | Azul PW = ");
  Serial.println(bluePW);
}
void seguir_linea(){
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
    }else if(s_izq_aux == 0 && s_der_aux == 1){
      m.motor(1,FORWARD,velocidad_avanzar);
      m.motor(2,BACKWARD,velocidad_retroceso);  
    }   
  }
  if((lectura_s_izq == 0 && lectura_s_der == 1) || (lectura_s_izq == 1 && lectura_s_der == 0)){
    s_izq_aux = lectura_s_izq;
    s_der_aux = lectura_s_der;  
  }
}
uint16_t calcular_distancia(uint8_t t, uint8_t e){

  long tiempo;
  long distancia;

  digitalWrite(t, HIGH);
  delayMicroseconds(10);    
  digitalWrite(t, LOW);
  
  tiempo = pulseIn(e, HIGH); 
  distancia = t/59;           
  
  return distancia;
}

void mover_brazo(uint8_t posicion){
  if(posicion == 1){
    servo_brazo.write(0);
  }else if(posicion == 0){
    servo_brazo.write(180);
  }
}

uint16_t getRedPW() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  uint16_t PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

uint16_t getGreenPW() {
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  uint16_t PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

uint16_t getBluePW() {
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  uint16_t PW;
  PW = pulseIn(sensorOut, LOW);
  return PW;
}

void lectura_sensores(){
  
  lectura_s_izq = digitalRead(s_izq);
  lectura_s_der = digitalRead(s_der);
  
  distancia = calcular_distancia(trigger, echo);
  
  redPW = getRedPW();
  delay(10);
  greenPW = getGreenPW();
  delay(10);
  bluePW = getBluePW();
  delay(10);

}
