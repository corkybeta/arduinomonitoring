//initialising pin outputs 
int RED = 3;
int GREEN = 5;
int BLUE = 6;

//variables
int repeats = 0;
int brightness = 0;
String readString;
String standardMessage = "VPW Systems";
int standardRed = 250;
int standardGreen = 166;
int standardBlue = 26;

//MAC address is set. values for ip, dns, gateway and subnet are added below
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192,168,1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);
//port for webserver
EthernetServer server(80);

//i2c LCD
#define I2C_ADDR 0x27 //address needs to be set, differs between i2c controllers
#define BACKLIGHT_PIN  3 //pin for LCD backlight
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
