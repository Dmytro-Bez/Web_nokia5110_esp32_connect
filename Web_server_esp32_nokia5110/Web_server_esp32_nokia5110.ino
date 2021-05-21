#include "fun.h"

void setup(){
  Serial.begin(115200);

  start_config();
  vect();
  goriz();
  
  pr_win();
//  return_game();
//  server_send();
}

void loop(){

}
