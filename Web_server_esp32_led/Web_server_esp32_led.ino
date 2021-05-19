#include "main.h"

void setup(){
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  
  start_config();
  spiss_init();
  server_send();
}

void loop(){
}
