#define HEATER_UP_PIN 5
#define HEATER_DOWN_PIN 6

byte heater_up_cache = 0;     // 1
byte heater_down_cache = 0;   // 2

void init_heaters() {
  pinMode(HEATER_UP_PIN, OUTPUT);
  pinMode(HEATER_DOWN_PIN, OUTPUT);
}

void setHeaterPower(int heater, byte power) {
  module->setLED((power > 0 ? TM1638_COLOR_RED : TM1638_COLOR_GREEN), heater+2);

  switch(heater) {
    case HEATER_UP:
      if (heater_up_cache != power) {
        analogWrite(HEATER_UP_PIN, power);
        heater_up_cache = power;
      }
      break;
    case HEATER_DOWN:
      if (heater_down_cache != power) {
        analogWrite(HEATER_DOWN_PIN, power);
        heater_down_cache = power;
      }
      break;
  }
}
