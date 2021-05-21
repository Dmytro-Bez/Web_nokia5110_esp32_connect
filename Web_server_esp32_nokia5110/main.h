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

#define SIZE 3                                            //size arr
/*----------VARIABLES----------*/
bool O_win = false;                                       //Variable win '0'
bool X_win = false;                                       //Variable win 'X'
int Array[SIZE][SIZE] = {{0,0,0}, {0,1,0}, {0,0,1}};      //Create test array

AsyncWebServer server(80);
Adafruit_PCD8544 display = Adafruit_PCD8544(D8, D7, D6, D5, D2);
/*----------PROTOTYPE FUNCTIONS----------*/
void start_config();                                      //Settings function  
void connect_wifi();                                      //Function connect Wifi
void vect();
void goriz();
bool matrix_check();
void move_win();
void pr_win();
void return_game();
/*----------FUNKTIONS----------*/
void start_config() {
  Serial.println("Start config mode");                    //Add function setting 
  connect_wifi();                                         //Function connect Wifi
  display.begin();
  display.setContrast(70);
  display.clearDisplay();
  pr_win();                                           //Testing win
}

void connect_wifi(){                                     //Create function connect wifi
  WiFi.softAP("ESP32", "");
  Serial.println("softAP");
  Serial.println("");
  Serial.println(WiFi.softAPIP());
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

void move_win(){                                            //Create function move win
  if(O_win){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(0,0);
    display.println("User won: 0");
    display.display();
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(BLACK, WHITE);
    display.setCursor(1,1);        
    display.print("User won: X");
    display.display();
  } 
}

bool matrix_check(){                                      //Create function matrix check
  bool status_arr = false;
  
  for(int i = 0; i < 3; i++){                             //Check the horizontals of the diagonals
    if((Array[0][i] == Array[1][i]) && (Array[0][i] == Array[2][i])) {
      if(Array[0][i] == 0){
        O_win = true;
        status_arr = true;
      }
        else if(Array[0][i] == 1){
          X_win = true;
          status_arr = true;
        }
    }
    for(int j = 0; j < 3; j++){                           //Check the verticals of the diagonal
      if((Array[j][0] == Array[j][1]) && (Array[j][0] == Array[j][2])) {
        if(Array[j][0] == 0){
          O_win = true;
          status_arr = true; 
        }
          else if(Array[j][0] == 1){
            X_win = true;
            status_arr = true;
          }
        }
      }
    }
    if ((Array[0][0] == Array[1][1]) && (Array[1][1] == Array[2][2])) {   //Check the winning diagonals
      if (Array[0][0] == 0){
        O_win = true;
        status_arr = true; 
      }
      else if (Array[0][0] == 1){
        X_win = true;
        status_arr = true;
      }
    }
    if((Array[0][2] == Array[1][1]) && (Array[1][1] == Array[2][0])) {    //Check the winning diagonals
      if(Array[0][2] == 0){
        O_win = true;
        status_arr = true; 
      }
      else if (Array[0][2] == 1){
        X_win = true;
      }
    }
    //Serial.print(status_arr);
    return status_arr; 
}

void pr_win(){                                              //Create function printing win
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  for(int i = 0; i < SIZE; i++){                            //Create cycle in cycle to fill
    for(int j = 0; j < SIZE; j++){
      if(Array[j][i] == 0){
        display.setCursor(12+i*28,6+j*15);             
        display.println("0"); 
        display.display();
      } else if(Array[j][i] == 1){
        display.setCursor(12+i*28,6+j*15);             
        display.println("X");
        display.display();
      }
    }
  }
}

void return_game(){                                       //Create function return game
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);      
  display.setCursor(0,0);             
  display.println("Start a new");
  display.print("game!");
  display.setCursor(0,20); 
  display.println("Please.");
  display.println("!!!"); 
  display.display();
}

#endif
