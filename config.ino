#define TEMP_MIN 25.0
#define TEMP_MAX 39.0
#define HUM_MIN 20
#define HUM_MAX 80
#define HUM_CAL_MIN 0
#define HUM_CAL_MAX 5
#define TEMP_CAL_MIN -1.0
#define TEMP_CAL_MAX 1.0

void loadConfig() {
  byte buttons = module->getButtons();
  Serial.println(buttons);
  if (buttons & 0b10000000) {
    restoreDefaults();
    module->setLEDs(0b0101010110101010);
    saveConfig();
    delay(1000);
    //changeDisplay(display_state);
  } else {
    loadConfigFromEEPROM();
  }
}

void loadConfigFromEEPROM() {
  config_temp_up = EEPROM.read(0)/10.f+TEMP_MIN;
  config_hum = EEPROM.read(1);
  config_temp_cal_up = EEPROM.read(2)/10.f;
  config_temp_cal_down = EEPROM.read(3)/10.f;
  config_hum_calibration = EEPROM.read(4);
  spin = EEPROM.read(5);
  m1g1 = EEPROM.read(6);
  m2g1 = EEPROM.read(7);
  cmg1 = EEPROM.read(8);
  m1g2 = EEPROM.read(9);
  m2g2 = EEPROM.read(10);
  cmg2 = EEPROM.read(11);
  config_temp_down = EEPROM.read(12)/10.f+TEMP_MIN;
  spinner_delay = EEPROM.read(13);
  spinner_power = EEPROM.read(14);
}

void restoreDefaults() {
  config_temp_up = 37.0;
  config_temp_down = 37.0;
  config_hum = 50;
  config_temp_cal_up = 0;
  config_temp_cal_down = 0;
  config_hum_calibration = 0;
  spin = 255;
  m1g1 = 255;
  m2g1 = 25;
  cmg1 = 5;
  m1g2 = 255;
  m2g2 = 255;
  cmg2 = 255;
  spinner_delay = 100;
  spinner_power = 255;
}

void saveConfig() {
  EEPROM.write(0, (config_temp_up-TEMP_MIN)*10);
  EEPROM.write(1, config_hum);
  EEPROM.write(2, config_temp_cal_up*10);
  EEPROM.write(3, config_temp_cal_down*10);
  EEPROM.write(4, config_hum_calibration);
  EEPROM.write(5, spin);
  EEPROM.write(6, m1g1);
  EEPROM.write(7, m2g1);
  EEPROM.write(8, cmg1);
  EEPROM.write(9, m1g2);
  EEPROM.write(10, m2g2);
  EEPROM.write(11, cmg2);
  EEPROM.write(12, (config_temp_down-TEMP_MIN)*10);
  EEPROM.write(13, spinner_delay);
  EEPROM.write(14, spinner_power);
}
   

