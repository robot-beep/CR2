#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);

  pinMode(sensorOut, INPUT);

  Serial.begin(9600);
}

void loop() {
  redPW = getRedPW();
  delay(20);
  greenPW = getGreenPW();
  delay(200);
  bluePW = getBluePW();
  delay(200);

  getColor(redPW, bluePW, greenPW);

  /*
  Serial.print("Rojo PW = ");
  Serial.print(redPW);
  Serial.print(" | Verde PW = ");
  Serial.print(greenPW);
  Serial.print(" | Azul PW = ");
  Serial.println(bluePW);
  */
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

char getColor(int red, int blue, int green){
  if(red < blue and red < blue){
      Serial.println("el color es rojo");
    }
   if(blue < red and blue < green){
      Serial.println("el color es blue");
    }
   if(green < blue and green < red){
      Serial.println("el color es green");
    } 
  
  }
