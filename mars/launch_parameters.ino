

void read_launch_parameters() {
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);




  serial_communication_enable = !digitalRead(3);
  motor_enable = !digitalRead(4);                       //включение двигателей
  radio_communication_enable = !digitalRead(5);



}


void set_launch_parameters() {
  digitalWrite(47, motor_enable);
  if (radio_communication_enable == 0) {
    set_zero_radio_date();
  }
}
