#include "cooler.h"



void urlSetup(){
    server.on("/win", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    Serial.println("Device being searched via mDNS dicovery");
    wledParser(request);
    });
    

server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", index_html); });
  server.on("/logged-out", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send_P(200, "text/html", logout_html); });
  server.on("/logout", HTTP_GET, [](AsyncWebServerRequest *request)
            { request->send(401); });

  // Send a GET request to control output socket <ESP_IP>/output?state=<fanSpeed>
  server.on("/output", HTTP_GET, [](AsyncWebServerRequest *request)
            {
    // if(!request->authenticate(http_username, http_password))
    //   return request->requestAuthentication();
   
    if (request->hasParam("fan")) {
      fanSpeed = request->getParam("fan")->value().toInt();
      
      if(fanSpeed == 0){
        digitalWrite(speedMid, HIGH);
        digitalWrite(speedHigh,HIGH);
        digitalWrite(ledPin, HIGH);
        Serial.println("Got speed 0");
        request->send(200, "text/plain", "OK");
      
      }
      else if (fanSpeed == 1)
      {
        digitalWrite(speedMid, HIGH);
        digitalWrite(speedHigh, LOW);
        digitalWrite(ledPin, LOW);
        Serial.println("Got speed 1");
        request->send(200, "text/plain", "OK");
      }
      else if (fanSpeed == 2)
      {
        digitalWrite(speedMid, LOW);
        digitalWrite(speedHigh, HIGH);
        digitalWrite(ledPin, LOW);
        Serial.println("Got speed 2");
        request->send(200, "text/plain", "OK");
      }
      // else if (fanSpeed == 3)
      // {
      //   digitalWrite(speedMid, HIGH);
      //   digitalWrite(speedHigh, LOW);
      //   digitalWrite(ledPin, LOW);
      //   Serial.println("Got speed 3");
      //   request->send(200, "text/plain", "OK");
      // }
     
      request->send(200, "text/plain", "OK");
      
    }
    
    if (request->hasParam("pump")) {
      pumpSpeed = request->getParam("pump")->value().toInt();
      digitalWrite(pumpPin, !pumpSpeed);
      request->send(200, "text/plain", "OK");
    }

    if (request->hasParam("direction")) {
      direction = request->getParam("direction")->value().toInt();
      digitalWrite(directionPin, !direction);
      request->send(200, "text/plain", "OK");
    }
    request->send(200, "text/plain", "Failed"); });

    
}

