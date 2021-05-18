#include "main.h"

void setup(){
  Serial.begin(115200);

  start_config();
  spiss_init();
  server_send();
}

void loop(){
}
