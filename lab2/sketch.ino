#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include "Adafruit_BMP085_U.h"

DHT dht(2, DHT22);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Убедитесь, что адрес правильный, например, 0x3F, 0x27
RTC_DS1307 rtc;
Adafruit_BMP085_Unified bmp;

float hum, temp;
int h, m, s;
long pres;  // Тип long для давления

void setup() {
  Serial.begin(9600);  // Для отладки через Serial Monitor

  dht.begin();
  rtc.begin();
  bmp.begin();  // Инициализация датчика BMP085
  lcd.init();
  lcd.backlight();

  // Выводим на Serial Monitor для проверки
  Serial.println("Setup Complete.");
}

void loop() {
  hum  =  dht.readHumidity();
  temp = dht.readTemperature();
  
  // Получаем данные о давлении
  sensors_event_t event;
  bmp.getEvent(&event);  // Получаем событие от BMP085
  if (event.pressure) {
    pres = event.pressure;  // Получаем давление, если оно доступно
  }

  // Получаем текущее время
  DateTime now = rtc.now();
  h = now.hour();
  m = now.minute();
  s = now.second();

  // Отладка: выводим данные на Serial Monitor
  Serial.print("Time: ");
  Serial.print(h);
  Serial.print(":");
  Serial.print(m);
  Serial.print(":");
  Serial.println(s);
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.print("Pressure: ");
  Serial.print(pres);
  Serial.println(" PA");
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  // Вывод на LCD
  lcd.clear();  // Очищаем экран перед выводом новых данных
  lcd.setCursor(0, 0);
  lcd.print(h);
  lcd.print(":");
  lcd.print(m);
  lcd.print(":");
  lcd.print(s);
  lcd.print(" ");
  lcd.print(temp);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print(pres);
  lcd.print("PA ");
  lcd.print(hum);
  lcd.print("%");

  delay(1000);  // Обновление данных каждую секунду
}
