#include "defines.h"
//https://github.com/khoih-prog/WebSockets2_Generic/blob/master/examples/ESP8266/Minimal-Esp8266-Client/defines.h
#include <WebSockets2_Generic.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>   

using namespace websockets2_generic;
int LED_D1 = 5; // d1 pertenece al 5
int D1_STATUS = 0;
void TURN_ON(){
  digitalWrite(LED_D1, HIGH);
  D1_STATUS = 1;
}
void TURN_OFF(){
  digitalWrite(LED_D1, LOW);
  D1_STATUS = 0;
}
void onMessageCallback(WebsocketsMessage message) 

{
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, message.data()); 
  Serial.print("Got Message: ");
  Serial.println(message.data());
  if (message.data()=="{\"message\":\"PRENDE\"}"){
    Serial.println("IGUALES");
    TURN_ON();
    }
   if (message.data()=="{\"message\":\"APAGA\"}"){
    Serial.println("IGUALEapagaS");
    TURN_OFF();
    }
  const char* message_ = doc["message"];
  const char* prender = "PRENDE";
  //Serial.println(message_);
  if (message_ == prender){
    Serial.print("HOaaaLA");
    TURN_ON();
    }
    if (message_== "APAGA"){
    TURN_OFF();
    }
}

void onEventsCallback(WebsocketsEvent event, String data) 
{
  (void) data;
  
  if (event == WebsocketsEvent::ConnectionOpened) 
  {
    Serial.println("Connnection Opened");
  } 
  else if (event == WebsocketsEvent::ConnectionClosed) 
  {
    Serial.println("Connnection Closed");
  } 
  else if (event == WebsocketsEvent::GotPing) 
  {
    Serial.println("Got a Ping!");
  } 
  else if (event == WebsocketsEvent::GotPong) 
  {
    Serial.println("Got a Pong!");
  }
}

WebsocketsClient client;

void setup() 
{
  pinMode(LED_D1, OUTPUT);
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart Minimal-ESP8266-Client on "); Serial.println(ARDUINO_BOARD);
  Serial.println(WEBSOCKETS2_GENERIC_VERSION);
  
  // Connect to wifi
  WiFi.begin("SALDIAS_2.4G", "2045._2927");

  // Wait some time to connect to wifi
  for (int i = 0; i < 10 && WiFi.status() != WL_CONNECTED; i++) 
  {
    Serial.print(".");
    delay(1000);
  }

  // Check if connected to wifi
  if (WiFi.status() != WL_CONNECTED) 
  {
    Serial.println("No Wifi!");
    return;
  }

  Serial.print("Connected to Wifi, Connecting to WebSockets Server @");
  Serial.println(websockets_server_host);
  
  // run callback when messages are received
  client.onMessage(onMessageCallback);

  // run callback when events are occuring
  client.onEvent(onEventsCallback);

  // Connect to server
  client.connect("192.168.1.5", 4000, "/websockets");

  // Send a message
  String WS_msg = "{\"message\":\"hola\"}";//String("Hello to Server from ") + BOARD_NAME;
  client.send(WS_msg);

  // Send a ping
  client.ping();
}

void loop() 
{
  //TURN_ON();
  //delay(1000);
  //TURN_OFF();
  //delay(1000);
  client.poll();
  //client.ping();
}
