#include <Arduino.h>
#include <WifiHouses.h> 
#include <TelegramBrain.h>
#include "esp_camera.h"
#include <utility>
#include <configEspCam.h>
#include "soc/rtc_cntl_reg.h"  // Para usar os registradores RTC do ESP32

const char *version = "0.0.1.3";
const char *espName = "Sentinel";
const char *telecatTokenID = "7506100450:AAGT3kzFRoAyXHP5lL4tfgj61TlT-CcF9sg";
const char *houseStellaChatId = "-1002271180205";
const char *telecatChatId = "6762474693";

TelegramBrain telegramBot(telecatTokenID,
                          telecatChatId);
camera_fb_t* fb = NULL;

void getPhoto();

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
void getPhoto() {
  fb = capturePhoto();
  telegramBot.sendPhoto(fb);
  esp_camera_fb_return(fb);
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
  getPhoto();
  Serial.println("- - - - Setup Concluído - - - -");
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
}



void loop() {

}