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
  set_radio_config();

  //контрольный звук
  toneAC(4000);    // Включить тон 440 Гц
  delay(100);
  noToneAC();      // Выключить звук




  Serial.begin(115200);                       // открываем порт для связи с ПК


}

void loop() {




  current_millis = millis();          // обновление счётчика времени


  //********************РАДИО***************************
  if (radio_communication_enable == 1) {
    byte pipeNo;
    while ( radio.available(&pipeNo) ) {
      radio.read(&recieved_data, sizeof(recieved_data));
      last_radio_recive_time = current_millis;
      noToneAC();   // Выключить звук
      if (recieved_data[0] == 0) {
        set_zero_radio_date();
        break;
        
      }
    }
  }

  //********************РАДИО***************************




  //*******************ПОСЛЕДОВАТЕЛЬНЫЙ ПОРТ********************************

  if (serial_communication_enable == 1) {
    if (Serial.available() > 0) {  //если есть доступные данные
      last_serial_recive_time = current_millis;
      String command = Serial.readStringUntil('\n');
    }
    String outgoing_serial_data = " {\"rd\": ["  + String(recieved_data[0]) + "," + String(recieved_data[1]) + "," + String(recieved_data[2]) + "]}";
    Serial.println(outgoing_serial_data);
  }

  //*******************ПОСЛЕДОВАТЕЛЬНЫЙ ПОРТ********************************





  //*******************ДВИГАТЕЛИ********************************

  //вызов функции двигалей
  motor(recieved_data[2], recieved_data[1]);

  //*******************ДВИГАТЕЛИ********************************



  //***********ОБРАБОТЧИК ОШИБОК*********************

  //вызов ошибки потери радио сигнала
  if ((current_millis - last_radio_recive_time > 100 || recieved_data[0] == 0) && radio_communication_enable == 1) {
    radio_error();
  }
  //вызов ошибки потери последовательной связи
  if (current_millis - last_serial_recive_time > 1000000 && serial_communication_enable == 1) {
    serial_connect_error();
  }

  //***********ОБРАБОТЧИК ОШИБОК*********************








}
