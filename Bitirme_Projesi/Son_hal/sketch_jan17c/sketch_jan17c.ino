#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Adafruit_PWMServoDriver nesnesi oluşturuluyor
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Servo motorunun bağlı olduğu PWM çıkış kanalı

RF24 radio(9, 10); // CE, CSN pins
int i,a,z,q,r,k,o;
int toplam,toplama,w,y,u;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL); // Set the pipe address to communicate with the transmitter
  radio.setPALevel(RF24_PA_LOW); // Set the power level (options: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX)
  radio.startListening();
  // I2C haberleşmesini başlat
  Wire.begin();

  // PWM sürücüsünü başlat
  pwm.begin();
      

  // PWM frekansını ayarla (Hz)
  pwm.setPWMFreq(60);

  delay(10);
  base();
}

void loop() {
    int s=600;
    char *ptr;
    int deger = 0;
    char receivedMessage[32] = {0}; // Maximum message length
    radio.read(&receivedMessage, sizeof(receivedMessage));
    deger=strtol(receivedMessage,&ptr,10);
   
if(deger==11){
      delay(s);
      receivedMessage[32] = {0}; // Maximum message length
      radio.read(&receivedMessage, sizeof(receivedMessage));
      Serial.println("Received message1: " + String(receivedMessage));
      // Servo motoru 0 derece konumuna getir
       int angle=0;
      char *a;
      angle=strtol(receivedMessage,&a,10);
      y =y+angle;
      
      k=k+1;
      Serial.println(k);
      if(k==4){
        y = y*0.25;
        moveServo(0, y);
       Serial.println(y);
        Serial.println(k);
       k=0;
       y=0;
       delay(150);
}
}
if(deger==44){
      delay(s);
      receivedMessage[32] = {0}; // Maximum message length
      radio.read(&receivedMessage, sizeof(receivedMessage));
      Serial.println("Received message4: " + String(receivedMessage));
      // Servo motoru 0 derece konumuna getir
       int angle=0;
      char *a;
      angle=strtol(receivedMessage,&a,10);
      u =u+angle;
      
      o=o+1;
      Serial.println(o);
      if(o==4){
      u = u*0.25;
      moveServo(3, u);
      moveServo(5, 180);
      Serial.println(u);
      Serial.println(o);
      o=0;
      u=0;
      delay(150);
}
}
if(deger==55){
      delay(s);
      receivedMessage[32] = {0}; // Maximum message length
      radio.read(&receivedMessage, sizeof(receivedMessage));
      Serial.println("Received message5: " + String(receivedMessage));
      // Servo motoru 0 derece konumuna getir
       int angle=0;
      char *a;
      angle=strtol(receivedMessage,&a,10);
      w =w+angle;
      
      r=r+1;
      Serial.println(r);
      if(r==4){
      w = w*0.25;
      moveServo(4, w);
      Serial.println(w);
      Serial.println(r);
      w=0;
      r=0;
      delay(150);
}
}

if(deger==33){
      delay(s);
      receivedMessage[32] = {0}; // Maximum message length
      radio.read(&receivedMessage, sizeof(receivedMessage));
      Serial.println("Received message3: " + String(receivedMessage));
      // Servo motoru 0 derece konumuna getir
       int angle=0;
      char *a;
      angle=strtol(receivedMessage,&a,10);
      toplam =toplam+angle;
      
      z=z+1;
      Serial.println(z);
      if(z==4){
      toplam = toplam*0.25;
      moveServo(2, toplam);
      moveServo(5, 30);
      Serial.println(toplam);
      Serial.println(z);
      toplam=0;
      z=0;
      delay(150);
}
}
if(deger==22){
      delay(s);
      receivedMessage[32] = {0}; // Maximum message length
      radio.read(&receivedMessage, sizeof(receivedMessage));
      Serial.println("Received message2: " + String(receivedMessage));
      // Servo motoru 0 derece konumuna getir
       int angle=0;
      char *a;
      angle=strtol(receivedMessage,&a,10);
      toplama =toplama+angle;
      
      q=q+1;
      Serial.println(q);
      if(q==4){
      toplama = toplama*0.25;
      moveServo(1, toplama);
      Serial.println(toplama);
      Serial.println(q);
      toplama=0;
      q=0;
      delay(150);
}
}
   }

  void base(){
    moveServo(5, 150);
    delay(100);
      moveServo(4, 90);
          delay(100);

      moveServo(3, 40);
          delay(100);

      moveServo(2, 180);
          delay(100);

      moveServo(1, 140);
          delay(100);

      moveServo(0, 180);
          delay(100);

  }
  

void moveServo(uint8_t channel, uint16_t degrees) {
  // Dereceyi mikrosaniyeye dönüştür
  uint16_t pulse = map(degrees, 30, 200, 150, 600);

  // PWM sürücüsüne komut gönder
  pwm.setPWM(channel, 0, pulse);
  delay(100);
}

