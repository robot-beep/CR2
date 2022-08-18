const uint8_t trigger = 2;  
const uint8_t echo = 3;  

void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT); 
  pinMode(echo, INPUT);  
  digitalWrite(trigger, LOW);
}
void loop()
{
  long distancia = calcular_distancia(trigger, echo);
  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(100);
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
