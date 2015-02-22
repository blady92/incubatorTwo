#include "TM1638.h"
#include "DHT.h"
#include <EEPROM.h>

#define DELAY_TIME 100

#define HEATER_UP 1
#define HEATER_DOWN 2

TM1638* module;
DHT* dht;

float temperature_up;
float temperature_down;
float humidity;

float config_temp_up;          //Temperatura górna        A01
float config_temp_down;        //Temperatura dolna        A02
float config_hum;              //Wilgotność               A03
byte spin;                     //Obroty wentylatora       A04
byte spinner_delay;            //Czas przerwy obracania   A05
byte m1g1;                     //Moc 1 grzałki 1          C01
byte m2g1;                     //Moc 2 grzałki 1          C02
byte cmg1;                     //Czas mocy 1 grzałki 1    C03
byte m1g2;                     //Moc 1 grzałki 2          C04
byte m2g2;                     //Moc 2 grzałki 2          C05
byte cmg2;                     //Czas mocy 1 grzałki 2    C06
float config_temp_cal_up;      //Kalibracja temperatury   C07
float config_temp_cal_down;    //Kalibracja temperatury   C08
float config_hum_calibration;  //Kalibracja wilgotności   C09
byte spinner_power;            //Moc silnika obracacza    C10

long timer;

short counter_up, counter_down;

void setup() {
  Serial.begin(9600);
  Serial.println("Begin");
  init_display();
  loadConfig();
  changeDisplay(1);
  init_temp();
  init_humidifier();
  init_heaters();
  init_spinner();
  counter_up = cmg1;
  counter_down = cmg2;
}

void loop() {
  readTemperatures();
  readHumidity();
  if (check_sensors()) {
    logic();
    serveSpinner();
    serveDisplay();
  } else {
    Serial.println("ERROR!");
    errorous();
  }
}

void logic() {
  Serial.println(counter_up);
  /* UPPER HEATER */
  if (temperature_up <= config_temp_up) {
    if (counter_up < 0) {
      counter_up = cmg1;
    }
    if (counter_up == 0) {
      setHeaterPower(HEATER_UP, m2g1);
    } else {
      counter_up--;
      setHeaterPower(HEATER_UP, m1g1);
    }
  } else {
    counter_up = -1;
    setHeaterPower(HEATER_UP, 0);
  }
  
  /* LOWER HEATER */
  if (temperature_up <= config_temp_down) {
    if (counter_down < 0) {
      counter_down = cmg2;
    }
    if (counter_down == 0) {
      setHeaterPower(HEATER_DOWN, m2g2);
    } else {
      counter_down--;
      setHeaterPower(HEATER_DOWN, m1g2);
    }
  } else {
    counter_down = -1;
    setHeaterPower(HEATER_DOWN, 0);
  }
  
  /* HUMIDIFIER */
  turnHumidifier(humidity < config_hum);
}

void errorous() {
  setHeaterPower(HEATER_UP, 0);
  module->clearDisplay();
  module->setDisplayToString("Err");
  module->setLEDs(0b0000000011111111);
  while(1) {
  }
}
