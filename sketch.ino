#define BLYNK_TEMPLATE_ID "TMPL606Lqq9hH"
#define BLYNK_TEMPLATE_NAME "tes kontrol led"
#define BLYNK_AUTH_TOKEN "lWLszWj-1k0PKOZ5D8RTsMTitjvpJgvz"

#define BLYNK_PRINT Serial

#define TRIG_PIN 18 // pin TRIG Sensor Ultrasonik terhubung ke ESP32 pin 18
#define ECHO_PIN 5 // pin ECHO Sensor Ultrasonik terhubung ke ESP32 pin 5
#define LED 2 // pin LED (merah) terhubung ke ESP32 pin 2

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Wokwi-GUEST"; //nama hotspot yang digunakan
char pass[] = ""; //password hotspot yang digunakan

float duration_us, distance_cm;
float curr_water_height,last_water_height = 0;
int condition;

BLYNK_WRITE(V0)
{
  condition = param.asInt(); // mengambil inputan dari var Vo di platfrom blynk
  if (condition == 1)
  {
    digitalWrite(4, HIGH);
    Serial.println("Matikkan Notifikasi");
  }
  else {
    digitalWrite(4, LOW);
    Serial.println("Notofikasi dinyalakan");
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(4, OUTPUT);
  Blynk.begin(auth, ssid, pass);

  // Konfigurasi pin TRIG sebagai output
  pinMode(TRIG_PIN, OUTPUT);
  // Konfigurasi pin ECHO sebagai input
  pinMode(ECHO_PIN, INPUT);
  // Konfigurasi pin LED sebagai output
  pinMode(LED, OUTPUT);
  // pin buzzer
  pinMode(14, OUTPUT);

}

void loop()
{
  Blynk.run();
  
  // Mengirimkan pulsa 10 mikrodetik ke pin TRIG
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
 
  // Mengukur durasi pulsa dari pin ECHO
  duration_us = pulseIn(ECHO_PIN, HIGH);
  
  // Menghitung jarak dalam centimeter
  distance_cm = 0.017 * duration_us;

  curr_water_height = 400 - distance_cm;
  
  // Menyala LED Merah jika terdeteksi ketinggian air
  if (curr_water_height > 50) {
    if(condition == 0){
      Serial.println("Banjir, Tinggi air: " + String(curr_water_height));
      digitalWrite(LED, HIGH);
      Blink(14);
      Blynk.logEvent("banjir","Tinggi air saat ini: " + String(curr_water_height) + " cm");
    }  
  }else{
    digitalWrite(LED, LOW);
  }
 
  // Menampilkan nilai jarak ke Serial Monitor
  if(abs(curr_water_height - last_water_height) >= 1){

    Serial.print("ketingian Air: ");
    Serial.print(curr_water_height);
    Serial.println(" cm      ");
    Blynk.virtualWrite(V1, curr_water_height);
    last_water_height = curr_water_height;
  }
  
  delay(500);
}

void Blink(int x){
  digitalWrite(x, HIGH);
  delay(10);
  digitalWrite(x, LOW);
}