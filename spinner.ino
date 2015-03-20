#define SPINNER_PIN 10

#define SPINNER_WORK_TIME 500
//#define SPINNER_WORK_VAL 255

#define SPINNER_MULTIPLIER 10

unsigned int spinner_counter = 0;

void init_spinner() {
  pinMode(SPINNER_PIN, OUTPUT);
}

void serveSpinner() {
  spinner_counter++;
  module->setLED(TM1638_COLOR_RED, 5);
  if (spinner_counter >= spinner_delay*SPINNER_MULTIPLIER) {
    Serial.println("Serving spinner");
    spinner_counter = 0;
    analogWrite(SPINNER_PIN, spinner_power);
    module->setLED(TM1638_COLOR_GREEN, 5);
    delay(SPINNER_WORK_TIME);
    analogWrite(SPINNER_PIN, 0);
    module->setLED(TM1638_COLOR_RED, 5);
  }
}
