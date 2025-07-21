
int OnBoardBatteryControlPin = A1;
int RideBatteryControlPin = A0;
int RadioModuleVoltageConvertorControlPin = A2;


//******************************СБОР ЗНАЧЕНИЙ ДЛЯ БОРТОВОГО АКБ************************
float getOnBoardBatteryCharge() {

  float voltage = map(analogRead(RideBatteryControlPin), 0, 999, 0, 1230);
  return voltage;
}
//******************************СБОР ЗНАЧЕНИЙ ДЛЯ БОРТОВОГО АКБ************************



//******************************СБОР ЗНАЧЕНИЙ ДЛЯ ХОДОВОГО АКБ************************
float getRideBatteryCharge() {
  float voltage = map(analogRead(OnBoardBatteryControlPin), 0, 999, 0, 1210);
  return voltage;
}
//******************************СБОР ЗНАЧЕНИЙ ДЛЯ ХОДОВОГО АКБ************************




//******************************СБОР ЗНАЧЕНИЙ ДЛЯ ПРЕОБРАЗОВАТЕЛЯ РАДИОМОДУЛЯ*******************************
float getRadioModuleVoltageConvertorVoltage() {
  float voltage = map(analogRead(RadioModuleVoltageConvertorControlPin), 0, 715, 0, 330);
  return voltage;
}
//******************************СБОР ЗНАЧЕНИЙ ДЛЯ ПРЕОБРАЗОВАТЕЛЯ РАДИОМОДУЛЯ*******************************





String check_voltage() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  String Sdata = String(getOnBoardBatteryCharge() / 100) + "v "
                 + String(getRideBatteryCharge() / 100) + "v "
                 + String(getRadioModuleVoltageConvertorVoltage() / 100)+ "v";
  /*
    String SdataPercent = String(map(getOnBoardBatteryCharge(), 900, 1260, 0, 100)) + "% "
                                 + String(map(getRideBatteryCharge(), 900, 1260, 0, 100)) + "% "
                                 + String(getRadioModuleVoltageConvertorVoltage()/100) + "%";
  */
  return Sdata;

}
