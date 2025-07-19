
//******************************ПОЛИНОМ ЗНАЧЕНИЙ ДЛЯ БОРТОВОГО АКБ************************


float getOnBoardBatteryCharge(int rawADC) {
  float voltage = map(rawADC, 0, 999, 0, 1230);
  return voltage / 100;
}

//******************************ПОЛИНОМ ЗНАЧЕНИЙ ДЛЯ БОРТОВОГО АКБ************************




//******************************ПОЛИНОМ ЗНАЧЕНИЙ ДЛЯ ХОДОВОГО АКБ************************


float getRideBatteryCharge(int rawADC) {
  float voltage = map(rawADC, 0, 999, 0, 1210);
  return voltage / 100;
}

//******************************ПОЛИНОМ ЗНАЧЕНИЙ ДЛЯ ХОДОВОГО АКБ************************





//******************************ПОЛИНОМ ЗНАЧЕНИЙ ДЛЯ ПРЕОБРАЗОВАТЕЛЯ РАДИОМОДУЛЯ*******************************

// Калибровочные данные: значения АЦП и соответствующие напряжения
const int radioModuleVoltageConvertorAdcPoints[] = {0, 205, 410};  // Пример измеренных значений АЦП
const float radioModuleVoltageConvertorVoltagePoints[] = {0.0, 1.0, 3.3}; // Реальные напряжения
const int radioModuleVoltageConvertorNumPoints = sizeof(radioModuleVoltageConvertorAdcPoints) / sizeof(radioModuleVoltageConvertorAdcPoints[0]);

// Функция полиномиальной аппроксимации
float getRadioModuleVoltageConvertorVoltage(int rawADC) {
  // Поиск ближайших точек для интерполяции
  int idx = 0;
  while (idx < radioModuleVoltageConvertorNumPoints - 1 && radioModuleVoltageConvertorAdcPoints[idx + 1] < rawADC) {
    idx++;
  }

  // Если вышли за пределы - возвращаем крайние значения
  if (idx == radioModuleVoltageConvertorNumPoints - 1) return radioModuleVoltageConvertorVoltagePoints[radioModuleVoltageConvertorNumPoints - 1];
  if (idx == 0 && rawADC <= radioModuleVoltageConvertorAdcPoints[0]) return radioModuleVoltageConvertorVoltagePoints[0];

  // Линейная интерполяция между точками
  float adc0 = radioModuleVoltageConvertorAdcPoints[idx];
  float adc1 = radioModuleVoltageConvertorAdcPoints[idx + 1];
  float v0 = radioModuleVoltageConvertorVoltagePoints[idx];
  float v1 = radioModuleVoltageConvertorVoltagePoints[idx + 1];

  return v0 + (v1 - v0) * (rawADC - adc0) / (adc1 - adc0);
}
//******************************ПОЛИНОМ ЗНАЧЕНИЙ ДЛЯ ПРЕОБРАЗОВАТЕЛЯ РАДИОМОДУЛЯ*******************************





String check_voltage() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  String Sdata = String(getOnBoardBatteryCharge(analogRead(A0))) + " "
                 + String(getRideBatteryCharge(analogRead(A1))) + " "
                 + String(getRadioModuleVoltageConvertorVoltage(analogRead(A2)));

  return Sdata;

}
