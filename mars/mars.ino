#include <toneAC.h>
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(49, 53);  // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

int recieved_data[3];  // массив принятых данных

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

unsigned long current_millis;                                               //счётчик времени с запуска
unsigned long last_radio_recive_time;                                       //счётчик времени с последнего приёма радиосигнала
unsigned long last_serial_recive_time;

bool serial_communication_enable;
bool radio_communication_enable;
bool motor_enable;


void setup() {
  read_launch_parameters();
  set_launch_parameters();

  //контрольный звук
  toneAC(4000);    // Включить тон 440 Гц
  delay(100);
  noToneAC();      // Выключить звук




  Serial.begin(115200);                       // открываем порт для связи с ПК
  radio.begin();                            //активировать модуль
  radio.setAutoAck(1);                      // режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);                  // (время между попыткой достучаться, число попыток)
  radio.enableAckPayload();                 // разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);                 // размер пакета, в байтах
  radio.openReadingPipe(1, address[0]);     // хотим слушать трубу 0
  radio.setChannel(0x70);                   // выбираем канал (в котором нет шумов!)
  radio.setPALevel (RF24_PA_MAX);           // уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS);         // скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  radio.powerUp();                          // начать работу
  radio.startListening();                   // начинаем слушать эфир, мы приёмный модуль
}

void loop() {




  current_millis = millis();          // обновление счётчика времени



  byte pipeNo;
  while ( radio.available(&pipeNo) && radio_communication_enable == 1) {
    radio.read(&recieved_data, sizeof(recieved_data));
    last_radio_recive_time = current_millis;
    noToneAC();   // Выключить звук
  }










  if (serial_communication_enable == 1) {
    if (Serial.available() > 0) {  //если есть доступные данные
      last_serial_recive_time = current_millis;
      String command = Serial.readStringUntil('\n');
    }
    if (current_millis - last_serial_recive_time > 100) {
      serial_connect_error();
    }
    String outgoing_serial_data = " {\"rd\": ["  + String(recieved_data[0]) + "," + String(recieved_data[1]) + "," + String(recieved_data[2]) + "]}";
    // Serial.println(outgoing_serial_data);
  }



  //вызов ошибки потери радио сигнала
  if (current_millis - last_radio_recive_time > 100 && radio_communication_enable == 1) {
    radio_error();
  }





  //вызов функции двигалей
  motor(recieved_data[2], recieved_data[1]);



  Serial.println(radio_communication_enable);


}
