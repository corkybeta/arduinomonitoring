# Arduino RGB Monitoring
This script utilises an Arduino with an ethernet and RGB shield. The Arduino can be connected to a router and reached from a local IP or it will function on a direct ethernet connection if the machine connected is configured correctly. No DHCP functionality is added to the script and it relies on a static IP.

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

When adding a new sequence, consider adding a return to the standard value outside of the loop. Sequences are most useful when limited to a certain time period otherwise the alert loses its effectiveness. The standard output (at time of writing):

    analogWrite(RED, 250);
    analogWrite(BLUE, 166);
    analogWrite(GREEN, 26);

When writing sequences, note that delay is in milliseconds. Large values such as 500 are for flashing sequences and a smaller value such as 5 is used for fading sequences.  

### Debugging
The HTML page hosted on the webserver is useful for testing new sequences. When that isn't working, the Arduino IDE has a Serial Monitor that shows HTTP requests and the IP of the board. All HTTP requests can be sent to the Serial Monitor with this line in the loop:

    //Serial.print(c);
