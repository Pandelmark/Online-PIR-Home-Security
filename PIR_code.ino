#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "xxxxxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "PIR Security system"
#define BLYNK_AUTH_TOKEN "xxxxxxxx"  // Enter your Blynk application auth token
#define WIFI_NAME "xxxxxxxx"  // Enter your WIFI name
#define WIFI_PASSWORD "xxxxxxxx"  // Enter your WIFI password

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = WIFI_NAME;
char pass[] = WIFI_PASSWORD;

BlynkTimer timer;
int sensorValue=0;

void checkPIR(){

  sensorValue = digitalRead(D3);
  Blynk.virtualWrite(V0, sensorValue);
  Serial.print("Pin D3: ");
  Serial.println(sensorValue);

  if (sensorValue == HIGH) {
    Blynk.logEvent("motion_detected"); // Write a value of 1 to virtual pin V0
    digitalWrite(D0, HIGH);
    //digitalWrite(D1, HIGH); 
    //digitalWrite(D2, LOW);
  }
  else if (sensorValue == LOW) { // Check if sensor value is equal to LOW
    //Serial.println("System is OFF");
    digitalWrite(D0, LOW); 
    //digitalWrite(D1, LOW); 
    //digitalWrite(D2, HIGH); 
  }
}

void setup() {
  pinMode(D3, INPUT);
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, checkPIR);
}

void loop() {
  Blynk.run();  // Run the Blynk library
  timer.run();  // Run the timer for scheduled tasks
}
