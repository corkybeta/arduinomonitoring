/*
 RGB Monitoring Indicator

 A simple server that takes displays a default LED output until a hyperlink receives a request, when the LEDs change colour.

 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13

 created 22 Feb 2016
 by Corey Wood
 modified 22 Feb 2016
 by Corey Wood

 */
 
// Initialising Pin outputs 
int BLUE = 6;                   
int GREEN = 5; 
int RED = 3;
int repeats = 0;
String readString;

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network.
// gateway and subnet are optional:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 177);
IPAddress myDns(192,168,1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

// Initialise the Ethernet server library
// with the IP address and port you want to use
EthernetServer server(80);

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  // Create a client connection
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
        //read char by char HTTP request
        if (readString.length() < 100) {
          //store characters to string
          readString += c;
          //Serial.print(c);
         }
         //if HTTP request has ended
         if (c == '\n') {          
           Serial.println(readString); //print to serial monitor for debugging
           client.println("HTTP/1.1 200 OK"); //send new page
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<html>");
           client.println("<head>");
           client.println("<title>RGB LEDs</title>");
           client.println("</head>");
           client.println("<body>");
           client.println("<br />");  
           client.println("<a href=\"/?sequence1\"\">Sequence 1</a>"); //url addition
           client.println("<br />");
           client.println("<a href=\"/?sequence2\"\">Sequence 2</a>");
           client.println("<br />");
           client.println("<a href=\"/?redon\"\">Turn On RED LED</a>");
           client.println("<br />"); 
           client.println("<a href=\"/?greenon\"\">Turn On GREEN LED</a>");
           client.println("<br />"); 
           client.println("<a href=\"/?blueon\"\">Turn On BLUE LED</a>");
           client.println("<br />"); 
           client.println("</body>");
           client.println("</html>");
           delay(1);
           //stopping client
           client.stop();
           //these commands read the appended url addition and activate the LEDs accordingly
           if (readString.indexOf("?sequence1") >0){
               for (repeats = 10; repeats > 0; repeats --) {
                analogWrite(GREEN, 0);
                analogWrite(RED, 255);
                analogWrite(BLUE, 0);
                delay(500);
                analogWrite(GREEN, 0);
                analogWrite(RED, 0);
                analogWrite(BLUE, 0);
                delay(500);
               }
               analogWrite(RED, 250);
               analogWrite(BLUE, 166);
               analogWrite(GREEN, 26);
           }
           if (readString.indexOf("?sequence2") >0){
               for (repeats = 5; repeats > 0; repeats --) {
                analogWrite(GREEN, 0);
                analogWrite(RED, 0);
                analogWrite(BLUE, 255);
                delay(500);
                analogWrite(GREEN, 0);
                analogWrite(RED, 0);
                analogWrite(BLUE, 0);
                delay(500);
               }
               analogWrite(RED, 250);
               analogWrite(BLUE, 166);
               analogWrite(GREEN, 26);
           }
           if (readString.indexOf("?redon") >0){
               analogWrite(RED, 255);
               analogWrite(GREEN, 0);
               analogWrite(BLUE, 0);
           }         
           if (readString.indexOf("?greenon") >0){
               analogWrite(RED, 0);
               analogWrite(GREEN, 255);
               analogWrite(BLUE, 0);
           }
           if (readString.indexOf("?blueon") >0){
               analogWrite(RED, 0);
               analogWrite(GREEN, 0);
               analogWrite(BLUE, 255);
           }
           //clearing string for next read
           readString="";
         }
      }
    }
  }
}
