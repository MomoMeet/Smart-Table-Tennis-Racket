#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  // Setup motion detection
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
  if (mpu.getMotionInterruptStatus()) {
    // Read and print mean data for the first 2 seconds
    calculateAndPrintMeanData(2000);

    delay(2000);

    // Read and print mean data for the next 2 seconds
    calculateAndPrintMeanData(2000);

    delay(2000);
  }
  delay(10);
}

void calculateAndPrintMeanData(unsigned long duration) {
  unsigned long startTime = millis();
  float sumAx = 0, sumAy = 0, sumAz = 0;
  float sumGx = 0, sumGy = 0, sumGz = 0;
  int count = 0;

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

  // Calculate mean values
  float meanAx = sumAx / count;
  float meanAy = sumAy / count;
  float meanAz = sumAz / count;
  float meanGx = sumGx / count;
  float meanGy = sumGy / count;
  float meanGz = sumGz / count;

  // Print mean values
  Serial.print(meanAx); Serial.print(",");Serial.print(meanAy); Serial.print(",");Serial.print(meanAz);Serial.print(",");Serial.print(meanGx); Serial.print(",");Serial.print(meanGy); Serial.print(",");Serial.print(meanGz); Serial.println();
}
