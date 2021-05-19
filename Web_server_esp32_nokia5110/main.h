#ifndef funk_h
#define funk_h

#include <WiFi.h>                                         //Connect lib.work wifi
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>
/*LCD*/
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
/*----------DEFINES----------*/
#define D8 18          //Serial clock out (SCLK)
#define D7 23          //Serial data out (DIN)
#define D6 19          //Data/Command select (D/C)
#define D5 5           //LCD chip select (CS)
#define D2 14          //LCD reset (RST)
/*----------VARIABLES----------*/
AsyncWebServer server(80);
Adafruit_PCD8544 display = Adafruit_PCD8544(D8, D7, D6, D5, D2);
/*----------PROTOTYPE FUNCTIONS----------*/
void start_config();                                      //Settings function  
void connect_wifi();                                      //Function connect Wifi
void notFound(AsyncWebServerRequest *request);
void spiss_init();
void server_send();
void vect();
void goriz();
/*----------FUNKTIONS----------*/
void start_config() {
  Serial.println("Start config mode");                    //Add function setting 
  connect_wifi();                                         //Function connect Wifi
  display.begin();
  display.setContrast(10);
  display.clearDisplay();
}
void connect_wifi(){                                     //Create function connect wifi
  WiFi.softAP("ESP32", "");
  Serial.println("softAP");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
}

void spiss_init(){                                       // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("ERROR!");
    return;
  }
}

void server_send(){  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    digitalWrite(Led, HIGH);
    display.setTextSize(2);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(9,1);
    display.println("X");
    display.display();
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest * request){ 
//    digitalWrite(Led, LOW);
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(9,1);
    display.println("0");
    display.display();
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.onNotFound(notFound);
  server.begin();
}
void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page not found");
}

void vect(){
  for(int i = 0; i < 47; i++){
    display.drawFastHLine(28,i,0,BLACK);
    display.display();
  }
  for(int j = 0; j < 47; j++){
    display.drawFastHLine(56,j,0,BLACK);
    display.display();
  }
}

void goriz(){
  display.drawFastHLine(0,16,83,BLACK);
  display.display();
  display.drawFastHLine(0,32,83,BLACK);
  display.display();
}

#endif
