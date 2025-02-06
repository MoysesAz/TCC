from telegram import Update, Message
from telegram.ext import Application, MessageHandler, CommandHandler, filters, CallbackContext

# Função para responder com a mesma mensagem recebida (mensagens de texto)
async def echo_text(update: Update, context: CallbackContext) -> None:
    chat_id = update.message.chat_id
    print(f"Chat ID: {chat_id}")  # Imprime o ID do chat no terminal

    # Responde com a mesma mensagem que o bot recebeu
    await update.message.reply_text(update.message.text)

# Função para responder a comandos
async def handle_command(update: Update, context: CallbackContext) -> None:
    command = update.message.text
    chat_id = update.message.chat_id

    # Aqui você pode adicionar um comportamento específico para comandos
    if command == "/start":
        await update.message.reply_text("Olá! Eu sou o seu bot.")
    elif command == "/help":
        await update.message.reply_text("Como posso te ajudar?")
    else:
        await update.message.reply_text(f"Comando desconhecido: {command}")

# Função para responder a imagens enviadas
async def handle_image(update: Update, context: CallbackContext) -> None:
    chat_id = update.message.chat_id
    print(f"Chat ID: {chat_id}")  # Imprime o ID do chat no terminal

    # Responde confirmando o recebimento de uma imagem
    await update.message.reply_text("Recebi a imagem! 😊")

# Função principal para rodar o bot
def main():
    # Insira o token do seu bot que você obteve do BotFather
    token = '7506100450:AAGT3kzFRoAyXHP5lL4tfgj61TlT-CcF9sg'

    # Cria o Application
    application = Application.builder().token(token).build()

    # Adiciona handlers para diferentes tipos de mensagem
    application.add_handler(CommandHandler("start", handle_command))  # Comando /start
    application.add_handler(CommandHandler("help", handle_command))   # Comando /help
    application.add_handler(MessageHandler(filters.TEXT & ~filters.COMMAND, echo_text))  # Mensagens de texto
    application.add_handler(MessageHandler(filters.PHOTO, handle_image))  # Imagens enviadas

    # Inicia o bot
    application.run_polling()  # Fica escutando as mensagens recebidas

if __name__ == '__main__':
    main()
