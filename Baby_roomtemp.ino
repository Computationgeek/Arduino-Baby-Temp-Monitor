#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define RED_LED 3
#define GREEN_LED 4
#define BLUE_LED 5

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  dht.begin();
  lcd.begin();
  lcd.backlight();

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Display a welcome message on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("ARDUINO");
  lcd.setCursor(0, 1);
  lcd.print("BABY MONITOR");
  delay(4000); // Display for 2 seconds
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%");

  // LED logic based on temperature readings
  if (temperature > 25) {
    // If temperature is more than 25 degrees Celsius, blink red LED
    blinkLED(RED_LED, 500); // 500 ms blink interval
  } else if (temperature >= 22 && temperature <= 25) {
    // If temperature is between 22 and 25 degrees Celsius, turn on green LED
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, LOW);
  } else if (temperature < 21) {
    // If temperature is less than 20 degrees Celsius, turn on blue LED
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, LOW);
  } else {
    // Default: Turn off all LEDs
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, LOW);
  }

  delay(2000); // Delay for 2 seconds before reading again
}

// Function to blink the LED
void blinkLED(int pin, int interval) {
  digitalWrite(pin, HIGH);
  delay(interval / 2);
  digitalWrite(pin, LOW);
  delay(interval / 2);
}
