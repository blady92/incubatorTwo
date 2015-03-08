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
  case 0:
    inc ? config_temp_up += 0.1 : config_temp_up -= 0.1;
    if (config_temp_up > TEMP_MAX) {
      config_temp_up = TEMP_MIN;
    }
    if (config_temp_up < TEMP_MIN) {
      config_temp_up = TEMP_MAX;
    }
    break;
  case 1:
    inc ? config_temp_down += 0.1 : config_temp_down -= 0.1;
    if (config_temp_down > TEMP_MAX) {
      config_temp_down = TEMP_MIN;
    }
    if (config_temp_down < TEMP_MIN) {
      config_temp_down = TEMP_MAX;
    }
    break;
  case 2:
    inc ? config_hum++ : config_hum--;
    if (config_hum > HUM_MAX) {
      config_hum = HUM_MIN;
    }
    if (config_hum < HUM_MIN) {
      config_hum = HUM_MAX;
    }
    break;
  case 3:
    inc ? spin_1++ : spin_1--;
    break;
  case 4:
    inc ? spin_2++ : spin_2--;
    break;
  case 5:
    inc ? spinner_delay++ : spinner_delay--;
    break;
  case 6:
    inc ? m1g1++ : m1g1--;
    break;
  case 7:
    inc ? m2g1++ : m2g1--;
    break;
  case 8:
    inc ? cmg1++ : cmg1--;
    break;
  case 9:
    inc ? m1g2++ : m1g2--;
    break;
  case 10:
    inc ? m2g2++ : m2g2--;
    break;
  case 11:
    inc ? cmg2++ : cmg2--;
    break;
  case 12:
    inc ? config_temp_cal_up += 0.1 : config_temp_cal_up -= 0.1;
    if (config_temp_cal_up > TEMP_CAL_MAX) {
      config_temp_cal_up = TEMP_MIN;
    }
    if (config_temp_cal_up < TEMP_CAL_MIN) {
      config_temp_cal_up = TEMP_CAL_MAX;
    }
    break;
  case 13:
    inc ? config_temp_cal_down += 0.1 : config_temp_cal_down -= 0.1;
    if (config_temp_cal_down > TEMP_CAL_MAX) {
      config_temp_cal_down = TEMP_CAL_MIN;
    }
    if (config_temp_cal_down < TEMP_CAL_MIN) {
      config_temp_cal_down = TEMP_CAL_MAX;
    }
    break;
  case 14:
    inc ? config_hum_calibration++ : config_hum_calibration--;
    if (config_hum_calibration > HUM_CAL_MAX) {
      config_hum_calibration = HUM_CAL_MIN;
    }
    if (config_hum_calibration < HUM_CAL_MIN) {
      config_hum_calibration = HUM_CAL_MAX;
    }
    break;
  case 15:
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
  if (number == 0) {
    if (precision == 0) {
      module->setDisplayDigit(0, 7, false);
    } else {
      module->setDisplayDigit(0, 7-precision, true);
      for(int i = 0; i < precision; i++) {
        module->setDisplayDigit(0, 7-i, false);
      }
    }
    return;
  }

  int dots = 0;
  boolean rev_flag = (number <= 0);

  if (rev_flag) {
    number *= -1.0f;
  }

  if (precision > 0) {
    int c = pow(10, precision);
    number *= c;
    dots = 1;
    while (number > c) {
      c *= 10;
      dots *= 2;
    }
  }

  int i_number = (int)number;

  if (precision > 0) {
    int r = i_number%10;
    if (r < 5) {
     i_number -= r;
    } else {
     i_number += 10-r;
    }
  }

  if (rev_flag) {
    i_number *= -1;
  }
  module->setDisplayToDecNumber(i_number, dots);
}
