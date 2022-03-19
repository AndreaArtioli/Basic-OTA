
#define STRINGIZE(x) #x
#define STRINGIZE_VALUE_OF(x) STRINGIZE(x)

#ifdef ESP32
  #include <WiFi.h>
#endif

#ifdef ESP8266
  #include <ESP8266WiFi.h>
#endif
#include <ArduinoOTA.h>

void setup() {
  #ifdef PORT
    ArduinoOTA.setPort(PORT);
  #endif
  
  WiFi.mode(WIFI_STA);

  //#ifdef NETWORK_NAME and NETWORK_PASSWORD
  WiFi.begin(STRINGIZE_VALUE_OF(NETWORK_NAME), STRINGIZE_VALUE_OF(NETWORK_PASSWORD));

  Serial.begin(9600);
  while(!Serial);

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    //Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  #ifdef OTA_PASSWORD
    // If you want authentication, uncomment this line
    ArduinoOTA.setPassword(STRINGIZE_VALUE_OF(OTA_PASSWORD));
  #endif

  #ifdef HOSTNAME
    ArduinoOTA.setHostname(STRINGIZE_VALUE_OF(HOSTNAME));
    WiFi.setHostname(STRINGIZE_VALUE_OF(HOSTNAME));
  #else
    ArduinoOTA.setHostname("ESP_OTA");
    WiFi.setHostname("ESP_OTA");
  #endif
  
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle();
  delay(100);
  Serial.print("Hostname vero: ");
  Serial.println(WiFi.getHostname());
  Serial.print("Hostname voluto: ");
  Serial.println(STRINGIZE_VALUE_OF(HOSTNAME));
}
