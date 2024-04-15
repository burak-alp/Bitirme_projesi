#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdio.h>
RF24 radio(9, 10); // CE, CSN pins

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL); // Set the pipe address to communicate with the receiver
  radio.setPALevel(RF24_PA_LOW); // Set the power level (options: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX)
}

void loop() {
  int a=180;
  char str[10];
  snprintf(str, sizeof(str),  "%d", a);
  radio.write(str, strlen(str) + 1);
  Serial.println("Sent message: " + String(str));
  delay(1000); // Send message every 1 second
}
