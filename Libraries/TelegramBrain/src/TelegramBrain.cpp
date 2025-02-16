#include "TelegramBrain.h"
#include <functional>

TelegramBrain::TelegramBrain(const char* token, const char* chatId)
  : token(token), chatId(chatId), bot(token, secured_client) {
    secured_client.setInsecure();
}

void TelegramBrain::sendMessage(String message) {
  // Adiciona uma borda simples para embelezar a mensagem
  String border = "------------------------------------\n";
  String msg = border + "📩 Enviando mensagem...\n\n";
  msg += message + "\n\n";
  msg += "✅ Mensagem enviada com sucesso!";
  msg += "\n" + border;
  
  // Envia a mensagem formatada
  bot.sendMessage(chatId, msg);

  // Log no serial para verificação
  Serial.println("Mensagem enviada: " + msg);
}


void TelegramBrain::sendPhoto(camera_fb_t* fb) {
  const char* myDomain = "api.telegram.org";
  if (secured_client.connect(myDomain, 443)) {
      Serial.println("Connection successful");
      
      String head = "--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"chat_id\"; \r\n\r\n" + String(chatId) + "\r\n--RandomNerdTutorials\r\nContent-Disposition: form-data; name=\"photo\"; filename=\"esp32-cam.jpg\"\r\nContent-Type: image/jpeg\r\n\r\n";
      String tail = "\r\n--RandomNerdTutorials--\r\n";

      size_t imageLen = fb->len;
      size_t extraLen = head.length() + tail.length();
      size_t totalLen = imageLen + extraLen;
    
      secured_client.println("POST /bot"+ String(token) + "/sendPhoto HTTP/1.1");
      secured_client.println("Host: " + String(myDomain));
      secured_client.println("Content-Length: " + String(totalLen));
      secured_client.println("Content-Type: multipart/form-data; boundary=RandomNerdTutorials");
      secured_client.println();
      secured_client.print(head);
    
      uint8_t *fbBuf = fb->buf;
      size_t fbLen = fb->len;
      for (size_t n=0;n<fbLen;n=n+1024) {
        if (n+1024<fbLen) {
          secured_client.write(fbBuf, 1024);
          fbBuf += 1024;
        }
        else if (fbLen%1024>0) {
          size_t remainder = fbLen%1024;
          secured_client.write(fbBuf, remainder);
        }
      }  
      
    secured_client.print(tail);
    Serial.println("Mensagem enviada: ");
  }
}

void TelegramBrain::setupTelegram(String version, String espName) {
  String msg = "🚀 **Sistema Ativado!**\n\n";
  msg += "🔧 **Versão:** " + version + "\n";
  msg += "📡 **Nome ESP:** " + espName + "\n";
  msg += "✅ **Status:** Ativo\n\n";
  msg += "Tudo pronto para operar! 🚀";

  sendMessage(msg);
  Serial.println("Mensagem enviada: " + msg);
}



