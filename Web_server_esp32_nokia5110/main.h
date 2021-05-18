#ifndef funk_h
#define funk_h

#include <WiFi.h>                                         //Connect lib.work wifi
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>

/*----------DEFINES----------*/
#define Led 2
/*----------VARIABLES----------*/
AsyncWebServer server(80);

/*----------PROTOTYPE FUNCTIONS----------*/
void start_config();                                      //Settings function  
void connect_wifi();                                      //Function connect Wifi
void notFound(AsyncWebServerRequest *request);
void spiss_init();
void server_send();
void notFound(AsyncWebServerRequest *request);
/*----------FUNKTIONS----------*/
void start_config() {
  Serial.println("Start config mode");                    //Add function setting 
  connect_wifi();                                         //Function connect Wifi
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
    digitalWrite(Led, HIGH);
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest * request){ 
    digitalWrite(Led, LOW);
    request->send(SPIFFS, "/index.html", "text/html");
  });
  server.onNotFound(notFound);
  server.begin();
}
void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page not found");
}
#endif
