/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80);

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid     = "EACI";
const char* password = "SMD@EACI";

const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";
const char* PARAM_INPUT_4 = "input4";
const char* PARAM_INPUT_5 = "input5";
const char* PARAM_INPUT_6 = "input6";
const char* PARAM_INPUT_7 = "input7";


/* LED */
#define LED_PIN1 15
#define LED_PIN2 16
#define LED_PIN3 17
#define LED_PIN4 18
#define LED_PIN5 19

// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
  <meta charset="UTF-8"> <!--portuguese chars-->
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Comando de Robôs por ESP32</title>
  </head>
  
  <body>
  <script>
  <button type="button"
  onclick="document.getElementById('entrar_no_link').innerHTML="location.href="https://duckduckgo.com/""";
  
  </script>  
  <noscript>Sorry, your browser does not support JavaScript!</noscript>
  <h1>Palavra a enviar ao Robô</h1>
  <form action="/get">
    Escreva a palavra: <input type="text" name="input1"> 
    <input type="submit" value="Enviar">
  </form><br>
 
  <div style="background-color:lightblue"><center>
  <h1>Jogo do Galo</h1>
    <table>
      <tr><td>
      <form action="/get">
      <!--input4:<input type="submit" value="Submit">-->
      <!--input4: <input type="text" name="input4">-->
      <input type="submit" name="input4" value="Posição 1" />             
      </form></td>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input5" value="Posição 2" />
      </td>
      </form>
      
      </tr>
      </table>
      <table>
      <tr><td>
      <form action="/get">
      <input type="submit" name="input6" value="Posição 3" />
      </form></td>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input7" value="Posição 4" />
      </td>        
    </tr></table>
    </br>
  </div>
  <p id="demo">Hi.</p>
  <script>
  document.getElementById("demo").innerHTML="Programado por: Fernando Costeira e Paulo Galvão";
  </script> 
  
  
  
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN1, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(LED_PIN3, OUTPUT);   
  pinMode(LED_PIN4, OUTPUT); 
  pinMode(LED_PIN5, OUTPUT); 
  delay(10);

//  connectWiFi();


  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed!");
    return;
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
    }
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_2)) {
      inputMessage = request->getParam(PARAM_INPUT_2)->value();
      inputParam = PARAM_INPUT_2;
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    else if (request->hasParam(PARAM_INPUT_3)) {
      inputMessage = request->getParam(PARAM_INPUT_3)->value();
      inputParam = PARAM_INPUT_3;
    }
    else if (request ->hasParam(PARAM_INPUT_4)) {
          digitalWrite(LED_PIN1, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN2, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN5, LOW);               // GET /H turns the LED on
        }

    else if (request ->hasParam(PARAM_INPUT_5)) {
          digitalWrite(LED_PIN1, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN2, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN5, LOW);               // GET /H turns the LED on
        }

    else if (request ->hasParam(PARAM_INPUT_6)) {
          digitalWrite(LED_PIN1, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN2, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN5, HIGH);               // GET /H turns the LED on
        }
    else if (request ->hasParam(PARAM_INPUT_7)) {
          digitalWrite(LED_PIN1, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN2, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN4, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN5, LOW);               // GET /H turns the LED off
        }
    
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    //Usar linhas seguintes para verificar envio de mensagens
    /*Serial.println(inputMessage);
    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
     */                                
  });
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
