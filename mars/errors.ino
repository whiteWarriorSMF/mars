unsigned long radio_error_delay_counter;
unsigned long serial_connect_error_delay_counter;



void radio_error() {
  set_zero_radio_date();
  if (current_millis - radio_error_delay_counter > 300) {
    toneAC(1000);  // Включить тон 440 Гц
  }
  if (current_millis - radio_error_delay_counter > 400) {
    noToneAC();   // Выключить звук
    radio_error_delay_counter = current_millis;
  }

}


void serial_connect_error() {
  if (current_millis - serial_connect_error_delay_counter > 400 && current_millis - serial_connect_error_delay_counter < 500) {
    toneAC(3000);  // Включить тон 440 Гц
  }
  if (current_millis - serial_connect_error_delay_counter > 450 && current_millis - serial_connect_error_delay_counter < 550) {
    noToneAC();   // Выключить звук
  }
  if (current_millis - serial_connect_error_delay_counter > 500) {
    toneAC(3000);  // Включить тон 440 Гц
  }
  if (current_millis - serial_connect_error_delay_counter > 550) {
    noToneAC();   // Выключить звук
    serial_connect_error_delay_counter = current_millis;
  }
}



void voltage_error() {
}


void low_voltage_error() {
    if (current_millis - radio_error_delay_counter > 100) {
    toneAC(5000);  // Включить тон 440 Гц
  }
  if (current_millis - radio_error_delay_counter > 200) {
    noToneAC();   // Выключить звук
    radio_error_delay_counter = current_millis;
  }
}
