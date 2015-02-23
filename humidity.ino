#define HUMIDIFIER_PIN 4

void init_humidifier() {
  pinMode(HUMIDIFIER_PIN, OUTPUT);
}

void readHumidity() {
  humidity = dht->readHumidity();
  humidity += config_hum_calibration;
}

void turnHumidifier(boolean hum_status) {
  module->setLED((hum_status ? TM1638_COLOR_GREEN : TM1638_COLOR_RED), 2);
  digitalWrite(HUMIDIFIER_PIN, (hum_status ? HIGH : LOW));
}
