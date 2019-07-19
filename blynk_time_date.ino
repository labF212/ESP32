   /* WiFi parameters and credentials */
#include <WiFi.h>
#define BLYNK_PRINT Serial
#include <BlynkSimpleEsp32.h> // Blynk-ESP32
#include <WiFiClient.h> // Wi-Fi client 
/*const char* ssid     = "YOUR SSID";
const char* password = "YOUR PASSWORD";
*/

#include <NTPClient.h>
#include <WiFiUdp.h>
// https://github.com/taranais/NTPClient instalar esta biblioteca
// fazendo desta forma https://www.robocore.net/tutoriais/adicionando-bibliotecas-na-ide-arduino.html 

const char* ssid     = "NOME_REDE"; //ver estas passwords no documento de texto
const char* password = "PASSWORD";

//-------- Token de Autenticação -----------
char auth[] = "Token_Blynk"; // Coloque aqui o código de Token

WiFiServer server(80);

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

/* DHT Temperature and Humidity Sensor */
/*#include "DHT.h"
#define DHTPIN 23  
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
float localHum = 0;
float localTemp = 0;
/*

/* LED */
#define LED_PIN 2

//Analog Input
#define ANALOG_PIN_0 36
int analog_value = 0;

// Variables to save date and time
  String formattedDate;
  String dayStamp;
  String timeStamp;


BlynkTimer timer;
void sendSensor()
{
  
  analog_value = analogRead(ANALOG_PIN_0);     // Armazena os valores de leitura do sensor de luz
 
  
  Blynk.virtualWrite(V1, LED_PIN);
  Blynk.virtualWrite(V2, analog_value);      // Valor de LDR porta virtual V2
  Blynk.virtualWrite(V3, timeStamp);
  Blynk.virtualWrite(V4, dayStamp);
  

}



void setup()
{
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT); 
  delay(10);

  connectWiFi();

  Blynk.begin(auth, ssid, password); // TOKEN+REDE+SENHA
  timer.setInterval(1000L, sendSensor);
 
//  dht.begin();

// Initialize a NTPClient to get time
  timeClient.begin();
  // Set offset time in seconds to adjust for your timezone, for example:
  // GMT +1 = 3600
  // GMT +8 = 28800
  // GMT -1 = -3600
  // GMT 0 = 0
  timeClient.setTimeOffset(3600);


}

int value = 0;

void data_hora() {
  while(!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);

  // Extract date
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  Serial.print("DATE: ");
  Serial.println(dayStamp);
  // Extract time
  timeStamp = formattedDate.substring(splitT+1, formattedDate.length()-1);
  Serial.print("HOUR: ");
  Serial.println(timeStamp);
  delay(1000);
}




void loop()
{
  analog_value = analogRead(ANALOG_PIN_0);
  //getDHT();
  WiFiLocalWebPageCtrl();

  timer.run();
  Blynk.run();
  data_hora();
  
}

/***************************************************
* Get indoor Temp/Hum data
****************************************************/
/*void getDHT()
{
  float tempIni = localTemp;
  float humIni = localHum;
  localTemp = dht.readTemperature();
  localHum = dht.readHumidity();
  if (isnan(localHum) || isnan(localTemp))   // Check if any reads failed and exit early (to try again).
  {
    localTemp = tempIni;
    localHum = humIni;
    return;
  }
}

*/
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
              
              client.print("<h1>Receiving Data from ESP32 webserver on 172.22.2.X</h1><hr><br>");
              
              client.print("Analog Data (LDR):     ");
              client.print(analog_value);
              client.print("<br>");
              client.print("<br>");
              
              client.print("Click <a href=\"/H\">here</a> to turn the LED on.<br>");
              client.print("Click <a href=\"/L\">here</a> to turn the LED off.<br>");
              client.print("<br>");
              client.print("Hora:     ");
              client.print(timeStamp);
              client.print("<br>");
              client.print("Dia:     ");
              client.print(dayStamp);
              client.print("<br>");

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
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_PIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_PIN, LOW);                // GET /L turns the LED off
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
