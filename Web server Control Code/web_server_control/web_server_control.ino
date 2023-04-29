#include <WiFi.h>

const char* ssid = "Orange";   //Enter SSID WIFI Name
const char* password = "Aqazwsxedc1";   //Enter WIFI Password
WiFiServer server(80);

String header;
String movment_forward_state = "off";
String movment_backward_state = "off";
String movment_right_state = "off";
String movment_left_state = "off";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Motor A
 
int enA = 5;
int in1 = 17;
int in2 = 16;
 
// Motor B
 
int enB = 2;
int in3 = 4;
int in4 = 0;


void setup() {
  Serial.begin(9600); // Starts the serial communication
  Serial.setDebugOutput(true);
  Serial.println();
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
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


void movment_stop(){
  analogWrite(enA, 0);
  analogWrite(enB, 0);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  }


void movment_forward(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Robot is moving forward");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }

void movment_backward(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Robot is moving backward");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }


void movment_left(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  Serial.println("Robot is moving left");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }


void movment_right(){
  analogWrite(enA, 200);
  analogWrite(enB, 200);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  Serial.println("Robot is moving right");  // printlns a label
  Serial.println("\t");         // printlns a tab
  }

void loop() {
  // server.handleClient();

  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
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
            if (header.indexOf("GET /movment_forward/on") >= 0) {
              Serial.println("movment_forward on");
              movment_forward_state = "on";
              movment_forward ();
            } else if (header.indexOf("GET /movment_forward/off") >= 0) {
              Serial.println("movment_forward off");
              movment_forward_state = "off";
              movment_stop();
            } 


            if (header.indexOf("GET /movment_backward/on") >= 0) {
              Serial.println("movment_backward on");
              movment_backward_state = "on";
              movment_backward ();
            } else if (header.indexOf("GET /movment_forward/off") >= 0) {
              Serial.println("movment_forward off");
              movment_backward_state = "off";
              movment_stop();
            } 


            if (header.indexOf("GET /movment_right/on") >= 0) {
              Serial.println("movment_right on");
              movment_right_state = "on";
              movment_right ();
            } else if (header.indexOf("GET /movment_right/off") >= 0) {
              Serial.println("movment_right off");
              movment_right_state = "off";
              movment_stop();
            } 
            if (header.indexOf("GET /movment_left/on") >= 0) {
              Serial.println("movment_left on");
              movment_left_state = "on";
              movment_left ();
            } else if (header.indexOf("GET /movment_left/off") >= 0) {
              Serial.println("movment_left off");
              movment_left_state = "off";
              movment_stop();
            } 
            // else if (header.indexOf("GET /27/on") >= 0) {
            //   Serial.println("GPIO 27 on");
            //   output27State = "on";
            //   digitalWrite(output27, HIGH);
            // } else if (header.indexOf("GET /27/off") >= 0) {
            //   Serial.println("GPIO 27 off");
            //   output27State = "off";
            //   digitalWrite(output27, LOW);
            // }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            // client.println("<p>Forward State " + movment_forward_state + "</p>");
            // If the movment_forward_state is off, it displays the ON button       
            if (movment_forward_state=="off") {
              client.println("<p><a href=\"/movment_forward/on\"><button class=\"button\">Forward ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/movment_forward/off\"><button class=\"button button2\">Forward OFF</button></a></p>");
            } 

            if (movment_backward_state=="off") {
              client.println("<p><a href=\"/movment_backward/on\"><button class=\"button\">Backward ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/movment_backward/off\"><button class=\"button button2\">Backward OFF</button></a></p>");
            } 

            if (movment_right_state=="off") {
              client.println("<p><a href=\"/movment_right/on\"><button class=\"button\">Right ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/movment_right/off\"><button class=\"button button2\">Right OFF</button></a></p>");
            } 
            if (movment_left_state=="off") {
              client.println("<p><a href=\"/movment_left/on\"><button class=\"button\">Left ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/movment_left/off\"><button class=\"button button2\">Left OFF</button></a></p>");
            } 
                        
            // Display current state, and ON/OFF buttons for GPIO 27  
            // client.println("<p>GPIO 27 - State " + output27State + "</p>");
            // If the output27State is off, it displays the ON button       
            // if (output27State=="off") {
            //   client.println("<p><a href=\"/27/on\"><button class=\"button\">ON</button></a></p>");
            // } else {
            //   client.println("<p><a href=\"/27/off\"><button class=\"button button2\">OFF</button></a></p>");
            // }
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

