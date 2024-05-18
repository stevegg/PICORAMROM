#include <Arduino.h>

#include <SPI.h>
#include <LiquidCrystal.h>

#define IN_LATCH_PIN 21

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

void writeDataBus(byte value);
byte readDataBus();
byte counter = 0x00;

// // MISO, MOSI, SCK (RX, TX, SCK)
// arduino::MbedSPI mbedSPI = arduino::MbedSPI(12, 11, 10);

void setup() {

  lcd.begin(16, 2);
  Serial.print("Starting up...");
  // pinMode(OUT_LATCH_PIN, OUTPUT);
  pinMode(IN_LATCH_PIN, OUTPUT);
  // digitalWrite(OUT_LATCH_PIN, LOW);
  digitalWrite(IN_LATCH_PIN, HIGH);
  SPI.begin();
  // Zero things out
  // writeDataBus(0x00);
}

char buffer[16];
void loop() {
  lcd.setCursor(2, 1);
  byte value = readDataBus();   
  sprintf(buffer, "Read: %02X", value);
  lcd.print(buffer);
}

// void writeDataBus(byte value) {
//   digitalWrite(OUT_LATCH_PIN, LOW);
//   SPI.transfer(~value);
//   digitalWrite(OUT_LATCH_PIN, HIGH);
// }

byte readDataBus() {
  SPI.beginTransaction(SPISettings(20000000, LSBFIRST, SPI_MODE1));
  // Sample
  digitalWrite(IN_LATCH_PIN, LOW);
  asm("nop\n nop\n"); 
  digitalWrite(IN_LATCH_PIN, HIGH);
  // Read
  byte value = SPI.transfer(0x00);
  SPI.endTransaction();

  return value;
}
