#ifndef TELEGRAMBRAIN_H
#define TELEGRAMBRAIN_H

#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <esp_camera.h>
#include <functional>

class TelegramBrain {
  private:
    const char* token;
    const char* chatId;
    WiFiClientSecure secured_client;
    UniversalTelegramBot bot;

  public:
    TelegramBrain(const char* token, const char* chatId);

    void sendMessage(String message);

    void sendPhoto(camera_fb_t* fb);

    void setupTelegram(String version, String espName);
};

#endif // TELEGRAMBRAIN_H
