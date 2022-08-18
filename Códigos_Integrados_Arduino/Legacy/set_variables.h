#define S0 A0
#define S1 A1
#define S2 A2
#define S3 A3
#define sensorOut A4

MotorDriver m;

uint8_t lectura_s_izq;
uint8_t lectura_s_der;
long distancia;

int redPW = 0;
int greenPW = 0;
int bluePW = 0;

const uint8_t s_izq = 6;
const uint8_t s_der = 5;

const uint8_t trigger = 13;  
const uint8_t echo = A5;

uint8_t s_izq_aux;
uint8_t s_der_aux;

uint8_t velocidad_avanzar = 60;   //76;
uint8_t velocidad_aux = 30;
uint8_t velocidad_retroceso = 50; //60;

Servo servo_brazo;
uint8_t pin_servo = 9;
