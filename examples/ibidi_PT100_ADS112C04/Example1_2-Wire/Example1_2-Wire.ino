/*
  Using the Adam board for PT100
  By: Hara Honnappa
  Date: 13.06.2024

  This example demonstrates how to read the PT100 temperature in Centigrade using a 2-wire connection

  Hardware Connections:
  Connect the Zeiss Adam Converter board to an Arduino.
  Open the serial monitor at 115200 baud to see the output

  Note: the library is configured for gain factor of 16, Reference Resistance of 2.5kOhm
*/

#include <Wire.h>

#include <SparkFun_ADS112C04_ADC_Arduino_Library.h> // Click here to get the library: http://librarymanager/All#SparkFun_ADS122C0

SFE_ADS112C04 traySensor;
SFE_ADS112C04 lidSensor;
SFE_ADS112C04 baseSensor;

void setup(void)
{
  Serial.begin(115200);
  while (!Serial)
    ; //Wait for user to open terminal
  Serial.println(F("ibidi PT100 Example"));

  Wire.begin();

  //traySensor.enableDebugging(); //Uncomment this line to enable debug messages on Serial
  //lidSensor.enableDebugging(); //Uncomment this line to enable debug messages on Serial
  //baseSensor.enableDebugging(); //Uncomment this line to enable debug messages on Serial

  /* LID */
  if (lidSensor.begin(0x40) == false) //Connect to the PT100 using the defaults: Address 0x40 and the Wire port
  {
    Serial.println(F("PT100 not detected at 0x40 I2C address. Please check wiring. Freezing."));
    while (1)
      ;
  }
  lidSensor.configureADCmode(ADS112C04_2WIRE_MODE, ADS112C04_DATA_RATE_90SPS); // Configure the PT100 for 2-wire mode and 180SPS (Turbo is set by default in 2-wire)

  /* TRAY */
  if (traySensor.begin(0x45) == false) //Connect to the PT100 using the defaults: Address 0x40 and the Wire port
  {
    Serial.println(F("PT100 not detected at 0x45 I2C address. Please check wiring. Freezing."));
    while (1)
      ;
  }
  traySensor.configureADCmode(ADS112C04_2WIRE_MODE, ADS112C04_DATA_RATE_90SPS); // Configure the PT100 for 2-wire mode and 180SPS (Turbo is set by default in 2-wire)


  /* BASE */
  if (baseSensor.begin(0x44) == false) //Connect to the PT100 using the defaults: Address 0x40 and the Wire port
  {
    Serial.println(F("PT100 not detected at 0x44 I2C address. Please check wiring. Freezing."));
    while (1)
      ;
  }
  baseSensor.configureADCmode(ADS112C04_2WIRE_MODE, ADS112C04_DATA_RATE_90SPS); // Configure the PT100 for 2-wire mode and 180SPS (Turbo is set by default in 2-wire)
}

void loop()
{
  // Get the temperature in Centigrade
//  float temperature = lidSensor.readIbidiPT100Centigrade();
//  float temperature = lidSensor.readPT100Centigrade();
  float RTD = lidSensor.readRTD();
  float temperature = lidSensor.computeTemperatureCentigrade(RTD);
  // Print the RTD
  Serial.print(F("The RTD on the lid is: "));
  Serial.print(RTD);
  Serial.println(F("Ohm"));
  // Print the temperature
  Serial.print(F("The temperature at lid is: "));
  Serial.print(temperature);
  Serial.println(F("C"));

  // Get the temperature in Centigrade
  //temperature = traySensor.readPT100Centigrade();
  RTD = traySensor.readRTD();
  temperature = traySensor.computeTemperatureCentigrade(RTD);
  // Print the RTD
  Serial.print(F("The RTD on the Tray is: "));
  Serial.print(RTD);
  Serial.println(F("Ohm"));
  // Print the temperature
  Serial.print(F("The temperature at lid is: "));
  Serial.print(temperature);
  Serial.println(F("C"));


  // Get the temperature in Centigrade
  //temperature = baseSensor.readPT100Centigrade();
  RTD = traySensor.readRTD();
  temperature = traySensor.computeTemperatureCentigrade(RTD);
  // Print the RTD
  Serial.print(F("The RTD on the Base is: "));
  Serial.print(RTD);
  Serial.println(F("Ohm"));

  // Print the temperature
  Serial.print(F("The temperature at base is: "));
  Serial.print(temperature);
  Serial.println(F("C"));

  delay(100); //Don't pound too hard on the I2C bus
}
