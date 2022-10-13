#include <ESP8266WiFi.h>//библиотека для подключения WiFi модуля 
#include <ESP8266WebServer.h>//библиотека для создания сервера
#include <ArduinoOTA.h>//библиотека для обновления по WiFi

#include <FastBot.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
//101- подвал дата
//102- вход
const char* ssid = "UPVEL";   const char* password = "12345678";//логин и пароль роутера
String client_ip = "192.168.10.101";//каждые 5 секунд обновляем страницу 149- влад 67- я
IPAddress ip (192, 168, 10, 101);//локальный ip //не забывай про обновление 67 -я 209- влад
IPAddress gateway (192, 168, 10, 1);//адрес роутера в сети
IPAddress subnet (255, 255, 255, 0);//макска подсети
IPAddress primaryDNS(8, 8, 8, 8);   //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional
const char* OTAPSWD = "data";


ESP8266WebServer server(80);//инициализация сервера esp8266

const char BotToken[] = "905399471:AAFXwqGGWDI4GcXkaU2eVMmVytU1wf9dxwU";// инициализация Telegram бота
FastBot bot(BotToken);

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
Adafruit_BME280 bme; // I2C
unsigned status;
float h , t, pressu;

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D8
OneWire oneWire(ONE_WIRE_BUS);

// передаем объект oneWire объекту DS18B20:
DallasTemperature ds(&oneWire);
DeviceAddress sensor0;
float temp_ds = 0;


#include "DHT.h"// Библиотека датчика температуры и влажности
#define DHTPIN D7 // вывод к датчику температуры и влажности
#define DHTTYPE DHT11//тип датчика температуры и влажности
DHT dht(DHTPIN, DHTTYPE);//инициализация датчика температуры и влажности
float  temp_dht;

int flag_gas = 0;

String webPage = "";//переменная для хранения html страницы

unsigned long current_time, last_time, last_time_telega; //временные переменные



int sensorPin = A0;
int coolerPin = D13;
int sensorValue = 0;

void setup(void) {//цикл инициализации
  Serial.begin(115200);//старт сериал порта

  WiFi.mode(WIFI_STA);//режим станции(подключение к действующей точке доступа)
  WiFi.config(ip, gateway, subnet, primaryDNS, secondaryDNS);
  WiFi.begin(ssid, password); //старт WIFI соединения
  while (WiFi.status() != WL_CONNECTED) { // ждем соединения
    delay(50);
  }
  Serial.print("\nIP address: ");   Serial.println(WiFi.localIP());//вывод локального IP устройства

  pinMode(coolerPin, OUTPUT);

  ds18b20_set();
  getTemperature_ds18b20();

  status = bme.begin();
  dht.begin();

  // getTemperature_dht();// функция получения температуры с датчика
  getData_bme();// функция получения температуры с датчика
  web();//функция формирования html страницы с обновленными переменными
  command();//инициализация возможных запросов и назначение ответных действий

  ArduinoOTA.setPort(8266);// порт для обновления по WiFi
  ArduinoOTA.setHostname("Data");// имя устройства для обновления по WiFi
  ArduinoOTA.setPassword(OTAPSWD);
  ArduinoOTA.begin();//старт возможности беспроводного обновления

  bot.attach(newMsg);
}

void loop(void) {//бесконечный цикл
  current_time = millis();//присваем переменной время работы мк со старта
  if (current_time - last_time >= 1000 ) {
    getData_bme();// функция получения температуры с датчика
    //  getTemperature_dht();//проверяем температуру и влажность
    getTemperature_ds18b20();
    last_time = millis();//сбрасываем счетчик

  }

  bot.tick();
  server.handleClient();//обрабатываем клиента при наличии
  ArduinoOTA.handle();//при наличии обновления- устанавливаем
}
