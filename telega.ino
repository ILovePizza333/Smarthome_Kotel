
void newMsg(FB_msg& msg) {
  Serial.print(msg.chatID);  Serial.print(", ");  Serial.print(msg.username);  Serial.print(", ");  Serial.println(msg.text);
  if (msg.text == "/podval_data") {
    msg.text = "Температура подвал:";
    msg.text += t;
    msg.text += "\r\n";
    msg.text += "Температура газ:";
    msg.text += temp_ds;
    bot.sendMessage(msg.text, msg.chatID);
  }
}

void telega_send(String mess) {
  bot.sendMessage(mess, "122190844");
}
