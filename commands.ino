void command() {
  server.on("/", []() {//если отправлен запрос на главную страницу сайта 
    web();//обновляем сайт
    server.send(200, "text/html", webPage);//отвечаем клиенту
  });


  server.on("/SVET", []() {//если отправлен запрос на адрес http://192.168.43.94/SVET/
   
    web();//обновляем страницу
    server.send(200, "text/html", webPage);//отвечаем клиенту

  });


  
  server.on("/UPDATE", []() {
    web();
   // getTemperature();
    server.send(200, "text/html", webPage);

  });

  server.on("/RESET", []() {
    Serial.println("RESET");
    web();
    server.send(200, "text/html", webPage);
    delay(100);
    ESP.restart();
  });
  server.begin();//старт сервера
  
}
