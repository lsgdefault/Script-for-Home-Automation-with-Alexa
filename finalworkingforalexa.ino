/*
 Version 0.4 - April 26 2019
*/ 

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsClient.h> //  https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries
#include <ArduinoJson.h> // https://github.com/kakopappa/sinric/wiki/How-to-add-dependency-libraries (use the correct version)
#include <StreamString.h>

int device_1 = 5;
int device_2 = 4;
int device_3 = 0;
int device_4 = 2;
int device_5 = 14;
int device_6 = 12;
int device_7 = 13;
int device_8 = 15;

ESP8266WiFiMulti WiFiMulti;
WebSocketsClient webSocket;
WiFiClient client;

#define MyApiKey "44ab537d-8a07-4ae4-a08d-7fbaf861c51f" // TODO: Change to your sinric API Key. Your API Key is displayed on sinric.com dashboard
#define MySSID "TP-LINK" // TODO: Change to your Wifi network SSID
#define MyWifiPassword "123123123" // TODO: Change to your Wifi network password

#define HEARTBEAT_INTERVAL 300000 // 5 Minutes 

uint64_t heartbeatTimestamp = 0;
bool isConnected = false;


// deviceId is the ID assgined to your smart-home-device in sinric.com dashboard. Copy it from dashboard and paste it here

void turnOn(String deviceId) {
  if (deviceId == "5d9358b0de917d27fed3d2a1") // Device ID of first device
  {  
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_1, LOW);
  } 
  else if (deviceId == "5d9358e4de917d27fed3d2ae") // Device ID of second device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_2, LOW);
  }
  else if (deviceId == "5d9358ebde917d27fed3d2b4") // Device ID of Third device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_3, LOW);
  }
  else if (deviceId == "5d9358f6de917d27fed3d2b9") // Device ID of Fourth device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_4, LOW);
  }
  else if (deviceId == "5d935900de917d27fed3d2be") // Device ID of Fifth device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_5, LOW);
  }
  else if (deviceId == "5d935907de917d27fed3d2c0") // Device ID of Sixth device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_6, LOW);
  }
  else if (deviceId == "5d93590fde917d27fed3d2c5") // Device ID of Seventh device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_7, LOW);
  }
  else if (deviceId == "5d935916de917d27fed3d2ca") // Device ID of Eighth device
  { 
    Serial.print("Turn on device id: ");
    Serial.println(deviceId);
    digitalWrite(device_8, LOW);
  }
  else {
    Serial.print("Turn on for unknown device id: ");
    Serial.println(deviceId);    
  }     
}

void turnOff(String deviceId) {
   if (deviceId == "5d9358b0de917d27fed3d2a1") // Device ID of first device
  {  
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_1, HIGH);
  } 
  else if (deviceId == "5d9358e4de917d27fed3d2ae") // Device ID of second device
  { 
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_2, HIGH);
  }
  else if (deviceId == "5d9358ebde917d27fed3d2b4") // Device ID of Third device
  { 
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_3, HIGH);
  }
  else if (deviceId == "5d9358f6de917d27fed3d2b9") // Device ID of Fourth device
  { 
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_4, HIGH);
  }
  else if (deviceId == "5d935900de917d27fed3d2be") // Device ID of Fifth device
  { 
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_5, HIGH);
  }
  else if (deviceId == "5d935907de917d27fed3d2c0") // Device ID of Sixth device
  { 
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_6, HIGH);
  }
  else if (deviceId == "5d93590fde917d27fed3d2c5") // Device ID of Seventh device
  { 
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_7, HIGH);
  }
  else if (deviceId == "5d935916de917d27fed3d2ca") // Device ID of Eighth device
  { 
    Serial.print("Turn off device id: ");
    Serial.println(deviceId);
    digitalWrite(device_8, HIGH);
  }
  else {
    Serial.print("Turn off for unknown device id: ");
    Serial.println(deviceId);    
  }     
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch(type) {
    case WStype_DISCONNECTED:
      isConnected = false;    
      Serial.printf("[WSc] Webservice disconnected from sinric.com!\n");
      break;
    case WStype_CONNECTED: {
      isConnected = true;
      Serial.printf("[WSc] Service connected to sinric.com at url: %s\n", payload);
      Serial.printf("Waiting for commands from sinric.com ...\n");        
      }
      break;
    case WStype_TEXT: {
        Serial.printf("[WSc] get text: %s\n", payload);
        // Example payloads

        // For Switch or Light device types
        // {"deviceId": xxxx, "action": "setPowerState", value: "ON"} // https://developer.amazon.com/docs/device-apis/alexa-powercontroller.html

        // For Light device type
        // Look at the light example in github
          
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject((char*)payload); 
        String deviceId = json ["deviceId"];     
        String action = json ["action"];
        
        if(action == "setPowerState") { // Switch or Light
            String value = json ["value"];
            if(value == "ON") {
                turnOn(deviceId);
            } else {
                turnOff(deviceId);
            }
        }
        else if (action == "SetTargetTemperature") {
            String deviceId = json ["deviceId"];     
            String action = json ["action"];
            String value = json ["value"];
        }
        else if (action == "test") {
            Serial.println("[WSc] received test command from sinric.com");
        }
      }
      break;
    case WStype_BIN:
      Serial.printf("[WSc] get binary length: %u\n", length);
      break;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(device_1, OUTPUT);
  pinMode(device_2, OUTPUT);
  pinMode(device_3, OUTPUT);
  pinMode(device_4, OUTPUT);
  pinMode(device_5, OUTPUT);
  pinMode(device_6, OUTPUT);
  pinMode(device_7, OUTPUT);
  pinMode(device_8, OUTPUT);
  digitalWrite(device_1, HIGH);
  digitalWrite(device_2, HIGH);
  digitalWrite(device_3, HIGH);
  digitalWrite(device_4, HIGH);
  digitalWrite(device_5, HIGH);
  digitalWrite(device_6, HIGH);
  digitalWrite(device_7, HIGH);
  digitalWrite(device_8, HIGH);
  
  WiFiMulti.addAP(MySSID, MyWifiPassword);
  Serial.println();
  Serial.print("Connecting to Wifi: ");
  Serial.println(MySSID);  

  // Waiting for Wifi connect
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if(WiFiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.print("WiFi connected. ");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  // server address, port and URL
  webSocket.begin("iot.sinric.com", 80, "/");

  // event handler
  webSocket.onEvent(webSocketEvent);
  webSocket.setAuthorization("apikey", MyApiKey);
  
  // try again every 5000ms if connection has failed
  webSocket.setReconnectInterval(5000);   // If you see 'class WebSocketsClient' has no member named 'setReconnectInterval' error update arduinoWebSockets
}

void loop() {
  webSocket.loop();
  
  if(isConnected) {
      uint64_t now = millis();
      
      // Send heartbeat in order to avoid disconnections during ISP resetting IPs over night.
      if((now - heartbeatTimestamp) > HEARTBEAT_INTERVAL) {
          heartbeatTimestamp = now;
          webSocket.sendTXT("H");          
      }
  }   
}
