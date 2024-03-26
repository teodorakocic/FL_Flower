#include <Arduino_LPS22HB.h> // Air pressure and temperature sensor
#include <Arduino_APDS9960.h> // Color, gesture, and proximity sensor
#include <Arduino_LSM9DS1.h> // Accelerometer, gyroscope and magnetometer

int side;
int countSide = 0;

int selectSide() {
    if (countSide % 75 == 0) {
      side = random(2);  
    }
}

int count = 0;
float startAccX, startAccY, startAccZ;
 
void setup() {
  Serial.begin(9600);
  while (!Serial);

  randomSeed(127);

  if (!BARO.begin()) {
    Serial.println("Failed to start the LPS22HB sensor.");
    while (1);
  }

  if (!APDS.begin()) {
    Serial.println("Failed to start the APDS9960 sensor.");
    while (1);
  }

  if (!IMU.begin()) {
    Serial.println("Failed to start the LSM9DS sensor.");
    while (1);
  }
}

void loop() {
  countSide += 1;
  
  selectSide();
  
  float accX, accY, accZ;
  IMU.readAcceleration(accX, accY, accZ);

  if (count == 1) {
    IMU.readAcceleration(startAccX, startAccY, startAccZ);
  }

  count += 1;
  
  float gyroX, gyroY, gyroZ;
  IMU.readGyroscope(gyroX, gyroY, gyroZ);

  int gestureUp, gestureDown, gestureLeft, gestureRight;
  if (APDS.gestureAvailable()) {
    int gesture = APDS.readGesture();
    switch (gesture) {
        case GESTURE_UP:
//          Serial.println("Detected UP gesture");
          gestureUp = 1;
          gestureDown = 0;
          gestureLeft = 0;
          gestureRight = 0;
          break;
        case GESTURE_DOWN:
//          Serial.println("Detected DOWN gesture");
          gestureUp = 0;
          gestureDown = 1;
          gestureLeft = 0;
          gestureRight = 0;
          break;
        case GESTURE_LEFT:
//          Serial.println("Detected LEFT gesture");
          gestureUp = 0;
          gestureDown = 0;
          gestureLeft = 1;
          gestureRight = 0;
          break;
        case GESTURE_RIGHT:
//          Serial.println("Detected RIGHT gesture");
          gestureUp = 0;
          gestureDown = 0;
          gestureLeft = 0;
          gestureRight = 1;
          break;
        default:
          break;
      }
  } else {
      if (abs(startAccX - accX) > abs(startAccY - accY)) {
        if (startAccX == accX) {
            gestureUp = 0;
            gestureDown = 0;
        } else {
            if (accX > startAccX) {
              gestureUp = 0;
              gestureDown = 1;
            }
            if (accX < startAccX) {
                gestureUp = 1;
                gestureDown = 0;
            }   
          }
            gestureRight = 0;
            gestureLeft = 0;
      } else {
        if (startAccY == accY) {
          gestureRight = 0;
          gestureLeft = 0;
        } else {
          if (accY < startAccY) {
            gestureRight = -0;
            gestureLeft = 1;
          }
          if (accY > startAccY) {
            gestureRight = 1;
            gestureLeft = 0;
          } 
        }
        gestureUp = 0;
        gestureDown = 0;
      }
  }

  if (count >= 1) {
    Serial.print(accX, 4);
    Serial.print(',');
    Serial.print(accY, 4);
    Serial.print(',');
    Serial.print(accZ, 4);
    Serial.print(',');
    Serial.print(gyroX, 4);
    Serial.print(',');
    Serial.print(gyroY, 4);
    Serial.print(',');
    Serial.print(gyroZ, 4);
    Serial.print(',');
    Serial.print(gestureUp);
    Serial.print(',');
    Serial.print(gestureDown);
    Serial.print(',');
    Serial.print(gestureLeft);
    Serial.print(',');
    Serial.print(gestureRight);
    Serial.print(',');
    Serial.print(side);
    Serial.println();
  
    delay(50);
  }
}
