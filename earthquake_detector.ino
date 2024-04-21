#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4 // Define OLED reset pin
#define buzzerPin 13 // Buzzer pin
Adafruit_MPU6050 mpu;
Adafruit_SSD1306 display(OLED_RESET);
const int threshold = 10.0; // Define the acceleration threshold for earthquake 
detection
float previousX = 0.0; // Store previous X-axis acceleration value
void setup() {
Serial.begin(115200);
while (!mpu.begin()) {
Serial.println("MPU6050 not connected!");
delay(1000);
}
Serial.println("MPU6050 ready!");
pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
// Begin OLED display
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Use I2C address 0x3C for 128x64 
 OLED
display.display(); // Clear the display
display.setTextSize(1); // Set text size
display.setTextColor(WHITE); // Set text color to white
 }
 void loop() {
sensors_event_t event;
mpu.getAccelerometerSensor()->getEvent(&event);
float currentX = event.acceleration.x; // Get current X-axis acceleration value
// Detect sudden changes in X-axis acceleration
if (abs(currentX - previousX) > threshold) {
// Display earthquake message on OLED

display.clearDisplay();
display.setCursor(0, 0);
display.println("Earthquake detected!");
display.display();
// Sound the buzzer to indicate an earthquake
tone(buzzerPin, 1000);
Serial.println("Earthquake detected!");
// Delay for 5 seconds to prevent the buzzer from sounding continuously
delay(5000);
// Stop the buzzer
noTone(buzzerPin);
// Delay for 5 seconds before clearing the OLED display
delay(5000);
display.clearDisplay(); // Clear the earthquake message after 5 seconds
 }
 previousX = currentX; // Update previous X-axis acceleration value
 // Delay for 250 milliseconds for continuous monitoring
 delay(250);
 }
