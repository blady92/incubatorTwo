#define FAN_1_PIN 3
#define FAN_2_PIN 9

byte fan_1_speed_cache = 0;
byte fan_2_speed_cache = 0;

void init_fan() {
  pinMode(FAN_1_PIN, OUTPUT);
  pinMode(FAN_2_PIN, OUTPUT);
}

void update_fan_speed() {
  if (spin_1 != fan_1_speed_cache) {
    analogWrite(FAN_1_PIN, spin_1);
  }
  if (spin_2 != fan_2_speed_cache) {
  analogWrite(FAN_2_PIN, spin_2);
  }
}
