#define FAN_PIN 3

void init_fan() {
  pinMode(FAN_PIN, OUTPUT);
}

void update_fan_speed() {
  analogWrite(FAN_PIN, spin);
}
