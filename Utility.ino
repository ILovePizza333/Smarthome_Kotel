
void ds18b20_set() {
  ds.begin();
  // показываем сколько датчиков нашли на шине
  Serial.print("Found ");  Serial.print(ds.getDeviceCount(), DEC);  Serial.println(" devices.");
  // достаем адрес датчика с индесом 0
  if (!ds.getAddress(sensor0, 0)) {
    Serial.println("Unable to find address for Device 0");
  }
  // отпаравляем адрес из массива в монитор порта
  Serial.print("address sensor 0: ");
  for (uint8_t i = 0; i < 8; i++)  {
    Serial.print("0x");    Serial.print(sensor0[i], HEX);    Serial.print(", ");
  }
  Serial.println();
  // устанавливаем разрешение датчика 11 бит (может быть 9, 10, 11, 12) на точность измерения температуры показатель не влияет.
  ds.setResolution(sensor0, 11);
}

void getTemperature_ds18b20() {
  ds.requestTemperatures();                  // считываем температуру с датчиков
  Serial.println("Проверка температуры"); Serial.print("Sensor 0: ");  Serial.print(ds.getTempC(sensor0));  Serial.println("C  ");
  if (ds.getTempC(sensor0) == -127.00) {
    temp_ds = -100;
    if (flag_gas != -1) {
      telega_send("GAS error!!!");
      flag_gas = -1;
    }
  } else {
    temp_ds = ds.getTempC(sensor0) * 1.1 ; //* 1.095
    if (temp_ds >= 70.00 && temp_ds <= 72.00 && flag_gas == 0) {
      telega_send("GAS 70+");
      flag_gas = 1;
    } else if (temp_ds >= 72.00 && temp_ds <= 74.00 && flag_gas <= 1) {
      telega_send("GAS 72+");
      flag_gas = 2;
    }
    else if (temp_ds >= 74.00 && flag_gas <= 2) {
      telega_send("GAS 74+!!!");
      flag_gas = 3;
    }
    else if (temp_ds < 70.00 && flag_gas != 0) {
      flag_gas = 0;
    }
  }
}

void getTemperature_dht() {
  h = dht.readHumidity() ;//считываем показания влажности
  temp_dht = dht.readTemperature() ; //считываем показания температуры
  if (isnan(h) || isnan(temp_dht)) {//если значение неверное
    temp_dht = 0;//температуру устанавливаем в 0
    h = 0;//влажность устанавливаем в 0
    return;//возвращаемся в предыдущее место кода
  }

}
void getData_bme() {
  //Serial.println("Проверка температуры");
  if (!status) {
    Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
    Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(), 16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    t = 0;
    h = 0;
  } else {
    t = bme.readTemperature() - 2.2 ; //* 0.9
    //Serial.print("Temperature = ");  Serial.print(temp_ds);   Serial.println(" *C");
    // pressu = bme.readPressure() / 100.0F;
    //Serial.print("Pressure = ");    Serial.print(pressu);   Serial.println(" hPa");
    h = bme.readHumidity() * 0.5; // * 0.625
    //  Serial.print("Humidity = ");  Serial.print(Humidity);  Serial.println(" %");
  }
  // отправляем температуру
}

void autocool() {
  sensorValue = analogRead(sensorPin);
  if (sensorValue >= 600 ) {
    digitalWrite(coolerPin, HIGH);
  } else if (sensorValue <= 530 ) {
    digitalWrite(coolerPin, LOW);
  }
}
