#ifndef var_h
#define var_h

/*----------VARIABLES----------*/
bool O_win = false;                                       //Variable win '0'
bool X_win = false;                                       //Variable win 'X'
int Array[SIZE][SIZE] = {{0,0,0}, {0,1,0}, {0,0,1}};      //Create test array
int i;
int code;

int WIFI_ERROR_CODE[ERROR_CODE_SIZE] = {ERROR_CODE_LONG, ERROR_CODE_LONG, ERROR_CODE_LONG, ERROR_CODE_LONG};
int AWS_ERROR_CODE[ERROR_CODE_SIZE] = {ERROR_CODE_LONG, ERROR_CODE_LONG, ERROR_CODE_SHORT, ERROR_CODE_LONG};
int DATA_TRANSFERING_CODE[ERROR_CODE_SIZE] = {ERROR_CODE_SHORT, ERROR_CODE_SHORT, ERROR_CODE_SHORT, ERROR_CODE_LONG};

//wifi configuration
const int max_connect_attempts = 10;                             //variable repeat connect
const int conf_par_size = 25;
char conf_wifi_ssid[conf_par_size] = "EE";                         //Login and password Wifi network
char conf_wifi_password[conf_par_size] = "EE@05kilogram";

//Interval begin app status
typedef enum {
  WIFI_ERROR,                                    //if this error appear then blinking led scheme is ----
  AWS_ERROR,                                     //if this error appear then blinking led scheme is -.--
  DATA_TRANSFERING,                              //start data transfer  blinking code is --.-
} app_status;
app_status a_status;

bool conf_button_pressed = false;

#endif
