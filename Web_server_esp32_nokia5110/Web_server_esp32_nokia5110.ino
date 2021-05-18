#include <WiFi.h>
#include "SPIFFS.h"
#include <ESPAsyncWebServer.h>

#define Led 2

void notFound(AsyncWebServerRequest *request);

AsyncWebServer server(80);

void setup(){
  Serial.begin(115200);
  pinMode(Led, OUTPUT);
  
  WiFi.softAP("ESP32", "");
  Serial.println("softAP");
  Serial.println("");
  Serial.println(WiFi.softAPIP());

  // Initialize SPIFFS
  if(!SPIFFS.begin(true)){
    Serial.println("A ocurrido un error al montando SPIFFS");
    return;
  }
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request){
    request->send(SPIFFS, "/index.html", "text/html");
  });

   server.on("/led/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, HIGH);
  request->send(SPIFFS, "/index.html", "text/html");
  });

  server.on("/led/off", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(Led, LOW);
  request->send(SPIFFS, "/index.html", "text/html");
  });

  server.onNotFound(notFound);

  server.begin();  // Finalmente inciamos el servidor
}


void loop(void)
{
}
void notFound(AsyncWebServerRequest *request){
  request->send(404, "text/plain", "Page not found");
}
