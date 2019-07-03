#include "ThingSpeak.h"
#include <WiFi.h>

#ifdef __cplusplus
extern "C" {
#endif
uint8_t temprature_sens_read();
#ifdef __cplusplus
}
#endif
uint8_t temprature_sens_read();

#define ANALOG_PIN_0 36
int analog_value = 0;


char ssid[] = "EACI"; // your network SSID (name)
char pass[] = "SMD@EACI"; // your network password
int keyIndex = 0; // your network key Index number (needed only for WEP)
WiFiClient client;
 
unsigned long myChannelNumber = 815527; //update
const char * myWriteAPIKey = "2IS0VFSE7U31WKZ6"; //update

void setup()
{
Serial.begin(115200); //Initialize serial

delay(10);
WiFi.mode(WIFI_STA);
ThingSpeak.begin(client); // Initialize ThingSpeak
 
}

void loop() {

int h = 0;
float t =0;

h = hallRead();
t = ((temprature_sens_read()-32)/1.8);                //changing temperature parameter to celsius

analog_value = analogRead(ANALOG_PIN_0);
Serial.println(analog_value);
 
// Connect or reconnect to WiFi
if(WiFi.status() != WL_CONNECTED){
Serial.print("Attempting to connect to SSID: ");
//Serial.println(SECRET_SSID);
while(WiFi.status() != WL_CONNECTED){
WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
Serial.print(".");
delay(5000);
}
Serial.println("\nConnected.");
}

// Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
// pieces of information in a channel.
ThingSpeak.setField(1, h);
ThingSpeak.setField(2, t);
ThingSpeak.setField(3, analog_value);

// write to the ThingSpeak channel
int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
if(x == 200){
Serial.println("Channel update successful.");
}
else{
Serial.println("Problem updating channel. HTTP error code " + String(x));
}
 
delay(20000); // Wait 20 seconds to update the channel again
}
