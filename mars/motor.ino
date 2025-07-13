int motor_enable_pin = 47;
int rigt_forvard_pin = 2;
int left_forvard_pin = 44;
int right_back_pin = 46;
int left_back_pin = 45;

int y_pos = 512;
int x_pos = 512;
int normalized_y_pos;
int normalized_x_pos;


int left_side = 0; //a
int right_side = 0; //b

void motor_init() {
  pinMode(motor_enable_pin, OUTPUT);
  pinMode(rigt_forvard_pin, OUTPUT);
  pinMode(left_forvard_pin, OUTPUT);
  pinMode(right_back_pin, OUTPUT);
  pinMode(left_back_pin, OUTPUT);

}


void motor_ena(bool state) {
  digitalWrite(47, state);
}


void motor(int x, int y) {
  normalized_y_pos = map(y, 0, 1024, 255, -255);
  normalized_x_pos = map(x, 0, 1024, -255, 255);
  if (normalized_x_pos > 0) {
    left_side = normalized_y_pos;
    right_side = map(normalized_x_pos, 127, 0, 0, normalized_y_pos);
  }
  if (normalized_x_pos == 0) {
    left_side = normalized_y_pos;
    right_side = normalized_y_pos;
  }
  if (normalized_x_pos < 0) {
    left_side = map(normalized_x_pos, -127, 0, 0, normalized_y_pos);
    right_side = normalized_y_pos;
  }
  left_side = constrain(left_side, -255, 255);
  right_side = constrain(right_side, -255, 255);
  if (right_side > 0) {
    analogWrite(rigt_forvard_pin, right_side);
    analogWrite(right_back_pin, 0);
  }
  if (right_side < 0) {
    analogWrite(rigt_forvard_pin, 0);
    analogWrite(right_back_pin, -right_side);
  }
  if (right_side == 0) {
    analogWrite(rigt_forvard_pin, 0);
    analogWrite(right_back_pin, 0);
  }
  if (left_side > 0) {
    analogWrite(left_forvard_pin, left_side);
    analogWrite(left_back_pin, 0);
  }
  if (left_side < 0) {
    analogWrite(left_forvard_pin, 0);
    analogWrite(left_back_pin, -left_side);
  }
  if (left_side == 0) {
    analogWrite(left_forvard_pin, 0);
    analogWrite(left_back_pin, 0);
  }
}


void anti_enercial_motor_stop() {
  analogWrite(left_forvard_pin, 0);
  analogWrite(left_back_pin, 0);
  analogWrite(rigt_forvard_pin, 0);
  analogWrite(right_back_pin, 0);
}
