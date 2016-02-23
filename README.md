# Arduino RGB Monitoring
This script utilises an Arduino with an ethernet and RGB shield. The Arduino can be connected to a router and reached from a local IP or it will function on a direct ethernet connection if the machine connected is configured correctly. **No DHCP functionality is added** to the script and it relies on a static IP.

    int BLUE = 6;                   
    int GREEN = 5;
    int RED = 3;

The pin inputs for the RGB shield are numbered on the board. They need to be initialised before use.

    IPAddress ip(192, 168, 1, 177);
    IPAddress myDns(192,168,1, 1);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 255, 0);
    EthernetServer server(80);

The network configuration for the Arduino happens here. Most of these values can be commented out and should auto configure.  
A simple HTML page exists on the webserver with the existing sequences. This is extremely useful for adding new functions and troubleshooting so if new sequences are added, an entry like the one below should also be added:

    client.println("<a href=\"/?redon\"\">Turn On RED LED</a>");
    client.println("<br />");

### Adding a new sequence
Adding a new sequence is done by writing an if statement directly into the script. Here is an example of a flashing sequence:

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

This sequence, triggered when the url **http://$ArduinoIP/?sequence1** is requested, flashes red on and off every half second for 10 repeats, making the sequence 10 seconds long. The for statement starts with a value for repeats of 10 and counts down to 1. After the 10 repeats, it returns to the standard RGB output.  
This is an example of a fading sequence:

    if (readString.indexOf("?sequence4") >0){
      for (repeats = 15; repeats > 0; repeats --) {
        for (brightness = 0; brightness < 255; brightness ++) {
          analogWrite(RED, brightness);
          analogWrite(GREEN, brightness);
          analogWrite(BLUE, 0);
          delay(5);
        }
        for (brightness = 255; brightness > 0; brightness --) {
          analogWrite(RED, brightness);
          analogWrite(GREEN, brightness);
          analogWrite(BLUE, 0);
          delay(5);
        }
      }
      analogWrite(RED, 250);
      analogWrite(GREEN, 26);
      analogWrite(BLUE, 166);
    }

This fading sequence uses two separate for loops inside a for loop. The first for loop has 255 repeats, each repeat **incrementing the brightness by 1.** This changes the value of RED and GREEN but **BLUE stays off.** The second for loop starts with a brightness of 255 and increments brightness by negative 1, causing the LEDs to fade. These two for loops are repeated 15 times, and then the LEDs are set back to the standard value.  

When adding a new sequence, consider adding a return to the standard value outside of the loop. Sequences are most useful when limited to a certain time period otherwise the alert loses its effectiveness. The standard output (at time of writing):

    analogWrite(RED, 250);
    analogWrite(BLUE, 166);
    analogWrite(GREEN, 26);

When writing sequences, note that delay is in milliseconds. Large values such as 500 are for flashing sequences and a smaller value such as 5 is used for fading sequences.  

### Debugging
The HTML page hosted on the webserver is useful for testing new sequences. When that isn't working, the Arduino IDE has a Serial Monitor that shows HTTP requests and the IP of the board. All HTTP requests can be sent to the Serial Monitor with this commented ou line in the loop:

    //Serial.print(c);
