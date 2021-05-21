#ifndef funk_h
#define funk_h

#include "def.h"                                          //Added include defines
#include "inc.h"                                          //Added include lib
#include "var.h"                                          //Added include viablea
#include "key.h"                                          //Added include key

Adafruit_PCD8544 display = Adafruit_PCD8544(D8, D7, D6, D5, D2);            //Protot. object display LCD
MQTTClient client = MQTTClient(256);                                        //Protot. object Client
WiFiClientSecure net = WiFiClientSecure();                                  //Protot. object WiFiClient

/*----------PROTOTYPE FUNCTIONS----------*/
void start_config();                                      //Settings function  
void vect();                                              //Function vertical 
void horiz();                                             //Function horizontal
bool matrix_check();                                      //Function matrix check
void move_win();                                          //Function move win
void pr_win();                                            //Function printing win
void return_game();                                       //Function return game
bool connect_to_wifi();                                   //Function connect to network
bool connect_to_aws();                                    //Function connect aws
void send_data_to_aws();                                  //Send data on the aws
void message_handler(String &topic, String &payload);     //Forming a letter to send
void start_transfer();                                    //Starts wifi and connects to aws to start transfering data
void info_blink(int code_array[]);                        //Indication and data transmission 
void IRAM_ATTR isr();                                     //Button interuption funtion
void ScanObjectTemp();                                    //Function of reading data from the D6T sensor

/*----------FUNKTIONS----------*/
void start_config() {
  Serial.println("Start config mode");                    //Add function setting 
  connect_to_wifi();                                         //Function connect Wifi
  display.begin();                                        //Init display
  display.setContrast(70);                                //Contrast
  display.clearDisplay();                                 //Clear display
  pr_win();                                               //Testing win
}

void vect(){                                              //Create function vertical
  for(int i = 0; i < 47; i++){
    display.drawFastHLine(28,i,0,BLACK);
    display.display();
  }
  for(int j = 0; j < 47; j++){
    display.drawFastHLine(56,j,0,BLACK);
    display.display();
  }
}

void horiz(){                                             //Create function horizontal
  display.drawFastHLine(0,16,83,BLACK);
  display.display();
  display.drawFastHLine(0,32,83,BLACK);
  display.display();
}

void move_win(){                                          //Create function move win
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

void pr_win(){                                            //Create function printing win
  display.setTextSize(1);
  display.setTextColor(BLACK, WHITE);
  for(int i = 0; i < SIZE; i++){                          //Create cycle in cycle to fill
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

bool connect_to_wifi(){                                   //Create function connect wifi
  bool c_status = false;
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(conf_wifi_ssid, conf_wifi_password);
  int retries = 0;                                        //Only try $max_connect_attempts times to connect to the WiFi
  while(WiFi.status() != WL_CONNECTED && retries < max_connect_attempts && !conf_button_pressed){
    delay(500);
    Serial.print(".");
    retries++;
  }
  Serial.println("!");
  if(WiFi.status() != WL_CONNECTED && !conf_button_pressed){                  //If we still couldn't connect to the WiFi, go to deep sleep for a minute and try again.
    esp_sleep_enable_timer_wakeup(1 * 10L * 1000000L);
    esp_deep_sleep_start();
    c_status = false;
  } else if(!conf_button_pressed){
    c_status = true;
  }
  return c_status;
}

bool connect_to_aws(){
  bool c_status = false;
  
  net.setCACert(aws_cert_ca);                                                 //Configure WiFiClientSecure to use the AWS certificates we generated
  net.setCertificate(aws_cert_crt);
  net.setPrivateKey(aws_cert_private);
  client.begin(AWS_IOT_ENDPOINT, 8883, net);                                  //Connect to the MQTT broker on the AWS endpoint we defined earlier
  int retries = 0;
  Serial.println("Connecting to AWS IOT");                                    //Try to connect to AWS and count how many times we retried.
  while(!client.connect(DEVICE_NAME) && retries < AWS_MAX_RECONNECT_TRIES && !conf_button_pressed){
    Serial.print("-");
    delay(1000);
    retries++;
  }
  if(!client.connected()){                                                    //Make sure that we did indeed successfully connect to the MQTT broker
    Serial.println(" Timeout!");                                              //If not we just end the function and wait for the next loop.
  } else {
    Serial.println("!!!Connected!!!");                                        //If we land here, we have successfully connected to AWS!And we can subscribe to topics and send messages.
    client.subscribe("/" DEVICE_NAME "/comm");
    client.onMessage(message_handler);     
    c_status = true;
  }
  return c_status;
}

void send_data_to_aws(){
  Serial.println("Reading data from sensors and preparing for sending to AWS.");
  StaticJsonDocument<512> json_doc;                                                       //AWS object formation
  JsonObject state_obj = json_doc.createNestedObject("state");
  JsonObject reported_obj = state_obj.createNestedObject("reported");
//=======================================OBJ====================================//
  JsonObject Accel_obj = reported_obj.createNestedObject("Accel");
  
//=================================JSON=========================================//
  char json_buffer[512];
  serializeJson(json_doc, json_buffer);
  client.publish("$aws/things/" DEVICE_NAME "/shadow/update", json_buffer);
  info_blink(DATA_TRANSFERING_CODE);                                                      //Blink the led to inform that data was succefuly sent
  Serial.println("Sending data to AWS");
}

void message_handler(String &topic, String &payload){
  Serial.println("incoming: " + topic + " - " + payload);
}

void start_transfer(){  
  conf_button_pressed = false;
  if (!connect_to_wifi()){
    a_status = WIFI_ERROR;
    Serial.println("Failed connecting to wi-fi");
  } else {
    Serial.println("Succesfully connected to wi-fi");
    if (!connect_to_aws()) {
      a_status = AWS_ERROR;
    } else {
      a_status = DATA_TRANSFERING;
    } 
  }
}

void info_blink(int code_array[]){
  for (i=0; i<ERROR_CODE_SIZE; i++){
    code = code_array[i];
    digitalWrite(INFO_LED_PIN, HIGH);                                                     // turn the LED on (HIGH is the voltage level)
    delay(code == ERROR_CODE_LONG?1000:500);                                              // wait for a second
    digitalWrite(INFO_LED_PIN, LOW);                                                      // turn the LED off by making the voltage LOW
    delay(500); 
  }
  delay(2000); 
}

void IRAM_ATTR isr() {
  conf_button_pressed = true;
}

#endif
