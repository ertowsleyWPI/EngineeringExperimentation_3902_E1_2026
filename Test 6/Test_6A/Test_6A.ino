#include "DHT.h"

#define DHTPIN 23
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);



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

}
