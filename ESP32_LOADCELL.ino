// Calibrating the load cell
#include <Arduino.h>
#include "soc/rtc.h"
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 16;
const int LOADCELL_SCK_PIN = 4;
long tara = -74248;
// Tare = 665886
/*
 * 106403 - Solto
 * -740100
 */

HX711 scale;

void setup() {
  Serial.begin(115200);
  rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    if(0)
    {
      scale.set_scale();    
      Serial.println("Tare... remove any weights from the scale.");
      delay(5000);
      scale.tare();
      Serial.println("Tare done...");
      Serial.print("Place a known weight on the scale...");
      delay(5000);
      long reading = scale.get_units(10);
      Serial.print("Result: ");
      Serial.println(reading); 
    }

    long reading = scale.read();
    long result = abs(reading-tara);
    //Serial.print("HX711 reading: ");
    Serial.println(result);
  } 
  else {
    Serial.println("HX711 not found.");
  }
  delay(50);
}

//calibration factor will be the (reading)/(known weight)
