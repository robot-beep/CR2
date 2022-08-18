#include "librerias.h"

void setup() {
  setup_linea();
  setup_ultrasonido();
  setup_servo();
  setup_color();  
}


void loop() {
  lectura_sensores();
  mostrar_datos(); 
  seguir_linea();
 
}










/*  Si detecta un objeto
 *  detenerse
 *  abrir el brazo
 *  acercarse hasta que la distancias sea 2 cm
 *  cerrar el brazo
 *  analizar el color
 *  si es el color dar vuelta y devolverse
 *  si no es rotar 90 grados avanzar 1 seg
 *  detenerse
 *  abrir brazo
 *  retroceder 
 *  girar 90 grados y volver a la pista hasta detectar otro objeto
 *  si encuentro el objeto se devuelve con el
 */
