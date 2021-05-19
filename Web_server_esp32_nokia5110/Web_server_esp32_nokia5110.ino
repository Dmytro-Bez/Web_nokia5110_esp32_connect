#include "main.h"

void setup(){
  Serial.begin(115200);

  start_config();
  spiss_init();
  vect();
  goriz();
  server_send();
}

void loop(){
}
