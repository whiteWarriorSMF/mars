const int OnBoardBatteryAdcPoints[] = {0, 205, 410, 615, 820, 1023};  // Пример измеренных значений АЦП
const float OnBoardBatteryVoltagePoints[] = {0.0, 5.0, 7.5, 9.8, 11.2, 12.6}; // Реальные напряжения
const int OnBoardBatteryNumPoints = sizeof(OnBoardBatteryAdcPoints)/sizeof(OnBoardBatteryAdcPoints[0]);
// Функция полиномиальной аппроксимации
float getOnBoardBatteryCharge(int rawADC) {
  // Поиск ближайших точек для интерполяции
  int idx = 0;
  while (idx < OnBoardBatteryNumPoints-1 && OnBoardBatteryAdcPoints[idx+1] < rawADC) {
    idx++;
  }
  // Если вышли за пределы - возвращаем крайние значения
  if (idx == OnBoardBatteryNumPoints-1) return OnBoardBatteryVoltagePoints[OnBoardBatteryNumPoints-1];
  if (idx == 0 && rawADC <= OnBoardBatteryAdcPoints[0]) return OnBoardBatteryVoltagePoints[0]; 
  // Линейная интерполяция между точками
  float adc0 = OnBoardBatteryAdcPoints[idx];
  float adc1 = OnBoardBatteryAdcPoints[idx+1];
  float v0 = OnBoardBatteryVoltagePoints[idx];
  float v1 = OnBoardBatteryVoltagePoints[idx+1];
  return v0 + (v1 - v0) * (rawADC - adc0) / (adc1 - adc0);
}
