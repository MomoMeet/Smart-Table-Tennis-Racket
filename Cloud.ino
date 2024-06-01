#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/Tokenhelper.h"
#include "addons/RTDBHelper.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define API_KEY ""
#define DATABASE_URL ""

Adafruit_MPU6050 mpu;

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPreMills = 0;
bool signupok = false;
/*const char ssid = "Meet";
const char pass = "Meet@Neeta403";*/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial)
    delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("*");
    delay(300);
  }
  Serial.print("");
  Serial.print("IP: ");
  Serial.print(WiFi.localIP());
  Serial.print("");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.print("Signup ok");
    signupok = true;
  } else {
    Serial.print("Error in connecting Firebase");
  }

  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  //setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true);  // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.println("");
  delay(100);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long startTime = millis();
  float sumAx = 0, sumAy = 0, sumAz = 0;
  float sumGx = 0, sumGy = 0, sumGz = 0;
  int count = 0;
  unsigned long duration=1000;

  if (Firebase.ready() && signupok && (millis() - sendDataPreMills > 2000 || sendDataPreMills == 0)) {
    if(mpu.getMotionInterruptStatus()){
      while (millis() - startTime < duration) {
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);

      sumAx += a.acceleration.x;
      sumAy += a.acceleration.y;
      sumAz += a.acceleration.z;
      sumGx += g.gyro.x;
      sumGy += g.gyro.y;
      sumGz += g.gyro.z;

      count++;
      delay(10); // Adjust delay based on sampling frequency
      }
      float meanAx = sumAx / count;
      float meanAy = sumAy / count;
      float meanAz = sumAz / count;
      float meanGx = sumGx / count;
      float meanGy = sumGy / count;
      float meanGz = sumGz / count;
      //Storing senor data to a RTDB
      if (Firebase.RTDB.setFloat(&fbdo, "MPU6050/meanax", meanAx)) {
        Serial.print("Successfully send ax");
      } else {
        Serial.print("FAILED: " + fbdo.errorReason());
      }
      if (Firebase.RTDB.setFloat(&fbdo, "MPU6050/meanay", meanAy)) {
        Serial.print("Successfully send ay");
      } else {
        Serial.print("FAILED: " + fbdo.errorReason());
      }
      if (Firebase.RTDB.setFloat(&fbdo, "MPU6050/meanaz", meanAz)) {
        Serial.print("Successfully send az");
      } else {
        Serial.print("FAILED: " + fbdo.errorReason());
      }
      if (Firebase.RTDB.setFloat(&fbdo, "MPU6050/meangx", meanGx)) {
        Serial.print("Successfully send gx");
      } else {
        Serial.print("FAILED: " + fbdo.errorReason());
      }
      if (Firebase.RTDB.setFloat(&fbdo, "MPU6050/meangy", meanGy)) {
        Serial.print("Successfully send gy");
      } else {
        Serial.print("FAILED: " + fbdo.errorReason());
      }
      if (Firebase.RTDB.setFloat(&fbdo, "MPU6050/meangz", meanGz)) {
        Serial.println("Successfully send gz");
      } else {
        Serial.println("FAILED: " + fbdo.errorReason());
      }
    }
    delay(1000);
  }
}
