#define DISPLAY_DATA 8
#define DISPLAY_CLOCK 21
#define DISPLAY_STROBE 7

int display_state = 1;
int config_state = -1;
boolean config_flag = false;

void init_display() {
  module = new TM1638 (DISPLAY_DATA, DISPLAY_CLOCK, DISPLAY_STROBE);
  changeDisplay(display_state);
}

const char* config_etiquetes[] = {
  "A01",
  "A02",
  "A03",
  "A04",
  "A05",
  "A06",
  "C01",
  "C02",
  "C03",
  "C04",
  "C05",
  "C06",
  "C07",
  "C08",
  "C09",
  "C10"
};

void serveDisplay() {
  byte buttons = module->getButtons();
  Serial.println(buttons);
  if (buttons & 0b10000000) {
    //module->setLEDs(0b0000000010000000);
    module->setLEDs(0);
    module->setLED(TM1638_COLOR_RED, 7);
    config_flag = true;
    serveConfig();
  }
  if (config_flag == true) {
    Serial.println("in config");
    if (buttons == 1) { // current config down
      modify_config(true);
    } else if (buttons == 2) { // current config up
      modify_config(false);
    }
    return;
  }

  if (buttons != display_state &&(
      buttons == 1 ||
      buttons == 2)) {
    changeDisplay(buttons);
  }
  module->clearDisplay();
  switch(display_state) {
    case 1:
      writeFloatNumber(temperature_up, 2);
      break;
    case 2:
      writeFloatNumber(humidity, 0);
      break;
  }
}

void modify_config(boolean inc) {
 switch(config_state) {
  case 0: //A01
    inc ? config_temp_up += 0.1 : config_temp_up -= 0.1;
    if (config_temp_up > TEMP_MAX) {
      config_temp_up = TEMP_MIN;
    }
    if (config_temp_up < TEMP_MIN) {
      config_temp_up = TEMP_MAX;
    }
    break;
  case 1: //A02
    inc ? config_temp_down += 0.1 : config_temp_down -= 0.1;
    if (config_temp_down > TEMP_MAX) {
      config_temp_down = TEMP_MIN;
    }
    if (config_temp_down < TEMP_MIN) {
      config_temp_down = TEMP_MAX;
    }
    break;
  case 2: //A03
    inc ? config_hum++ : config_hum--;
    if (config_hum > HUM_MAX) {
      config_hum = HUM_MIN;
    }
    if (config_hum < HUM_MIN) {
      config_hum = HUM_MAX;
    }
    break;
  case 3: //A04
    inc ? spin_1++ : spin_1--;
    break;
  case 4: //A05
    inc ? spin_2++ : spin_2--;
    break;
  case 5: //A06
    inc ? spinner_delay++ : spinner_delay--;
    break;
  case 6: //C01
    inc ? m1g1++ : m1g1--;
    break;
  case 7: //C02
    inc ? m2g1++ : m2g1--;
    break;
  case 8: //C03
    inc ? cmg1++ : cmg1--;
    break;
  case 9: //C04
    inc ? m1g2++ : m1g2--;
    break;
  case 10: //C05
    inc ? m2g2++ : m2g2--;
    break;
  case 11: //C06
    inc ? cmg2++ : cmg2--;
    break;
  case 12: //C07
    inc ? config_temp_cal_up += 0.1 : config_temp_cal_up -= 0.1;
    if (config_temp_cal_up > TEMP_CAL_MAX) {
      config_temp_cal_up = TEMP_MIN;
    }
    if (config_temp_cal_up < TEMP_CAL_MIN) {
      config_temp_cal_up = TEMP_CAL_MAX;
    }
    break;
  case 13: //C08
    inc ? config_temp_cal_down += 0.1 : config_temp_cal_down -= 0.1;
    if (config_temp_cal_down > TEMP_CAL_MAX) {
      config_temp_cal_down = TEMP_CAL_MIN;
    }
    if (config_temp_cal_down < TEMP_CAL_MIN) {
      config_temp_cal_down = TEMP_CAL_MAX;
    }
    break;
  case 14: //C09
    inc ? config_hum_calibration++ : config_hum_calibration--;
    if (config_hum_calibration > HUM_CAL_MAX) {
      config_hum_calibration = HUM_CAL_MIN;
    }
    if (config_hum_calibration < HUM_CAL_MIN) {
      config_hum_calibration = HUM_CAL_MAX;
    }
    break;
  case 15: //C10
    inc ? spinner_power++ : spinner_power--;
    break;
  }
  update_config_display();
}

void serveConfig() {
  config_state++;
  if (config_state > 15) {
    saveConfig();
    config_state = -1;
    config_flag = 0;
    changeDisplay(display_state);
    return;
  }
  update_config_display();
}

void update_config_display() {
  module->clearDisplay();
  switch(config_state) {
  case 0:
    writeFloatNumber(config_temp_up, 2);
    break;
  case 1:
    writeFloatNumber(config_temp_down, 2);
    break;
  case 2:
    writeFloatNumber(config_hum, 0);
    break;
  case 3:
    writeFloatNumber(spin_1, 0);
    break;
  case 4:
    writeFloatNumber(spin_2, 0);
    break;
  case 5:
    writeFloatNumber(spinner_delay, 0);
    break;
  case 6:
    writeFloatNumber(m1g1, 0);
    break;
  case 7:
    writeFloatNumber(m2g1, 0);
    break;
  case 8:
    writeFloatNumber(cmg1, 0);
    break;
  case 9:
    writeFloatNumber(m1g2, 0);
    break;
  case 10:
    writeFloatNumber(m2g2, 0);
    break;
  case 11:
    writeFloatNumber(cmg2, 0);
    break;
  case 12:
    writeFloatNumber(config_temp_cal_up, 2);
    break;
  case 13:
    writeFloatNumber(config_temp_cal_down, 2);
    break;
  case 14:
    writeFloatNumber(config_hum_calibration, 0);
    break;
  case 15:
    writeFloatNumber(spinner_power, 0);
    break;
  }
  module->setDisplayToString(config_etiquetes[config_state]);
}

void changeDisplay(int state) {
  module->setLEDs(0);
  switch(state) {
    case 1:
      module->setLED(TM1638_COLOR_GREEN, 0);
      break;
    case 2:
      module->setLED(TM1638_COLOR_GREEN, 1);
      break;
  }
  display_state = state;
}

void writeFloatNumber(float number, int precision) {
  char *buffer = new char[9];
  dtostrf(
    number,
    precision+1,
    precision,
    buffer);
  int n = strlen(buffer);
  int l = 0;
  int i = 8 - n + 1;
  if (precision == 0) {
    i--;
  }
  if (i < 0) {
    i = 0;
  }
  while (i < 8) {
    if (buffer[0] == '-') {
      module->setDisplayToString("-", 0, i);
    } else if (buffer[1] == '.') {
      module->setDisplayDigit(buffer[0]-'0', i, true);
      buffer++;
    } else {
      module->setDisplayDigit(buffer[0]-'0', i, false);
    }
    i++;
    buffer++;
  }
  module->setDisplayToString(buffer);
}
