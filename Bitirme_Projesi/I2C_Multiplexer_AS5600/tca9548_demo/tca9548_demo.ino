#include <Wire.h>
#include <AS5600.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// AS5600 için I2C adresi
#define AS5600_I2C_ADDRESS 0x36
RF24 radio(9, 10); // CE, CSN pins

void setup() {
  Serial.begin(9600);
  Wire.begin();
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL); // Set the pipe address to communicate with the receiver
  radio.setPALevel(RF24_PA_LOW); // Set the power level (options: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX)
  
}

void loop() {

  // PCA9548A'ya uygun I2C kanalını seçmek için
  selectI2CChannel(0); // Örneğin, SD0 ve SC0 çıkışındaki kanal
  // AS5600'den açı bilgisini oku
  int angle0 = readAS5600Angle();
  
  Serial.print("Açı0: ");
  Serial.println(angle0);
  wifiSend(11);
  wifiSend(angle0);
  delay(100);

  // PCA9548A'ya uygun I2C kanalını seçmek için
  selectI2CChannel(1); // Örneğin, SD0 ve SC0 çıkışındaki kanal
  // AS5600'den açı bilgisini oku
  int angle1 = readAS5600Angle();
  
  Serial.print("Açı1: ");
  Serial.println(angle1);
  wifiSend(22);
  wifiSend(angle1);
  delay(100);

  // PCA9548A'ya uygun I2C kanalını seçmek için
  selectI2CChannel(2); // Örneğin, SD0 ve SC0 çıkışındaki kanal
  // AS5600'den açı bilgisini oku
  int angle2 = readAS5600Angle();
  
  Serial.print("Açı2: ");
  Serial.println(angle2);
  wifiSend(33);
  wifiSend(angle2);
  delay(100);

  // PCA9548A'ya uygun I2C kanalını seçmek için
  selectI2CChannel(3); // Örneğin, SD0 ve SC0 çıkışındaki kanal
  // AS5600'den açı bilgisini oku
  int angle3 = readAS5600Angle();
  
  Serial.print("Açı3: ");
  Serial.println(angle3);
  wifiSend(44);
  wifiSend(angle3);
  delay(100);

  // PCA9548A'ya uygun I2C kanalını seçmek için
  selectI2CChannel(4); // Örneğin, SD0 ve SC0 çıkışındaki kanal
  // AS5600'den açı bilgisini oku
  int angle4 = readAS5600Angle();
  
  Serial.print("Açı4: ");
  Serial.println(angle4);
  wifiSend(55);
  wifiSend(angle4);
  delay(100);
}

void selectI2CChannel(int channel) {
  Wire.beginTransmission(0x70); // PCA9548A'nın I2C adresi
  Wire.write(1 << channel);    // İlgili kanalı seç
  Wire.endTransmission();
}

int readAS5600Angle() {
  Wire.beginTransmission(AS5600_I2C_ADDRESS);
  Wire.write(0x0E); // AS5600'nin açı bilgisini okumak için komut
  Wire.endTransmission();

  delay(10);

  Wire.requestFrom(AS5600_I2C_ADDRESS, 2);

  if (Wire.available() >= 2) {
    int msb = Wire.read();
    int lsb = Wire.read();
    int angle = ((msb << 8) | lsb) & 0x0FFF; // 12-bit değer

    
    angle=map(angle, 0, 4095, 30, 200);
    return angle;
  }

  return -1; // Hata durumunda -1 döndür
}

void wifiSend(int angle){
  char str[5];
  snprintf(str, sizeof(str),"%d",angle);
  radio.write(str, strlen(str) + 1);
  Serial.println("Sent message: " + String(str));
  delay(500); // Send message every 1 second
}
