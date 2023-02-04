#include <AntaresESP8266MQTT.h> 
#include <ESP8266WiFi.h>
#define ACCESSKEY ""       // Ganti dengan access key akun Antares anda
#define WIFISSID ""         // Ganti dengan SSID WiFi anda
#define PASSWORD ""     // Ganti dengan password WiFi anda
#define applicationName ""   // Ganti dengan application name Antares yang telah dibuat
#define deviceName ""     // Ganti dengan device Antares yang telah dibuat

const int trigPin = D1;
const int echoPin = D2;

#define SOUND_VELOCITY 0.034

long duration;
int distance;
AntaresESP8266MQTT antares(ACCESSKEY); 

void setup() {
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  antares.setDebug(true);   // Nyalakan debug. Set menjadi "false" jika tidak ingin pesan-pesan tampil di serial monitor
  antares.wifiConnection(WIFISSID,PASSWORD);
  antares.setMqttServer(); 
}

void loop() {
  antares.checkMqttConnection();
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distance = duration * SOUND_VELOCITY/2;
  // Prints the distance on the Serial Monitor
  Serial.println(distance);
  antares.add("Distance", distance);
  antares.publish(applicationName, deviceName);
  delay(3000);
}
