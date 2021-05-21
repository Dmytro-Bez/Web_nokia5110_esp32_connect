#include "fun.h"

void setup(){
  Serial.begin(115200);

  pinMode(BUTTON_PIN,  INPUT_PULLUP);                                                   //Initialize the button and LED indicator
  pinMode(INFO_LED_PIN,OUTPUT);                                                         //Initialize the button and BUTTON
  attachInterrupt(BUTTON_PIN, isr, FALLING);

  if (String(conf_wifi_ssid) == "" ||  String(conf_wifi_password) == ""){               //if we don't have credentials to wifi then lets start ble for initialization
    start_config();
    vect();
    horiz();
  
    pr_win();
//  return_game();
//  server_send();
  } else {   
    start_transfer();
  }
}

void loop(){
  switch(a_status){
    case WIFI_ERROR:
      info_blink(WIFI_ERROR_CODE);
      connect_to_wifi();
      break;
    case AWS_ERROR:
      info_blink(AWS_ERROR_CODE);
      return;
    default:
      break;
  }
  if(conf_button_pressed){               //Activation button pressed
    start_config();
    send_data_to_aws();
  } 
}
