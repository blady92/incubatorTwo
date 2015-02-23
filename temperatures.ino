#define DHTTYPE DHT22
#define DHT_PIN 2

void init_temp() {
  dht = new DHT(DHT_PIN, DHTTYPE);
  dht->begin();
}

void readTemperatures() {
  Serial.println("Temp begin");
  temperature_up = dht->readTemperature();
  temperature_down = temperature_up;
  
  temperature_up += config_temp_cal_up;
  temperature_down += config_temp_cal_down;
  
  Serial.println("Temp end");
}
