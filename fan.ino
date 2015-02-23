#define FAN_PIN 3

byte fan_speed_cache = 0;

void init_fan() {
  pinMode(FAN_PIN, OUTPUT);
}

void update_fan_speed() {
  if (spin != fan_speed_cache) {
    analogWrite(FAN_PIN, spin);
  }
}
