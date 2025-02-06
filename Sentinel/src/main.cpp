#include <Arduino.h>
#include <WifiHouses.h> 
#include <TelegramBrain.h>
#include "esp_camera.h"
#include <utility>
#include <configEspCam.h>


const char *version = "0.0.1.0";
const char *espName = "Sentinel";
TelegramBrain telegramBot("7506100450:AAGT3kzFRoAyXHP5lL4tfgj61TlT-CcF9sg",
                          "-1002271180205");
camera_fb_t* fb = NULL;

camera_fb_t* capturePhoto() {
  camera_fb_t* fb = esp_camera_fb_get();

  String contentType = (fb->format == PIXFORMAT_JPEG) ? "image/jpeg" : "image/png";
  if (!fb) {
    Serial.println("Falha ao capturar imagem");
    return fb;
  }

  Serial.println("Imagem capturada com sucesso!");
  return fb;
}

void setup() {
  Serial.begin(115200); 
  delay(10000);
  Serial.println("- - - - Setup - - - -");
  Serial.println(version);
  setupCam();
  delay(3000);
  wifiConnect();
  telegramBot.setupTelegram(version, espName);
  Serial.println("- - - - Setup Concluído - - - -");
}

void getPhoto() {
  fb = capturePhoto();
  telegramBot.sendPhoto(fb);
  esp_camera_fb_return(fb);
}

void loop() {

}