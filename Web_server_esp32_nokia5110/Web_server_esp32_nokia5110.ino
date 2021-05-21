#include "main.h"

void setup(){
  Serial.begin(115200);

  start_config();
  vect();
  goriz();
  
//  pr_win();
  return_game();
//  server_send();
}

void loop(){
//  if(!matrix_check()){                                //Check array on the win
//    return_game();
//    //move_win();                                       //If someone wins, go to the first menu and repeat the process of filling the matrix
//  } else {
//    move_win();
//    //return_game();                                    //If not, then the problems with entering the matrix or field are not filled
//  }
}
