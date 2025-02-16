#include "WifiHouses.h"

void wifiConnect() {
  const char *loginWifiAzHouse = "Az_house";
  const char *passwordAzHouse = "89204133";
  const char *loginWifiCarolinaHouse = "Stella_2G";
  const char *passwordCarolinaHouse = "19031946";

  WiFi.mode(WIFI_STA);

  WiFi.begin(loginWifiAzHouse, passwordAzHouse);
  unsigned long startTime = millis();
  
  while (WiFi.status() != WL_CONNECTED) {
    if (millis() - startTime > 30000) {
      Serial.println("Falha na conexão Wi-Fi Az_house. Tentando Judas...");
      break;
    }
    delay(1000);
    Serial.print(".");
  }

  if (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(loginWifiCarolinaHouse, passwordCarolinaHouse);
    startTime = millis();
    
    while (WiFi.status() != WL_CONNECTED) {
      if (millis() - startTime > 30000) {
        Serial.println("Falha na conexão Wi-Fi Judas após 30 segundos.");
        ESP.restart();  
      }
      delay(1000);
      Serial.print(".");
    }
  }

  Serial.println("Conexão Wi-Fi bem-sucedida!!!");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
