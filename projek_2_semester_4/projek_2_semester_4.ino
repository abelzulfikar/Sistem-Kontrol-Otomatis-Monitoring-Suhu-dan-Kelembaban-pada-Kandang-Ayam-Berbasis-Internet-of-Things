//BLINK
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLkl4KxK3W"
#define BLYNK_DEVICE_NAME "SISTEM MONITORING SUHU PADA KANDANG AYAM"
#define BLYNK_AUTH_TOKEN "YIeajtnhagjT0QN_wwGzTK8HrxLqMPsO"
#include <BlynkSimpleEsp32.h>
char ssid[] = "Nyari wifi ya?";
char pass[] = "modaldong";
BlynkTimer timer;

//DHT dan LCD

#include "DHT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#define DHT11PIN 15
DHT dht(DHT11PIN, DHT11);
LiquidCrystal_I2C lcd(0x27,16,2);
int relay = 5;

byte degree_symbol[8] = 
              {
                0b00111,
                0b00101,
                0b00111,
                0b00000,
                0b00000,
                0b00000,
                0b00000,
                0b00000
              };

boolean flag1, flag2 = false ;
void myTimerEvent()
{
  float humi = dht.readHumidity();
  float temp = dht.readTemperature();

  if(temp > 33){
digitalWrite(relay, HIGH);
Blynk.virtualWrite(V2,1);
}else{
digitalWrite(relay, LOW);
Blynk.virtualWrite(V2,0);   
  }
  
  Blynk.virtualWrite(V0,temp);
  Blynk.virtualWrite(V1,humi);
}

BLYNK_WRITE(V2){
  int pinValue = !param.asInt(); // assigning incoming value from pin V1 to a variable

  digitalWrite(relay, pinValue); 
}
void setup()
{
  /* Start the DHT11 Sensor */
  Serial.begin(115200);
  pinMode(relay, OUTPUT); 
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
  lcd.begin();
  lcd.backlight();
  lcd.createChar(0, degree_symbol);
  lcd.setCursor(0,0);
  lcd.print("  Suhu Dan ");
  lcd.setCursor(0,1);
  lcd.print("  Kelembaban ");
  delay(2000);
  lcd.clear();
}

void loop()
{
  Blynk.run();
  timer.run();

  float humi = dht.readHumidity();
  float temp = dht.readTemperature();
  
  lcd.setCursor(0,0);
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.write(0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity = ");
  lcd.print(humi);
  lcd.print("%");
  delay(1000);
}
