#include "fun.h"

void setup(){
  Serial.begin(115200);

  pinMode(BUTTON_PIN,  INPUT);                                                   //Initialize the button and LED indicator
  pinMode(INFO_LED_PIN1,OUTPUT);                                                 //Initialize the button and BUTTON
  pinMode(INFO_LED_PIN2,OUTPUT);                                                 //Initialize the button and BUTTON
  attachInterrupt(BUTTON_PIN, isr, FALLING);

  start_config();
}

void loop(){
  if(conf_button_pressed){
    digitalWrite(INFO_LED_PIN2, HIGH);
    Serial.println("1");
    conf_button_pressed = false;
  } else {
    digitalWrite(INFO_LED_PIN2, LOW);
    Serial.println("0");
  }
  
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
}
