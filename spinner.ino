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
  if (spinner_counter >= spinner_delay*SPINNER_MULTIPLIER) {
    Serial.println("Serving spinner");
    spinner_counter -= spinner_delay*SPINNER_MULTIPLIER;
    analogWrite(SPINNER_PIN, spinner_power);
    delay(SPINNER_WORK_TIME);
    analogWrite(SPINNER_PIN, 0);
  }
}
