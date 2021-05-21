#ifndef def_h
#define def_h

/*----------DEFINES----------*/
#define D8 18                                                           //Serial clock out (SCLK)
#define D7 23                                                           //Serial data out (DIN)
#define D6 19                                                           //Data/Command select (D/C)
#define D5 5                                                            //LCD chip select (CS)
#define D2 14                                                           //LCD reset (RST)
#define SIZE 3                                                          //size arr
#define DEVICE_NAME "TIC01"                                             //The name of the device. This MUST match up with the name defined in the AWS console
#define AWS_IOT_ENDPOINT "***"              //The MQTTT endpoint for the device (unique for each AWS account but shared amongst devices within the account)
#define AWS_IOT_TOPIC "/"+ DEVICE_NAME+ "/comand"                       //The MQTT topic that this device should publish to
#define BUTTON_PIN 4                                                    //button pin
#define INFO_LED_PIN 2                                                  //(RED)led pin
#define AWS_MAX_RECONNECT_TRIES 50  
#define ERROR_CODE_SIZE 4                                               //led blinker and parameter is array of ERROR_CODE_SIZE items 
#define ERROR_CODE_LONG 0                                               //where ERROR_CODE_LONG long light and ERROR_CODE_SHORT is short light
#define ERROR_CODE_SHORT 1                                              //error

#endif
