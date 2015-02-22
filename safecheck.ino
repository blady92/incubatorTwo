#define CHECKS 5

int zero_checks = 0;

boolean check_sensors() {
  Serial.print("zero_checks=");
  Serial.println(zero_checks);
  Serial.print("config_flag=");
  Serial.println(config_flag);
  if (temperature_up == 0.0f) {
    zero_checks++;
  } else if (zero_checks > 0) {
    zero_checks--;
  }
  return zero_checks <= CHECKS;
}
