/********************************************************************************
 * Sending data to a local Page
 *  => LDR
 *  => Generic data from a analog input (potenciometer, LDR, etc)
 * 
 * Receiving commands from a local page
 *  ==> Turning ON/OFF a LED
 * 
 * Based on original SimpleWiFiServer created for on Arduino 25 Nov 2012 by Tom Igoe
 * and ported for sparkfun esp32 on 31.01.2017 by Jan Hendrik Berlin
 * 
 * MJRoBot.org 9Sept17 
 * 
 * Send comands to multiple outputs - node32s
 *  
 * Paulo Galvão Jul19
 ********************************************************************************/


/* WiFi parameters and credentials */
#include <WiFi.h>
/*const char* ssid     = "YOUR SSID";
const char* password = "YOUR PASSWORD";
*/

const char* ssid     = "EACI";
const char* password = "EACI@EACI";

WiFiServer server(80);


/* DHT Temperature and Humidity Sensor */
/*#include "DHT.h"
#define DHTPIN 23  
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
float localHum = 0;
float localTemp = 0;
/*

/* LED */
#define LED_PIN1 15
#define LED_PIN2 16
#define LED_PIN3 17
#define LED_PIN4 18
#define LED_PIN5 19

//Analog Input
#define ANALOG_PIN_0 T0 //D4
int analog_value = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);   
  pinMode(LED_PIN4, OUTPUT); 
  pinMode(LED_PIN5, OUTPUT); 
  delay(10);

  connectWiFi();
 
//  dht.begin();
}

int value = 0;

void loop()
{
  analog_value = analogRead(ANALOG_PIN_0);
  //getDHT();
  WiFiLocalWebPageCtrl();
}




/***************************************************
* Send and receive data from Local Page
****************************************************/
void WiFiLocalWebPageCtrl(void)
{
  WiFiClient client = server.available();   // listen for incoming clients
  //client = server.available();
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            //WiFiLocalWebPageCtrl(); 
  /*            client.print("Temperature now is: ");
              client.print(localTemp);
              client.print("  oC<br>");
              client.print("Humidity now is:     ");
              client.print(localHum);
              client.print(" % <br>");
              client.print("<br>");*/
                            
              client.print("<meta charset=""UTF-8"">"); //portuguese chars
              client.print("<div><h1>Receiving Data from ESP32 webserver on 172.22.2.X</h1><hr><br></div>");
              
              client.print("Analog Data (LDR):     ");
              client.print(analog_value);
              client.print("<br>");
              client.print("<br>");
              
              client.print("<div style=><center>Clique <a href=\"/SEQ1\">aqui</a> sequência 1.<br>");
              client.print("Clique <a href=\"/SEQ2\">aqui</a> sequência 2.<br>");
              client.print("Clique <a href=\"/SEQ3\">aqui</a> sequência 3.<br></div>");
              client.print("<a href=""/SEQ3""><button>Desligar tudo</button><center></a>");         

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /SEQ1")) {
          digitalWrite(LED_PIN1, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN2, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN5, LOW);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /SEQ2")) {
          digitalWrite(LED_PIN1, LOW);                // GET /L turns the LED off
          digitalWrite(LED_PIN2, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN5, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /SEQ3")) {
          digitalWrite(LED_PIN1, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN2, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN5, LOW);               // GET /H turns the LED on
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}









/***************************************************
* Connecting to a WiFi network
****************************************************/
void connectWiFi(void)
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.begin();
}
