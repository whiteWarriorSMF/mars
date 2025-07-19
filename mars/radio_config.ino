void set_radio_config() {
  pinMode(42, OUTPUT);                      // пин отключения преобразователя
  radioModuleVoltageConvertorEnable(radio_communication_enable);
  radio.begin();                            // активировать модуль
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

void radioModuleVoltageConvertorEnable(int state) {
  digitalWrite(42, state);
}
