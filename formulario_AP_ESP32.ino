//http://onlineshouter.com/use-esp8266-wifi-modes-station-access-point/
//https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
//https://github.com/me-no-dev/ESPAsyncWebServer#redirect-to-another-url
#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

//Configuration of Network AP 
AsyncWebServer server(80);

IPAddress local_IP(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

const char* ssid     = "ROBOT";
const char* password = "eaci2020"; //tem de ter no minimo 8 char


//Variables for Inputs in WebPage Form
const char* PARAM_INPUT_1 = "input1";
const char* PARAM_INPUT_2 = "input2";
const char* PARAM_INPUT_3 = "input3";
const char* PARAM_INPUT_4 = "input4";
const char* PARAM_INPUT_5 = "input5";
const char* PARAM_INPUT_6 = "input6";
const char* PARAM_INPUT_7 = "input7";
const char* PARAM_INPUT_8 = "input8";
const char* PARAM_INPUT_9 = "input9";
const char* PARAM_INPUT_10 = "input10";


//Variables for the Robot
String palavra;
char letra;

/* Definifion of Outputs */
#define LED_PIN1 15
#define LED_PIN2 16
#define LED_PIN3 17
#define LED_PIN4 18
#define LED_PIN5 19

// HTML web page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
  <head>
  <meta charset="UTF-8"> <!--portuguese chars-->
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Comando de Robôs por ESP32</title>
  </head>
  
  <body>
  
  <h1>Palavra a enviar ao Robô</h1>
  <form action="/get">
    Escreva a palavra (apenas com 10 caracteres): <input type="text" name="input1"> 
    <input type="submit" value="Enviar">
  </form><br>
 
  <div style="background-color:lightblue"><center>
  <h1>Jogo do Galo</h1>
    <table>
      <!--Linha 1-->
      <tr><td>
      <form action="/get">
      <!--input4:<input type="submit" value="Submit">-->
      <!--input4: <input type="text" name="input4">-->
      <input type="submit" name="input2" value="Posição 1" />             
      </form></td>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input3" value="Posição 2" />
      </td>
      </form>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input4" value="Posição 3" />
      </td>
      </form>
      <!--Linha 2-->
      </tr>
      </table>
      <table>
      <tr><td>
      <form action="/get">
      <input type="submit" name="input5" value="Posição 4" />
      </form></td>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input6" value="Posição 5" />
      </td>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input7" value="Posição 6" />
      </td>
      </tr></table>
      <!--Linha 3-->
      </tr>
      </table>
      <table>
      <tr><td>
      <form action="/get">
      <input type="submit" name="input8" value="Posição 7" />
      </form></td>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input9" value="Posição 8" />
      </td>
      <td>
      </&emsp> <!--4 spaces-->
      </td>
      <td>
      <form action="/get">
      <input type="submit" name="input10" value="Posição 9" />
      </td>
      </tr></table>               
    </br>
  </div>
  
  <p id="demo">Hi.</p>
  <script>
  document.getElementById("demo").innerHTML="Programado por: Fernando Costeira e Paulo Galvão";
  </script>
  <p><a href="https://github.com/labF212/ESP32">Obter código</a></p>
    
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

//  connect to WiFi (check in serial monitor)

Serial.print("Setting soft-AP configuration ... ");
Serial.println(WiFi.softAP(ssid,password) ? "Ready" : "Failed!");
Serial.print("Soft-AP IP address = ");

Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed!");
Serial.print("Setting soft-AP ... ");

Serial.println(WiFi.softAPIP());
delay(10);

  // Send web page with input fields to client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });


   // Jogo da Palavra
  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    String inputParam;
    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
    //Recebe a Palavra
    if (request->hasParam(PARAM_INPUT_1)) {
      inputMessage = request->getParam(PARAM_INPUT_1)->value();
      inputParam = PARAM_INPUT_1;
      //Serial.println("Palavra");
      //Serial.println(inputParam);
      
      inputMessage.toLowerCase();
      //Serial.println(inputMessage);
      
      //palavra+ = inputParam;
      for (int i = 0; i < 10; i++) {
      //Serial.println(inputMessage[i]);

      //char letra = palavra[i];
      char letra = inputMessage[i];
      Serial.println(letra);
      
      
      if(letra == 'a'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }

      if(letra == 'b'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, HIGH); 
        delay(400);
        } 

      if(letra == 'c'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'd'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'e'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'f'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);    
        }
      
      if(letra == 'g'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'h'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
    
      if(letra == 'i'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'j'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'k'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'l'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'm'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'n'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'o'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, HIGH);
        delay(400);
        }
      
      if(letra == 'p'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 'q'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 'r'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 's'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 't'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2,HIGH);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 'u'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 'v'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 'x'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, LOW);
        digitalWrite(LED_PIN3, LOW);
        digitalWrite(LED_PIN4, HIGH);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 'y'){
        digitalWrite(LED_PIN1, HIGH);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }
      
      if(letra == 'z'){
        digitalWrite(LED_PIN1, LOW);
        digitalWrite(LED_PIN2, HIGH);
        digitalWrite(LED_PIN3, HIGH);
        digitalWrite(LED_PIN4, LOW);
        digitalWrite(LED_PIN5, LOW);
        delay(400);
        }

    }    
    }

    // JOGO DO GALO
    
    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
    // Recebe o numero da posição 1 da jogada do jogo do galo
    else if (request->hasParam(PARAM_INPUT_2)) {
          digitalWrite(LED_PIN1, LOW);               // GET turns the LED off
          digitalWrite(LED_PIN2, HIGH);               // GET turns the LED off
          digitalWrite(LED_PIN3, HIGH);               // GET turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET turns the LED on
          delay(2000);    
    }
    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
    // Recebe o numero da posição 2 da jogada do jogo do galo
    else if (request->hasParam(PARAM_INPUT_3)) {
          digitalWrite(LED_PIN1, HIGH);               // GET turns the LED off
          digitalWrite(LED_PIN2, LOW);               // GET turns the LED off
          digitalWrite(LED_PIN3, HIGH);               // GET turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET turns the LED on    
          delay(2000);
    }
    // Recebe o numero da posição 3 da jogada do jogo do galo
    else if (request ->hasParam(PARAM_INPUT_4)) {
          digitalWrite(LED_PIN1, LOW);               // GET turns the LED off
          digitalWrite(LED_PIN2, LOW);               // GET turns the LED off
          digitalWrite(LED_PIN3, HIGH);               // GET turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET turns the LED on
          delay(2000);
          
        }
    // Recebe o numero da posição 4 da jogada do jogo do galo
    else if (request ->hasParam(PARAM_INPUT_5)) {
          digitalWrite(LED_PIN1, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN2, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET /H turns the LED on
          delay(2000);
        }
    // Recebe o numero da posição 5 da jogada do jogo do galo
    else if (request ->hasParam(PARAM_INPUT_6)) {
          digitalWrite(LED_PIN1, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN2, HIGH);               // GET /H turns the LED on
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED on
          digitalWrite(LED_PIN4, HIGH);               // GET /H turns the LED on
          delay(2000);
        }
    // Recebe o numero da posição 6 da jogada do jogo do galo
    else if (request ->hasParam(PARAM_INPUT_7)) {
          digitalWrite(LED_PIN1, HIGH);               // GET /H turns the LED off
          digitalWrite(LED_PIN2, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN4, HIGH);               // GET /H turns the LED off
          delay(2000);
        }
    // Recebe o numero da posição 7 da jogada do jogo do galo
    else if (request ->hasParam(PARAM_INPUT_8)) {
          digitalWrite(LED_PIN1, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN2, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN3, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN4, HIGH);               // GET /H turns the LED off
          delay(2000);
        }
    // Recebe o numero da posição 8 da jogada do jogo do galo
    else if (request ->hasParam(PARAM_INPUT_9)) {
          digitalWrite(LED_PIN1, HIGH);               // GET /H turns the LED off
          digitalWrite(LED_PIN2, HIGH);               // GET /H turns the LED off
          digitalWrite(LED_PIN3, HIGH);               // GET /H turns the LED off
          digitalWrite(LED_PIN4, LOW);               // GET /H turns the LED off
          delay(2000);
        }

    // Recebe o numero da posição 9 da jogada do jogo do galo
    else if (request ->hasParam(PARAM_INPUT_10)) {
          digitalWrite(LED_PIN1, LOW);               // GET /H turns the LED off
          digitalWrite(LED_PIN2, HIGH);               // GET /H turns the LED off
          digitalWrite(LED_PIN3, HIGH);               // GET /H turns the LED off
          digitalWrite(LED_PIN4, LOW);               // GET /H turns the LED off
          delay(2000);
        }
    
    else {
      inputMessage = "No message sent";
      inputParam = "none";
    }
    //Verificar o envio da mensagem na porta série
    Serial.println(inputMessage);
    
    //Página que abre quando se carrega num botão
    //to local url
    request->redirect("/");
   /* request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
                                     + inputParam + ") with value: " + inputMessage +
                                     "<br><a href=\"/\">Return to Home Page</a>");
     */                                                                                                                                                                                                                                            
  });                                            
  server.onNotFound(notFound);
  server.begin();
}

void loop() {
  
}
