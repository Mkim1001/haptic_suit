/*********
  Rui Santos
  Complete project details at https://randomnerdtutorials.com  
*********/

// Load Wi-Fi library
#include <WiFi.h>

// Replace with your network credentials
const char* ssid     = "hyungwoo";
const char* password = "123456789a";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String output21State = "off";
String output12State = "off";

// Assign output variables to GPIO pins
const int output4 = 4;
const int output12 = 12;
const int output13 = 13;
const int output14 = 14;
const int output15 = 15;
const int output21 = 21;
const int output25 = 25;
const int output26 = 26;
const int output32 = 32;
const int output33 = 33;
const int output34 = 34;
const int output36 = 36;
const int output39 = 39;


void setup() {
  Serial.begin(115200);
  // Initialize the output variables as outputs
 pinMode(output4, OUTPUT);
 pinMode(output12, OUTPUT);
 pinMode(output13, OUTPUT);
 pinMode(output14, OUTPUT);
 pinMode(output15, OUTPUT);
 pinMode(output21, OUTPUT);
 pinMode(output25, OUTPUT);
 pinMode(output26, OUTPUT);
 pinMode(output32, OUTPUT);
 pinMode(output33, OUTPUT);
 pinMode(output34, OUTPUT);
 pinMode(output36, OUTPUT);
 pinMode(output39, OUTPUT);
  // Set outputs to LOW
  digitalWrite(output21, LOW);
  digitalWrite(output12, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /21/on") >= 0) {
              Serial.println("GPIO 21 on");
              output21State = "on";
              digitalWrite(output21, HIGH);
            } else if (header.indexOf("GET /21/off") >= 0) {
              Serial.println("GPIO 21 off");
              output21State = "off";
              digitalWrite(output21, LOW);
            } else if (header.indexOf("GET /12/on") >= 0) {
              Serial.println("GPIO 12 on");
              output12State = "on";
              digitalWrite(output12, HIGH);
            } else if (header.indexOf("GET /12/off") >= 0) {
              Serial.println("GPIO 12 off");
              output12State = "off";
              digitalWrite(output12, LOW);
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>.container { position; relative; width; 100% max-width;400px;}");
           // client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            //client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".container img { width: 70%; height: 20;}");
          
            client.println(".container .btn:hover {background-color: black;}");
           // client.println("text-decoration: none; font-size: 3px; margin: 2px; cursor: pointer;}");
            client.println(".button1 {position: absolute;top: 30%;left: 50%; transform: translate(-50%, -50%);-ms-transform: translate(-50%, -50%);background-color: #eb133e;color: white;font-size: 5px;padding: 10px 10px;border: none;cursor: pointer;border-radius: 20px;text-align: center;");
            client.println(".button2 {position: absolute;top: 30%;left: 50%; transform: translate(-50%, -50%);-ms-transform: translate(-50%, -50%);background-color: #eb133e;color: white;font-size: 5px;padding: 10px 10px;border: none;cursor: pointer;border-radius: 20px;text-align: center;");
             client.println(".container .btn1:hover {background-color: black;}");
             client.println(".container .btn2:hover {background-color: black;}");
            // Web Page Heading
            
            client.println("</style>");
            client.println("</head>");
            client.println("<body><h1>Haptic body suit</h1>");
            client.println("<p>Click the buttons to telecomunicat touch senses to the suit:</p>");
         
           client.println("<div class=container>");
          client.println("<img src=\"https://mkim1001.github.io/haptic_suit/Bodysuite.png\">");
          client.println("<img src=img_Bodysuit.jpg>// alt=now style=width:100%>");
           client.println("<button class=btn>Button</button>");
           client.println("<button2 class=btn2>Button</button2>");
          
            // Display current state, and ON/OFF buttons for GPIO 21  
           // client.println("<p>GPIO 21 - State " + output21State + "</p>");
            // If the output21State is off, it displays the ON button       
            if (output21State=="off") {
           client.println("<p><a href=\"/21/on\"><button1 class=\"button1\">21ON</button1></a></p>");
            } else {
              client.println("<p><a href=\"/21/off\"><button1 class=\"button1 button1\">21OFF</button1></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 12  
           // client.println("<p>GPIO 12 - State " + output12State + "</p>");
            // If the output12State is off, it displays the ON button       
            if (output12State=="off") {
              client.println("<p><a href=\"/12/on\"><button2 class=\"button2\">12ON</button2></a></p>");
            } else {
              client.println("<p><a href=\"/12/off\"><button2 class=\"button2 button2\">12OFF</button2></a></p>");
            }
           client.println("</div>");
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
