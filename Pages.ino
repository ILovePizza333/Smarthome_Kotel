void web() {
  //проверяем состояние переменных, присваеваем кнопкам цвета

  webPage = "";//обнуляем значение переменной

  webPage += "<html>";//начало html кода
  webPage += "<head>";//прописываем "шапку" сайта
  webPage += "<title>Добро пожаловать!</title>";//заголовок в поисковой строке
  webPage += "<meta http-equiv='Content-Type' content ='text/html; charset=utf-8'>";//устанавливаем тип контента, кодировку
  webPage += "<meta http-equiv='Refresh' content='5;http://";
  webPage += client_ip;
  webPage += "/UPDATE'>";
  webPage += "</head>";//конец "шапки"

  webPage += "<body style = 'background-color: #a6b2c3'>";//фоновый цвет
  webPage += "<h1 style='color: #000000' align = center >Датчики </h1>";//Первая стока
  webPage += "<style> p {margin-top: 2em;    margin-bottom: 1em;}</style>";//установка шрифта


  webPage += "<style> p {margin-top: 2em;  font-size:30px;  margin-bottom: 1em;}</style>";//установка шрифта
  //вывод температуры и влажности
  webPage += "<p align = center>Температура: ";
  webPage += t;
  webPage += "</p>";

  webPage += "<p align = center>Влажность: ";
  webPage += h;
  webPage += "</p>";
  /*
    webPage += "<p align = center>Давление: ";
    webPage += pressu;
    webPage += "</p>";
  */
  webPage += "<p align = center>Температура трубы: ";
  webPage +=  temp_ds ;
  webPage += "</p>";
/*
  webPage += "<p align = center>Температура бп: ";
  webPage +=  sensorValue ;
  webPage += "</p>";
 */
  webPage += "<p align = center><a href=\"UPDATE\"><button style='width:100px;height:100px'>Обновить</button></a>&nbsp;</p>";//кнопка обновления страницы

  webPage += "<p align = center><a href=\"RESET\"><button style='width:100px;height:100px'>Перезагрузка</button></a>&nbsp;</p>";//кнопка перезагрузки

  webPage += "</body>";//конец "тела" сайта

  webPage += "</html>";//конец html страницы
}
