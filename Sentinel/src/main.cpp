#include <Arduino.h>
#include <WifiHouses.h> 
#include <TelegramBrain.h>
#include "esp_camera.h"
#include <utility>
#include <configEspCam.h>
#include "soc/rtc_cntl_reg.h"  // Para usar os registradores RTC do ESP32

const char *version = "0.0.2.0";
const char *lastCommit = "MVP projeto"; 
const char *espName = "Sentinel";
const char *telecatTokenID = "7506100450:AAGT3kzFRoAyXHP5lL4tfgj61TlT-CcF9sg";
const char *houseCarolinaChatId = "-1002271180205";
const char *telecatChatId = "6762474693";

TelegramBrain telegramBotDebug(telecatTokenID,
                          telecatChatId);
TelegramBrain telegramBotHouseCarolina(telecatTokenID,
                          houseCarolinaChatId);

camera_fb_t* fb = NULL;

int pirPin = 12; 
int count = 10;
int state = 0;
int ledPin = 4;

void setupLed() {
  pinMode(ledPin, OUTPUT);
  for (int i = 0; i < 5; i++) {
  digitalWrite(ledPin, HIGH);
  delay(100);
  digitalWrite(ledPin, LOW);
  delay(100);
  }
}

camera_fb_t* capturePhoto() {
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  delay(2000);
  for (int i = 0; i < 100; i++) {
    camera_fb_t * fb = esp_camera_fb_get();
    if (!fb) {
    Serial.println("Failed to capture frame");
    continue;
  }
  esp_camera_fb_return(fb);
  }
  camera_fb_t* fb = esp_camera_fb_get();

  String contentType = (fb->format == PIXFORMAT_JPEG) ? "image/jpeg" : "image/png";
  if (!fb) {
    Serial.println("Falha ao capturar imagem");
    return fb;
  }

  Serial.println("Imagem capturada com sucesso!");
  digitalWrite(ledPin, LOW);
  return fb;
}

void setupTelegramBot() {
  telegramBotDebug.setupTelegram(version, espName);
  telegramBotHouseCarolina.setupTelegram(version, espName);
}

void sendPhotoTelegram() {
  fb = capturePhoto();
  telegramBotDebug.sendPhoto(fb);
  telegramBotHouseCarolina.sendPhoto(fb);
  esp_camera_fb_return(fb);
}

void sendMessageTelegram(String message) {
  telegramBotDebug.sendMessage(message);
  telegramBotHouseCarolina.sendMessage(message);
}

void trackCatPresence() {
    if (count > 0) {
      delay(500);
      count -= 1;
      if (digitalRead(pirPin) == 1) {
        count = 10;
      }
      trackCatPresence();
    } else {
      sendMessageTelegram("👋🏻 🐈‍⬛🐈‍⬛🐈‍⬛🐈‍⬛🐈‍⬛🐈‍⬛🐈‍");
      sendPhotoTelegram();
    }
}

void setup() {
  Serial.begin(115200); 
  Serial.println("- - - - Setup - - - -");
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  Serial.println(version);
  setupLed();
  pinMode(pirPin, INPUT);
  setupCam();
  wifiConnect();
  setupTelegramBot();
  Serial.println("- - - - Setup Concluído - - - -");
}


void loop() {
  state = digitalRead(pirPin);
  if (state == 1) {
    count = 10;
    sendMessageTelegram("💦 🐈‍⬛🐈‍⬛🐈‍⬛🐈‍⬛🐈‍⬛🐈‍⬛🐈‍");
    sendPhotoTelegram();
    trackCatPresence();
  } else {
  
  }
}
