#include "DHT.h"
#include "math.h" // for the caluclations

#define DHTPIN 23
#define DHTTYPE DHT22
#define THERMISTORPIN 34

DHT dht(DHTPIN, DHTTYPE);

//Circuit Constants

const float SeriesResistor = 10000; //10kohm
const float NominalResistance = 10000; //@25 deg C
const float NominalTemperature = 25.0;
const float BCoefficient = 3950.0; // from spec sheet
const float ADCMax = 4095.0; // from esp32 ADC res

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);
  Serial.println("Initializing");
  dht.begin();

 
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(2000);

  float humidity = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humidity) || isnan(temp)) {

    Serial.println("Not reading data from the the DHT 22 Module");

  }

  Serial.print("Humidity in % :");
  Serial.println(humidity);
  Serial.print("Temperature in deg C:");
  Serial.println(temp);

  float AdcVal = analogRead(THERMISTORPIN);

  if (AdcVal >= ADCMax) {
    AdcVal = ADCMax - 1;
  }
  if (AdcVal <= 0){
    AdcVal = 1;
  } // This is to avoid an issue later


  //Thermistor Resistance Calc

  float Resistance = SeriesResistor / ((ADCMax/AdcVal) - 1.0);

  //Stienhard-Hart Equation

  float SH;
  SH = Resistance / NominalResistance;
  SH = log(SH);
  SH /= BCoefficient;
  SH += 1.0 / (NominalTemperature + 273.15);
  SH = 1.0 / SH;

  float tempC = SH - 273.15;

  Serial.print("Thermistor Temperature in deg C: ");
  Serial.println(tempC);

  delay(1000);
}
